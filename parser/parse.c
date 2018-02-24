
#include <stdio.h>
#include "kersh.tab.h"
#include "parser.h"
#include "symbols.h"
#include "code.h"
#include "utlist.h"

int line_num;

static unsigned int pr_indent;
static unsigned int pr_newline;
static unsigned int enum_index;

struct token_list {
    int token;
    union {
        unsigned long   lval;
        char*           strval;
    };
    struct token_list *prev;
    struct token_list *next;
};
static struct token_list* cur_token;
static struct token_list* token_list_head;

struct parse_stage {
    struct token_list* start;
    struct parse_stage *prev;
    struct parse_stage *next;
};
static struct parse_stage* cur_stage;
static struct parse_stage* head_stage;

/*bison required functions...*/
void yyerror (char const *s) {
    fprintf (stderr, "line: %d,\n   %s\n", line_num, s);
}

int yywrap (void )
{
    return 1;
}

/*kersh implementations...*/

void pre_shift_token(const char* parse_text, int token_num) {
    unsigned long const_int_val;

    if (token_num == '}') {
        indent_dec(); 
    }
    print_token(parse_text);

    struct token_list* tk;
    tk = malloc(sizeof(struct token_list));
    memset(tk, 0, sizeof(struct token_list));
    tk->token = token_num;
    DL_APPEND(token_list_head, tk);
    cur_token = tk;

    switch (token_num) {
        case IDEN:
        tk->strval = strdup(parse_text);
        //printf("dup %s...\n", parse_text);
        break;

        case TYPEDEF:
        enter_parse_stage(token_num); 
        break;

        case ENUM:
        enter_parse_stage(token_num); 
        break;

        case ENUM_CONSTANT:
        tk->strval = strdup(parse_text);
        break;

        case DECIMAL_CONSTANT:
        sscanf(parse_text, "%d", &const_int_val);
        tk->lval = const_int_val;
        break;

        case OCTAL_CONSTANT:
        sscanf(parse_text, "%o", &const_int_val);
        tk->lval = const_int_val;
        break;

        case HEX_CONSTANT:
        sscanf(parse_text, "%x", &const_int_val);
        tk->lval = const_int_val;
        break;

        case STRUCT:
        case UNION:
        enter_parse_stage(token_num); 
        break;

        case VOID:
        case CHAR:
        case SHORT:
        case INT:
        case LONG:
        case SIGNED:
        case UNSIGNED:
        break;

        case '{':
        if (cur_stage->start->token == ENUM) {
            cb_add_enum_block();
            if (cur_token->prev->token == IDEN) {
                cb_set_enum_name(cur_token->prev->strval);
            }
        }
        else if (cur_stage->start->token == STRUCT || cur_stage->start->token == UNION) {
            cb_add_struct_block(cur_stage->start->token, 
                cur_token->prev->token == IDEN ? cur_token->prev->strval : NULL);
        }
        line_break();
        indent_inc(); 
        break;

        case ';':
        case ':':
        line_break();
        break;

    }
}

/*check input token is identifier or enum constant or typedef name*/
int check_token_type(void) {
    /*printf("ps_stage: %d\n", ps_stage);*/
    if (!cur_stage || !cur_stage->start) {
        return IDEN;
    }
    if (cur_stage->start->token == ENUM &&
        (cur_token->token == '{' || cur_token->token == ',') ) {
        return ENUM_CONSTANT;
    }
    else {
        return IDEN;
    }
}

void enter_parse_stage(int stage) {
    struct parse_stage* ps;

    if (stage == ENUM) {
        enum_index = 0;
    }
    ps = malloc(sizeof(struct parse_stage));
    memset(ps, 0, sizeof(struct parse_stage));
    ps->start = cur_token;
    DL_APPEND(head_stage, ps);
    cur_stage = ps;
    //printf("stage %d entered, %08x\n", stage, ps);
}

void exit_parse_stage(void) {
    struct parse_stage* ps;
/*
*/
    struct token_list *prev, *t1;

    prev = cur_token;
    cur_token = cur_stage->start->prev;
    //printf("cur_token:%08x, prev:%08x\n", cur_token, prev);
    while(prev != cur_token) {
        //printf("del token:%04x, %40s, %x\n", prev->token, 
          //      (prev->token == IDEN || prev->token == ENUM_CONSTANT) ? prev->strval : "-", prev);
        DL_DELETE(token_list_head, prev);
        t1 = prev;
        prev = prev->prev;
        if (t1->token == IDEN || t1->token == ENUM_CONSTANT) {
            free(t1->strval);
        }
        free(t1);
    }

    ps = cur_stage;
    cur_stage = cur_stage->prev;
    DL_DELETE(head_stage, ps);
    free(ps);
    //printf("stage %d exite, %08x\n", ps->stage, ps);
}

int get_current_stage(void) {
    return cur_stage->start->token;
}

int get_const_val(void) {
    struct token_list* prev = cur_token;
    while(prev) {
        if (prev->token == DECIMAL_CONSTANT || 
            prev->token == OCTAL_CONSTANT || 
            prev->token == HEX_CONSTANT)
            return (int)prev->lval;
        prev = prev->prev;
    }
    return 0;
}

int get_enum_index() {
    return enum_index;
}

void set_enum_index(int val) {
    enum_index = val;
}

char* get_old_identifer(void) {
    struct token_list* prev = cur_token;
    while(prev) {
        if (prev->token == IDEN || prev->token == ENUM_CONSTANT)
            return prev->strval;
        prev = prev->prev;
    }
    return NULL;
}

void line_break(void) {
    printf("\n");
    pr_newline = 1;
}

void print_token(const char* parse_text) {
    if (pr_newline) {
        int i;
        for (i = 0; i < pr_indent; i++) {
             printf("  ");
        }
    }
    pr_newline = 0;
    printf("%s ", parse_text);
}

void indent_inc(void) {
    pr_indent++;
}

void indent_dec(void) {
    pr_indent--;
}

void init_parser(void) {
    extern int yydebug;
    yydebug = 0;
    line_num = 1;
    cur_stage = NULL;
    head_stage = NULL;
    cur_token = NULL;
    token_list_head = NULL;
    pr_indent = 0;
    pr_newline = 0;
    init_code_block();
}

void exit_parser(void) {
    if (head_stage) {
        free(head_stage);
    }
    exit_code_block();
}
