
#include <stdio.h>
#include <string.h>


#include "kersh.tab.h"
#include "kersh.h"

int line_num;

void yyerror (char const *s) {
    fprintf (stderr, "line: %d,\n   %s\n", line_num, s);
}


int yywrap (void )
{
    return 1;
}

void init_values(void) {
    yydebug = 0;
    line_num = 1;
}


