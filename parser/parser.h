
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
int check_token_type(const char* parse_text);
void enter_parse_stage(int stage);
void exit_parse_stage(void);

struct type_definition* lookup_declaration(void);
struct type_definition* consume_function(void);

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

