%{
#include "kersh.h"
#include "kersh.tab.h"
%}



%%
[ \t\r]+      ; /*ignore white spaces...*/
\n          {   line_num++;     }


"int"       {   printf("%s ", yytext);     return(INT);         }
"char"      {   printf("%s ", yytext);     return(CHAR);        }
"short"     {   printf("%s ", yytext);     return(SHORT);       }
"long"      {   printf("%s ", yytext);     return(LONG);        }
"signed"    {   printf("%s ", yytext);     return(SIGNED);      }
"unsigned"  {   printf("%s ", yytext);     return(UNSIGNED);    }

"+"         {   printf("%s ", yytext);     return(OPE_2);   }
"-"         {   printf("%s ", yytext);     return(OPE_2);   }
"*"         {   printf("%s ", yytext);     return(OPE_2);   }
"/"         {   printf("%s ", yytext);     return(OPE_2);   }
"&"         {   printf("%s ", yytext);     return(OPE_2);   }
"|"         {   printf("%s ", yytext);     return(OPE_2);   }
"<<"        {   printf("%s ", yytext);     return(OPE_2);   }
">>"        {   printf("%s ", yytext);     return(OPE_2);   }
"=="        {   printf("%s ", yytext);     return(OPE_2);   }
">"         {   printf("%s ", yytext);     return(OPE_2);   }
">+"        {   printf("%s ", yytext);     return(OPE_2);   }
"<"         {   printf("%s ", yytext);     return(OPE_2);   }
"<="        {   printf("%s ", yytext);     return(OPE_2);   }

"++"        {   printf("%s ", yytext);     return(OPE_INC);   }
"--"        {   printf("%s ", yytext);     return(OPE_INC);   }

"="         {   printf("%s ", yytext);     return(OPE_ASIGN);   }
"+="        {   printf("%s ", yytext);     return(OPE_ASIGN);   }
"-="        {   printf("%s ", yytext);     return(OPE_ASIGN);   }
"*="        {   printf("%s ", yytext);     return(OPE_ASIGN);   }
"/="        {   printf("%s ", yytext);     return(OPE_ASIGN);   }
"&="        {   printf("%s ", yytext);     return(OPE_ASIGN);   }
"|="        {   printf("%s ", yytext);     return(OPE_ASIGN);   }

"->"        {   printf("%s ", yytext);     return(OPE_ARROW);   }

"("         {   printf("%s ", yytext);     return(LPAR);   }
")"         {   printf("%s ", yytext);     return(RPAR);   }
"."         {   printf("%s ", yytext);     return(DOT);   }
","         {   printf("%s ", yytext);     return(COMMA);   }
"?"         {   printf("%s ", yytext);     return(QUESTION);   }
":"         {   printf("%s ", yytext);     return(COLON);   }
";"         {   printf("%s ", yytext);     return(SEMI_COLON);   }

[1-9][0-9]*      {   printf("%s ", yytext);     /*yylval.ival = atoi(yytext);*/     return(INT); }
"0"         {   printf("%s ", yytext);     return(INT); }

[a-zA-Z_]([a-zA-Z_]|[0-9])*      {   printf("%s ", yytext);     /*yylval = atoi(yytext);*/     return(VAR); }

%%


int main2(int argc, char* argv[]) {
    return yylex();
}

