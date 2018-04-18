
#include <stdio.h>
#include "kersh.tab.h"
#include "util.h"
#include "parser.h"
#include "utlist.h"
#include "symbol.h"
#include "code.h"

static struct ctoken* alloc_token(void);

static unsigned int line_num;
static unsigned int enum_decl_follow;
static unsigned int enum_index;
static struct ctoken* token_list_head;

/*kersh implementations...*/

/*check input token is identifier or enum constant or typedef name*/
int check_token_type(const char* parse_text) {
    struct symbol* sym;

    /*case "enum" and "{" comes,*/
    if (enum_decl_follow == 2) return ENUM_CONSTANT;
    sym = lookup_symbol(parse_text);
    if (sym == NULL) return IDEN;
    if (sym->symbol_type == SYM_TYPEDEF) return TYPEDEF_NAME;
    return IDEN;
}

void remove_token(struct ctoken* tk) {
    LL_DELETE(token_list_head, tk);
}

void pre_shift_token(const char* parse_text, int token_num) {
    unsigned long const_int_val;
    struct ctoken* tk;

    tk = alloc_token();
    tk->token = token_num;
    LL_APPEND(token_list_head, tk);

    /*set token object.*/
    yylval.tk = tk;

    if (token_num == '}') {
        indent_dec();
    }
    print_token(parse_text);

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

        case ENUM:
        enum_decl_follow++;
        break;

        case '{':
        enum_decl_follow++;
        line_break();
        indent_inc(); 
        break;

        case STRUCT:
        case UNION:
        case '}':
        case ';':
            enum_decl_follow = 0;
        case ':':
            line_break();
        break;
    }
}

enum OP_TYPE get_exp_op(struct ctoken* tk) {
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

static struct ctoken* alloc_token(void) {
    struct ctoken* tk;
    tk = ker_malloc(sizeof(struct ctoken));
    return tk;
}

struct ctoken* alloc_null_attr(void) {
    struct ctoken* tk;
    tk = ker_malloc(sizeof(struct ctoken));
    tk->token = NULL_ATTR;
    return tk;
}

void free_token(struct ctoken* tkn) {
    //printf("delete token ");
    //dbg_print_token(tkn);
    if (tkn->token == IDEN || tkn->token == ENUM_CONSTANT || tkn->token == TYPEDEF_NAME) {
        ker_free(tkn->strval);
    }
    ker_free(tkn);
}

#define CASE_BREAK(token)\
    case token:                      p = #token; break;

static void print_err_token(struct ctoken* tl) {
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
    fprintf (stderr, "token = [%s]\n", (tl->token == IDEN || tl->token == ENUM_CONSTANT) ? tl->strval : p);

}

/*bison required functions...*/
int yywrap (void ) {
    return 1;
}

void yyerror (char const *s) {
    struct ctoken* tk;

    tk = token_list_head;
    while (tk->next) {
        tk = tk->next;
    }

    fprintf (stderr, "line: %d ", line_num);
    print_err_token(tk);
    fprintf (stderr, "message: %s\n", s);
}

void line_inc(void) {
    line_num++;
}

void init_parser(void) {
    yydebug = 0;
    line_num = 1;
    enum_decl_follow = 0;
    token_list_head = NULL;
}

void exit_parser(void) {
    struct ctoken *tk, *tmp2;

    printf("clean up remaining tokens.\n");
    LL_FOREACH_SAFE(token_list_head, tk, tmp2) {
        printf("*");
        LL_DELETE(token_list_head, tk);
        if (tk) free_token(tk);
    }
    printf("\n");
}
