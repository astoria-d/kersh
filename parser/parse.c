
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
static unsigned int const_int_val;

static int old_token;
static char* old_identifier;

struct parse_stage {
    int     stage;
    struct parse_stage *prev;
    struct parse_stage *next;
};
static struct parse_stage* cur_stage;
static struct parse_stage* head_stage;

static void check_old_buf(void);

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

    if (token_num == '}') {
        indent_dec(); 
    }
    print_token(parse_text);

    switch (token_num) {
        case IDEN:
        /*set_last_symbol(parse_text);*/
        check_old_buf();
        old_identifier = strdup(parse_text);
        break;

        case TYPEDEF:
        enter_parse_stage(token_num); 
        break;

        case ENUM:
        enter_parse_stage(token_num); 
        break;

        case ENUM_CONSTANT:
        cb_add_emu_def(parse_text, enum_index++);
        break;

        case DECIMAL_CONSTANT:
        sscanf(parse_text, "%d", &const_int_val);
        break;

        case OCTAL_CONSTANT:
        sscanf(parse_text, "%o", &const_int_val);
        break;

        case HEX_CONSTANT:
        sscanf(parse_text, "%x", &const_int_val);
        break;

        case STRUCT:
        case UNION:
        enter_parse_stage(token_num); 
        break;

        case '{':
        if (cur_stage->stage == STRUCT || cur_stage->stage == UNION) {
            //sym_add_struct_def(old_identifier);
            old_identifier = NULL;
        }
        line_break();
        indent_inc(); 
        break;

        case ';':
        case ':':
        line_break();
        break;

    }

    old_token = token_num;
}

/*check input token is identifier or enum constant or typedef name*/
int check_token_type(void) {
    /*printf("ps_stage: %d\n", ps_stage);*/
    if (cur_stage->stage == ENUM && (old_token == '{' || old_token == ',') ) {
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
    ps->stage = stage;
    DL_APPEND(head_stage, ps);
    cur_stage = ps;
    //printf("stage %d entered, %08x\n", stage, ps);
}

void exit_parse_stage(void) {
    struct parse_stage* ps;

    ps = cur_stage;
    cur_stage = cur_stage->prev;
    DL_DELETE(head_stage, ps);
    //printf("stage %d exite, %08x\n", ps->stage, ps);
    free(ps);
}

int get_const_val(void) {
    return const_int_val;
}

void set_enum_index(int next_index) {
    enum_index = next_index;
}

void free_identifer(void) {
    free(old_identifier);
    old_identifier = NULL;
}

static void check_old_buf(void) {
    if (old_identifier) {
        /*old_identifier must be correctly handled in the reducer function.*/
        printf(">>[%s] symbol left unfree...", old_identifier);
        free_identifer();
    }
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
    pr_indent = 0;
    pr_newline = 0;
    old_identifier = NULL;
    init_code_block();
}

void exit_parser(void) {
    if (head_stage) {
        free(head_stage);
    }
    check_old_buf();
    exit_code_block();
}
