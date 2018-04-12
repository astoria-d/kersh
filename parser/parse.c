
#include <stdio.h>
#include "kersh.tab.h"
#include "util.h"
#include "parser.h"
#include "symbol.h"
#include "utlist.h"
#include "util.h"

static void print_token(const char* parse_text);
static struct token_list* alloc_token(void);
static void dbg_print_token(struct token_list* tl);

static unsigned int pr_indent;
static unsigned int pr_newline;
static unsigned int enum_index;

static struct token_list* token_list_head;

/*kersh implementations...*/

/*check input token is identifier or enum constant or typedef name*/
int check_token_type(const char* parse_text) {
    return IDEN;
}

void pre_shift_token(const char* parse_text, int token_num) {
    unsigned long const_int_val;
    int create_block;

    if (token_num == '}') {
        indent_dec(); 
    }
    print_token(parse_text);

    struct token_list* tk;
    tk = alloc_token();
    tk->token = token_num;
    DL_APPEND(token_list_head, tk);

    /*set token object.*/
    yylval.tk = tk;

    switch (token_num) {
        case IDEN:
        case TYPEDEF_NAME:
        tk->strval = ker_strdup(parse_text);
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

        case C_CHAR:
        sscanf(parse_text, "%c", &const_int_val);
        tk->lval = const_int_val;
        break;

        case '{':
        line_break();
        indent_inc(); 
        break;

        case '}':
        case ';':
        case ':':
        line_break();
        break;
    }
}
enum OP_TYPE get_exp_op(struct token_list* tk) {
    switch (tk->token) {
    case '='        : return OP_EQ         ;
    case ASTR_EQ    : return OP_ASTR_EQ    ;
    case DASH_EQ    : return OP_DASH_EQ    ;
    case PERC_EQ    : return OP_PERC_EQ    ;
    case PLUS_EQ    : return OP_PLUS_EQ    ;
    case MINUS_EQ   : return OP_MINUS_EQ   ;
    case LSHIFT_EQ  : return OP_LSHIFT_EQ  ;
    case RSHIFT_EQ  : return OP_RSHIFT_EQ  ;
    case AMP_EQ     : return OP_AMP_EQ     ;
    case HAT_EQ     : return OP_HAT_EQ     ;
    case OR_EQ      : return OP_OR_EQ      ;
    default         : return OP_INVALID    ;
    }
}

static struct token_list* alloc_token(void) {
    struct token_list* tk;
    tk = ker_malloc(sizeof(struct token_list));
    return tk;
}

void free_token(struct token_list* tkn) {
    //printf("delete token ");
    //dbg_print_token(tkn);
    if (tkn->token == IDEN || tkn->token == ENUM_CONSTANT || tkn->token == TYPEDEF_NAME) {
        ker_free(tkn->strval);
    }
    ker_free(tkn);
}


/* print utilities....*/

void indent_inc(void) {
    pr_indent++;
}

void indent_dec(void) {
    pr_indent--;
}

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
    token_list_head = NULL;
    pr_indent = 0;
    pr_newline = 0;
    init_utils();
    init_symbols();
}

void exit_parser(void) {
    struct token_list *tk, *tmp2;

    printf("clean up remaining tokens.\n");
    DL_FOREACH_SAFE(token_list_head, tk, tmp2) {
        printf("*");
        DL_DELETE(token_list_head, tk);
        if (tk) free_token(tk);
    }
    printf("\n");
    exit_utils();
}
