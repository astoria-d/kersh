
#ifndef __kersh_h__
#define __kersh_h__

int yylex (void);
void yyerror (char const *s);

void init_values(void);

int line_num;

#endif

