
#include <stdio.h>

#include "kersh.tab.h"
#include "kersh.h"

int line_num;

void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
}


int yywrap (void )
{
    return 1;
}

void init_values(void) {
    yydebug = 0;
    line_num = 1;
}
