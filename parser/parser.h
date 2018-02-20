
#ifndef __parser_h__
#define __parser_h__

int return_token(const char* parse_text, int token_num);
int check_symbol_type(void);

void init_parser(void);

extern int line_num;

void enter_parse_stage(int stage);
void exit_parse_stage(void);
void line_break(void);


#endif /*__parser_h__*/

