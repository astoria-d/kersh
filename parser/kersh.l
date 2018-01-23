%{
#include "kersh.h"
#include "kersh.tab.h"
%}



%%
[ \t\r]+      ; /*ignore white spaces...*/
\n          {   line_num++;     }

"+"         {   printf("plus\n");      return(MATH_OPE);   }
"-"         {   printf("minus\n");     return(MATH_OPE);   }
"*"         {   printf("mul\n");       return(MATH_OPE);   }
"/"         {   printf("div\n");       return(MATH_OPE);   }
"&"         {   printf("and\n");       return(MATH_OPE);   }
"|"         {   printf("or\n");       return(MATH_OPE);   }
"<<"        {   printf("lshift\n");       return(MATH_OPE);   }
">>"        {   printf("rshift\n");       return(MATH_OPE);   }
"=="        {   printf("eq\n");       return(MATH_OPE);   }

"++"        {   printf("inc\n");      return(INC_OPE);   }
"--"        {   printf("dec\n");     return(INC_OPE);   }

"="         {   printf("asign\n");       return(ASIGN_OPE);   }
"+="        {   printf("pasign\n");       return(ASIGN_OPE);   }
"-="        {   printf("masign\n");       return(ASIGN_OPE);   }
"*="        {   printf("mulasign\n");       return(ASIGN_OPE);   }
"/="        {   printf("divasign\n");       return(ASIGN_OPE);   }
"&="        {   printf("andasign\n");       return(ASIGN_OPE);   }
"|="        {   printf("orasign\n");       return(ASIGN_OPE);   }

"->"        {   printf("arrow\n");       return(ARROW_OPE);   }

"."         {   printf("dot\n");       return(DOT);   }
"?"         {   printf("ques\n");       return(QUESTION);   }
":"         {   printf("col\n");       return(COLON);   }
";"         {   printf("semicol\n");       return(SEMI_COLON);   }

[1-9][0-9]*      {   printf("non-zero num\n");       yylval = atoi(yytext);     return(INT); }

[a-zA-Z_]([a-zA-Z_]|[0-9])*      {   printf("variable\n");       yylval = atoi(yytext);     return(VAR); }

%%


int main2(int argc, char* argv[]) {
    return yylex();
}

