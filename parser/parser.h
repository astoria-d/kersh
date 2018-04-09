
#ifndef __parser_h__
#define __parser_h__

#include "kersh.tab.h"

#define     LBRACKET    '['
#define     RBRACKET    ']'
#define     LPAR        '('
#define     RPAR        ')'
#define     LBRACE      '{'
#define     RBRACE      '}'
#define     DOT         '.'
#define     AMP         '&'
#define     ASTR        '*'
#define     PLUS        '+'
#define     MINUS       '-'
#define     TILDA       '~'
#define     EXQL        '!'
#define     DASH        '/'
#define     PERCENT     '%'
#define     LT          '<'
#define     GT          '>'
#define     HAT         '^'
#define     OR          '|'
#define     QUESTION    '?'
#define     COLON       ':'
#define     SEMI_COLON  ';'
#define     EQ          '='
#define     COMMA       ','

#define tk_enum(enum_entry) tk_##enum_entry = enum_entry,
enum tk_type {
tk_enum(LBRACKET)
tk_enum(RBRACKET)
tk_enum(LPAR)
tk_enum(RPAR)
tk_enum(LBRACE)
tk_enum(RBRACE)
tk_enum(DOT)
tk_enum(AMP)
tk_enum(ASTR)
tk_enum(PLUS)
tk_enum(MINUS)
tk_enum(TILDA)
tk_enum(EXQL)
tk_enum(DASH)
tk_enum(PERCENT)
tk_enum(LT)
tk_enum(GT)
tk_enum(HAT)
tk_enum(OR)
tk_enum(QUESTION)
tk_enum(COLON)
tk_enum(SEMI_COLON)
tk_enum(EQ)
tk_enum(COMMA)
tk_enum(AUTO)
tk_enum(BREAK)
tk_enum(CASE)
tk_enum(CHAR)
tk_enum(CONST)
tk_enum(CONTINUE)
tk_enum(DEFAULT)
tk_enum(DO)
tk_enum(ELSE)
tk_enum(ENUM)
tk_enum(EXTERN)
tk_enum(FOR)
tk_enum(GOTO)
tk_enum(IF)
tk_enum(INLINE)
tk_enum(INT)
tk_enum(LONG)
tk_enum(REGISTER)
tk_enum(RETURN)
tk_enum(SHORT)
tk_enum(SIGNED)
tk_enum(SIZEOF)
tk_enum(STATIC)
tk_enum(STRUCT)
tk_enum(SWITCH)
tk_enum(TYPEDEF)
tk_enum(UNION)
tk_enum(UNSIGNED)
tk_enum(VOID)
tk_enum(VOLATILE)
tk_enum(WHILE)
tk_enum(IDEN)
tk_enum(DECIMAL_CONSTANT)
tk_enum(OCTAL_CONSTANT)
tk_enum(HEX_CONSTANT)
tk_enum(ENUM_CONSTANT)
tk_enum(INVALID)
tk_enum(C_CHAR)
tk_enum(S_CHAR)
tk_enum(TYPEDEF_NAME)
tk_enum(LOWER_THAN_ELSE)
tk_enum(ARROW)
tk_enum(INC)
tk_enum(DEC)
tk_enum(LSHIFT)
tk_enum(RSHIFT)
tk_enum(LE)
tk_enum(GE)
tk_enum(EQEQ)
tk_enum(NE)
tk_enum(L_AND)
tk_enum(L_OR)
tk_enum(DOT3)
tk_enum(ASTR_EQ)
tk_enum(DASH_EQ)
tk_enum(PERC_EQ)
tk_enum(PLUS_EQ)
tk_enum(MINUS_EQ)
tk_enum(LSHIFT_EQ)
tk_enum(RSHIFT_EQ)
tk_enum(AMP_EQ)
tk_enum(HAT_EQ)
tk_enum(OR_EQ)
tk_enum(ATTRIBUTE)
};

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


void pre_shift_token(const char* parse_text, int token_num);
int check_token_type(const char* parse_text);
void enter_parse_stage(int stage);
void exit_parse_stage(void);

struct type_definition* consume_declaration(void);
struct type_definition* consume_function(void);

struct token_list* pop_token_tail(void);
void push_token_tail(struct token_list* tk);

int get_current_stage(void);
struct code_block* get_current_cb(void);
struct type_definition* get_current_td(void);
int get_const_val(void);
char* get_old_identifer(void);

int get_enum_index();
void set_enum_index(int val);

int get_decl_handled(void);
void set_decl_handled(int val);

void line_break(void);
void indent_inc(void);
void indent_dec(void);
void line_inc(void);
unsigned int get_line_num();

void init_semantic_check(void);
void semantic_err(const char* msg);

void init_parser(void);
void exit_parser(void);

#endif /*__parser_h__*/

