
#ifndef __kersh_h__
#define __kersh_h__

int yylex (void);
void yyerror (char const *s);
int return_token(const char* parse_text, int token_num);
int check_symbol_type(void);

void init_parser(void);

extern int line_num;

void enter_parse_stage(int stage);
void exit_parse_stage(void);



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


#endif

