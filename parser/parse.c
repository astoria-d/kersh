
#include <stdio.h>
#include "kersh.tab.h"
#include "util.h"
#include "parser.h"
#include "symbols.h"
#include "code.h"
#include "utlist.h"
#include "util.h"

#define START_TOKEN 0

struct token_list {
    enum tk_type token;
    union {
        unsigned long   lval;
        char*           strval;
    };
    struct token_list *prev;
    struct token_list *next;
};

/*  nested code block main data  */
struct parse_stage {
    struct token_list* start;
    struct parse_stage *prev;
    struct parse_stage *next;
    struct code_block* cb;
    struct type_definition* td;
};


static void print_token(const char* parse_text);
static void free_token(struct token_list* tkn);
static void dbg_print_token(struct token_list* tl);

static unsigned int pr_indent;
static unsigned int pr_newline;
static unsigned int enum_index;

static struct token_list* cur_token;
static struct parse_stage* cur_stage;

static struct token_list* token_list_head;
static struct parse_stage* head_stage;
static struct code_block* root_code_block;

static int declare_handled;

/*kersh implementations...*/

void pre_shift_token(const char* parse_text, int token_num) {
    unsigned long const_int_val;

    if (token_num == '}') {
        indent_dec(); 
    }
    print_token(parse_text);

    struct token_list* tk;
    tk = ker_malloc(sizeof(struct token_list));
    memset(tk, 0, sizeof(struct token_list));
    tk->token = token_num;
    DL_APPEND(token_list_head, tk);
    cur_token = tk;

    switch (token_num) {
        case IDEN:
        tk->strval = ker_strdup(parse_text);
        //printf("dup %s...\n", parse_text);
        break;

        case ENUM:
        enter_parse_stage(token_num);
        declare_handled = 0;
        break;

        case ENUM_CONSTANT:
        tk->strval = ker_strdup(parse_text);
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
        declare_handled = 0;
        break;


        case '{':
        if (!cur_stage->start) {
            printf("new block...");
        }
        else if (cur_stage->start->token == ENUM) {
            struct type_definition* td;

            td = cb_add_enum_block(&cur_stage->cb->types);
            if (cur_token->prev->token == IDEN) {
                td->name = ker_strdup(cur_token->prev->strval);
            }
            cur_stage->td = td;
        }
        else if (cur_stage->start->token == STRUCT || cur_stage->start->token == UNION) {
            if (cur_stage->td->type_id == TP_STRUCT || cur_stage->td->type_id == TP_UNION) {
                struct type_definition* td;
                /*already in struct definition stage.*/
                td = cb_add_sub_struct_block(cur_stage->td, cur_stage->start->token,
                    cur_token->prev->token == IDEN ? cur_token->prev->strval : NULL);
                cur_stage->td = td;
            }
            else {
                struct type_definition* td;
                /*first level struct definition. add to code block.*/
                td = cb_add_struct_block(&cur_stage->td, cur_stage->start->token,
                    cur_token->prev->token == IDEN ? cur_token->prev->strval : NULL);
                cur_stage->td = td;
            }
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
int check_token_type(const char* parse_text) {
    /*printf("ps_stage: %d\n", ps_stage);*/
    if (cur_stage->start && cur_stage->start->token == ENUM &&
        (cur_token->token == '{' || cur_token->token == ',') ) {
        return ENUM_CONSTANT;
    }
    else {
        /*check if the token is in the symbol table.*/
        struct code_block* cb;
        struct symbol* sym;

        cb = cur_stage != NULL ? cur_stage->cb : root_code_block;
        if (cb->symbol_table == NULL) return IDEN;
        sym = lookup_symbol(cb->symbol_table, parse_text);
        if (sym == NULL) return IDEN;
        if (sym->symbol_type == SYM_TYPEDEF) return TYPEDEF_NAME;
        return IDEN;
    }
}

void enter_parse_stage(int stage) {
    struct parse_stage* ps;

    //printf("enter stage...\n");
    if (stage == ENUM) {
        enum_index = 0;
    }
    ps = ker_malloc(sizeof(struct parse_stage));
    memset(ps, 0, sizeof(struct parse_stage));
    ps->start = cur_token;
    ps->cb = cur_stage != NULL ? cur_stage->cb : root_code_block;
    ps->td = cur_stage != NULL ? cur_stage->td : root_code_block->types;
    DL_APPEND(head_stage, ps);
    cur_stage = ps;
    //printf("stage %d entered, %08x\n", stage, ps);
}

void exit_parse_stage(void) {
    struct parse_stage* ps;
/*
*/
    //printf("exit stage...\n");
    struct token_list *prev, *t1;

    prev = cur_token;
    cur_token = cur_stage->start->prev;
    //printf("cur_token:%08x, prev:%08x\n", cur_token, prev);
    //dbg_print_token(cur_token);
    while(prev != cur_token) {
//        DL_DELETE(token_list_head, prev);
//        t1 = prev;
        prev = prev->prev;
//        free_token(t1);
    }

    ps = cur_stage;
    cur_stage = cur_stage->prev;
    DL_DELETE(head_stage, ps);
    ker_free(ps);
    //printf("stage %d exite, %08x\n", ps->stage, ps);
}

struct type_definition* lookup_declaration(void) {
    struct type_definition* decl;
    struct token_list* prev;
    struct token_list* tmp;
    int name_cnt = 0;

    //printf("lookup decl...\n");
    /*lookup token history.*/
    decl = alloc_typedef();

    /*cur token is ';'*/
    prev = cur_token->prev;
    DL_DELETE(token_list_head, cur_token);
    free_token(cur_token);

    while(prev) {
        struct token_list* pp;

        //dbg_print_token(prev);
        if (prev == token_list_head) {
            /*the head item is token_list_head*/
            break;
        }
        if (prev->token == ';') {
            break;
        }
        if (prev->token == '{') {
            break;
        }
        switch (prev->token) {
        case IDEN:
            /*struct case declaration is like this.
             * struct type_name str_name;
             * */
            if (name_cnt == 0)
                decl->name = ker_strdup(prev->strval);
            else if (name_cnt == 1)
                decl->type_name = ker_strdup(prev->strval);
            name_cnt++;
            break;

        case CONST:
            decl->ql.is_const = 1;
            break;

        case VOLATILE:
            decl->ql.is_volatile = 1;
            break;

        case '*':
            decl->ql.is_pointer = 1;
            decl->pointer_cnt++;
            decl->size = sizeof(void*);
            break;

        case VOID:
            decl->type_id = TP_BASE_0;
            decl->size = 0;
            break;

        case CHAR:
            decl->type_id = TP_BASE_1;
            if (!decl->ql.is_pointer) decl->size = 1;
            break;

        case SHORT:
            decl->type_id = TP_BASE_2;
            if (!decl->ql.is_pointer) decl->size = 2;
            break;

        case INT:
            decl->type_id = TP_BASE_4;
            if (!decl->ql.is_pointer) decl->size = 4;
            break;

        case LONG:
            decl->type_id = sizeof(long) == 8 ? TP_BASE_8 : TP_BASE_4;
            if (!decl->ql.is_pointer) decl->size = sizeof(long);
            break;

        case UNSIGNED:
            decl->ql.is_unsigned = 1;
        case SIGNED:
            if (!decl->type_id) decl->type_id = TP_BASE_4;
            if (!decl->ql.is_pointer) {
                if (!decl->size) decl->size = 4;
            }
            break;

        case '}':
            pp = prev->prev;
            if (pp->token == '{') {
                tmp = prev->prev;
                DL_DELETE(token_list_head, prev);
                free_token(prev);
                prev = tmp;
                name_cnt++;
                decl->ql.internal_def = 1;
            }
            break;

        case STRUCT:
            decl->type_id = TP_STRUCT;
            break;

        case UNION:
            decl->type_id = TP_UNION;
            break;

        case TYPEDEF:
            decl->ql.is_typedef = 1;
            break;

        default:
            printf("not handled!!!!\n");
        }
        tmp = prev->prev;
        DL_DELETE(token_list_head, prev);
        free_token(prev);
        prev = tmp;
    }
    cur_token = prev;
    if (!prev) {
        return NULL;
    }

    return decl;
}

static void free_token(struct token_list* tkn) {
    //printf("delete token ");
    //dbg_print_token(tkn);
    if (tkn->token == IDEN || tkn->token == ENUM_CONSTANT) {
        ker_free(tkn->strval);
    }
    ker_free(tkn);
}

int get_current_stage(void) {
    return cur_stage->start->token;
}

struct type_definition* get_current_td(void) {
    return cur_stage->td;
}

struct code_block* get_current_cb(void) {
    return cur_stage->cb;
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

void set_decl_handled(int val) {
    declare_handled = val;
}

int get_decl_handled(void) {
    return declare_handled;
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

void indent_inc(void) {
    pr_indent++;
}

void indent_dec(void) {
    pr_indent--;
}


/* print utilities....*/

void line_break(void) {
    printf("\n");
    pr_newline = 1;
}

static void print_token(const char* parse_text) {
    if (pr_newline) {
        int i;
        for (i = 0; i < pr_indent; i++) {
             printf("  ");
        }
    }
    pr_newline = 0;
    printf("%s ", parse_text);
}

#define CASE_BREAK(token)\
    case token:                      p = #token; break;

static void dbg_print_token(struct token_list* tl) {
    char* p;
    switch (tl->token) {
    CASE_BREAK(AUTO)
    CASE_BREAK(BREAK)
    CASE_BREAK(CASE)
    CASE_BREAK(CHAR)
    CASE_BREAK(CONST)
    CASE_BREAK(CONTINUE)
    CASE_BREAK(DEFAULT)
    CASE_BREAK(DO)
    CASE_BREAK(ELSE)
    CASE_BREAK(ENUM)
    CASE_BREAK(EXTERN)
    CASE_BREAK(FOR)
    CASE_BREAK(GOTO)
    CASE_BREAK(IF)
    CASE_BREAK(INLINE)
    CASE_BREAK(INT)
    CASE_BREAK(LONG)
    CASE_BREAK(REGISTER)
    CASE_BREAK(RETURN)
    CASE_BREAK(SHORT)
    CASE_BREAK(SIGNED)
    CASE_BREAK(SIZEOF)
    CASE_BREAK(STATIC)
    CASE_BREAK(STRUCT)
    CASE_BREAK(SWITCH)
    CASE_BREAK(TYPEDEF)
    CASE_BREAK(UNION)
    CASE_BREAK(UNSIGNED)
    CASE_BREAK(VOID)
    CASE_BREAK(VOLATILE)
    CASE_BREAK(WHILE)
    CASE_BREAK(IDEN)
    CASE_BREAK(DECIMAL_CONSTANT)
    CASE_BREAK(OCTAL_CONSTANT)
    CASE_BREAK(HEX_CONSTANT)
    CASE_BREAK(ENUM_CONSTANT)
    CASE_BREAK(INVALID)
    CASE_BREAK(C_CHAR)
    CASE_BREAK(S_CHAR)
    CASE_BREAK(TYPEDEF_NAME)
    CASE_BREAK(LOWER_THAN_ELSE)
    CASE_BREAK(ARROW)
    CASE_BREAK(INC)
    CASE_BREAK(DEC)
    CASE_BREAK(LSHIFT)
    CASE_BREAK(RSHIFT)
    CASE_BREAK(LE)
    CASE_BREAK(GE)
    CASE_BREAK(EQEQ)
    CASE_BREAK(NE)
    CASE_BREAK(L_AND)
    CASE_BREAK(L_OR)
    CASE_BREAK(DOT3)
    CASE_BREAK(ASTR_EQ)
    CASE_BREAK(DASH_EQ)
    CASE_BREAK(PERC_EQ)
    CASE_BREAK(PLUS_EQ)
    CASE_BREAK(MINUS_EQ)
    CASE_BREAK(LSHIFT_EQ)
    CASE_BREAK(RSHIFT_EQ)
    CASE_BREAK(AMP_EQ)
    CASE_BREAK(HAT_EQ)
    CASE_BREAK(OR_EQ)

    CASE_BREAK(LBRACKET)
    CASE_BREAK(RBRACKET)
    CASE_BREAK(LPAR)
    CASE_BREAK(RPAR)
    CASE_BREAK(LBRACE)
    CASE_BREAK(RBRACE)
    CASE_BREAK(DOT)
    CASE_BREAK(AMP)
    CASE_BREAK(ASTR)
    CASE_BREAK(PLUS)
    CASE_BREAK(MINUS)
    CASE_BREAK(TILDA)
    CASE_BREAK(EXQL)
    CASE_BREAK(DASH)
    CASE_BREAK(PERCENT)
    CASE_BREAK(LT)
    CASE_BREAK(GT)
    CASE_BREAK(HAT)
    CASE_BREAK(OR)
    CASE_BREAK(QUESTION)
    CASE_BREAK(COLON)
    CASE_BREAK(SEMI_COLON)
    CASE_BREAK(EQ)
    CASE_BREAK(COMMA)

    CASE_BREAK(ATTRIBUTE)
    }
    printf("token = [%s]\n", (tl->token == IDEN || tl->token == ENUM_CONSTANT) ? tl->strval : p);

}

void init_parser(void) {
    extern int yydebug;
    yydebug = 0;
    cur_stage = NULL;
    head_stage = NULL;
    cur_token = NULL;
    token_list_head = NULL;
    pr_indent = 0;
    pr_newline = 0;
    declare_handled = 0;
    init_utils();
    init_symbols();

    root_code_block = create_code_block();
    root_code_block->types = alloc_typedef();
    /*create dummy head block.*/
    root_code_block->types->name = ker_strdup("null_type");
    enter_parse_stage(START_TOKEN);
    cur_stage->cb = root_code_block;
}

void exit_parser(void) {
    struct parse_stage *stg, *tmp1;
    struct token_list *tk, *tmp2;

    printf("deleting stages");
    DL_FOREACH_SAFE(head_stage, stg, tmp1) {
        printf(".");
        LL_DELETE(head_stage, stg);
        ker_free(stg);
    }
    printf("\n");
    printf("deleting tokens");
    DL_FOREACH_SAFE(token_list_head, tk, tmp2) {
        printf(".");
        LL_DELETE(token_list_head, tk);
        if (tk) free_token(tk);
    }
    printf("\n");
    free_code_block(root_code_block);
    exit_utils();
}
