
#ifndef __parser_h__
#define __parser_h__

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

void pre_shift_token(const char* parse_text, int token_num);
int check_token_type(void);
void enter_parse_stage(int stage);
void exit_parse_stage(void);
void free_identifer(void);

int get_current_stage(void);
int get_const_val(void);
char* get_old_identifer(void);
int get_enum_index();
void set_enum_index(int val);

void line_break(void);
void indent_inc(void);
void indent_dec(void);

void init_parser(void);
void exit_parser(void);

#endif /*__parser_h__*/

