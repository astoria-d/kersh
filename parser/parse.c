
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
    int token;
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

        case TYPEDEF:
        enter_parse_stage(token_num); 
        break;

        case ENUM:
        enter_parse_stage(token_num); 
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
        break;
/*
        case VOID:
        case CHAR:
        case SHORT:
        case INT:
        case LONG:
        case SIGNED:
        case UNSIGNED:
        break;
*/
        case '{':
        if (cur_stage->start->token == ENUM) {
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
            if (!decl->ql.is_pointer) decl->size = 2;
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
                break;
            }

        case STRUCT:
            decl->type_id = TP_STRUCT;
            break;

        case UNION:
            decl->type_id = TP_UNION;
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

static void dbg_print_token(struct token_list* tl) {
    char* p;
    switch (tl->token) {
case AUTO:                      p = "AUTO"; break;
case BREAK:                     p = "BREAK"; break;
case CASE:                      p = "CASE"; break;
case CHAR:                      p = "CHAR"; break;
case CONST:                     p = "CONST"; break;
case CONTINUE:                  p = "CONTINUE"; break;
case DEFAULT:                   p = "DEFAULT"; break;
case DO:                        p = "DO"; break;
case ELSE:                      p = "ELSE"; break;
case ENUM:                      p = "ENUM"; break;
case EXTERN:                    p = "EXTERN"; break;
case FOR:                       p = "FOR"; break;
case GOTO:                      p = "GOTO"; break;
case IF:                        p = "IF"; break;
case INLINE:                    p = "INLINE"; break;
case INT:                       p = "INT"; break;
case LONG:                      p = "LONG"; break;
case REGISTER:                  p = "REGISTER"; break;
case RETURN:                    p = "RETURN"; break;
case SHORT:                     p = "SHORT"; break;
case SIGNED:                    p = "SIGNED"; break;
case SIZEOF:                    p = "SIZEOF"; break;
case STATIC:                    p = "STATIC"; break;
case STRUCT:                    p = "STRUCT"; break;
case SWITCH:                    p = "SWITCH"; break;
case TYPEDEF:                   p = "TYPEDEF"; break;
case UNION:                     p = "UNION"; break;
case UNSIGNED:                  p = "UNSIGNED"; break;
case VOID:                      p = "VOID"; break;
case VOLATILE:                  p = "VOLATILE"; break;
case WHILE:                     p = "WHILE"; break;
case IDEN:                      p = "IDEN"; break;
case DECIMAL_CONSTANT:          p = "DECIMAL_CONSTANT"; break;
case OCTAL_CONSTANT:            p = "OCTAL_CONSTANT"; break;
case HEX_CONSTANT:              p = "HEX_CONSTANT"; break;
case ENUM_CONSTANT:             p = "ENUM_CONSTANT"; break;
case INVALID:                   p = "INVALID"; break;
case C_CHAR:                    p = "C_CHAR"; break;
case S_CHAR:                    p = "S_CHAR"; break;
case TYPEDEF_NAME:              p = "TYPEDEF_NAME"; break;
case LOWER_THAN_ELSE:           p = "LOWER_THAN_ELSE"; break;
case ARROW:                     p = "ARROW"; break;
case INC:                       p = "INC"; break;
case DEC:                       p = "DEC"; break;
case LSHIFT:                    p = "LSHIFT"; break;
case RSHIFT:                    p = "RSHIFT"; break;
case LE:                        p = "LE"; break;
case GE:                        p = "GE"; break;
case EQEQ:                      p = "EQEQ"; break;
case NE:                        p = "NE"; break;
case L_AND:                     p = "L_AND"; break;
case L_OR:                      p = "L_OR"; break;
case DOT3:                      p = "DOT3"; break;
case ASTR_EQ:                   p = "ASTR_EQ"; break;
case DASH_EQ:                   p = "DASH_EQ"; break;
case PERC_EQ:                   p = "PERC_EQ"; break;
case PLUS_EQ:                   p = "PLUS_EQ"; break;
case MINUS_EQ:                  p = "MINUS_EQ"; break;
case LSHIFT_EQ:                 p = "LSHIFT_EQ"; break;
case RSHIFT_EQ:                 p = "RSHIFT_EQ"; break;
case AMP_EQ:                    p = "AMP_EQ"; break;
case HAT_EQ:                    p = "HAT_EQ"; break;
case OR_EQ:                     p = "OR_EQ"; break;

case LBRACKET:                  p = "["; break;
case RBRACKET:                  p = "]"; break;
case LPAR:                      p = "("; break;
case RPAR:                      p = ")"; break;
case LBRACE:                    p = "{"; break;
case RBRACE:                    p = "}"; break;
case DOT:                       p = "."; break;
case AMP:                       p = "&"; break;
case ASTR:                      p = "*"; break;
case PLUS:                      p = "+"; break;
case MINUS:                     p = "-"; break;
case TILDA:                     p = "~"; break;
case EXQL:                      p = "!"; break;
case DASH:                      p = "/"; break;
case PERCENT:                   p = "%"; break;
case LT:                        p = "<"; break;
case GT:                        p = ">"; break;
case HAT:                       p = "^"; break;
case OR:                        p = "|"; break;
case QUESTION:                  p = "?"; break;
case COLON:                     p = ":"; break;
case SEMI_COLON:                p = ";"; break;
case EQ:                        p = "="; break;
case COMMA:                     p = ","; break;
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
    init_utils();
    init_symbols();

    root_code_block = create_code_block();
    root_code_block->types = alloc_typedef();
    enter_parse_stage(START_TOKEN);
    cur_stage->cb = root_code_block;
}

void exit_parser(void) {
    struct parse_stage *stg, *tmp1;
    struct token_list *tk, *tmp2;

    printf("deleting stages\n");
    DL_FOREACH_SAFE(head_stage, stg, tmp1) {
        printf(".");
        LL_DELETE(head_stage, stg);
        ker_free(stg);
    }
    printf("\n");
    printf("deleting tokens\n");
    DL_FOREACH_SAFE(token_list_head, tk, tmp2) {
        printf(".");
        LL_DELETE(token_list_head, tk);
        if (tk) free_token(tk);
    }
    printf("\n");
    free_code_block(root_code_block);
    exit_utils();
}
