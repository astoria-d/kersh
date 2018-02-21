
#ifndef __parser_h__
#define __parser_h__

int return_token(const char* parse_text, int token_num);
int check_symbol_type(void);

void init_parser(void);

extern int line_num;

void enter_parse_stage(int stage);
void exit_parse_stage(void);
void line_break(void);
void set_enum_index(int next_index);
int get_const_val(void);
void print_token(const char* parse_text);
void indent_inc(void);
void indent_dec(void);


#endif /*__parser_h__*/

