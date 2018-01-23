%{
#include "kersh.h"
#include "kersh.tab.h"
%}



%%
[ \t\r]+      ; /*ignore white spaces...*/
\n          {   line_num++;     }


"int"         {   printf("decl\n");     return(DECL_INT);   }

"+"         {   printf("plus\n");           return(OPE_PLUS);   }
"-"         {   printf("minus\n");          return(OPE_MINUS);   }
"*"         {   printf("mul\n");            return(OPE_MUL);   }
"/"         {   printf("div\n");            return(OPE_DIV);   }
"&"         {   printf("and\n");            return(OPE_AND);   }
"|"         {   printf("or\n");             return(OPE_OR);   }
"<<"        {   printf("lshift\n");         return(OPE_LS);   }
">>"        {   printf("rshift\n");         return(OPE_RS);   }

"=="        {   printf("eq\n");             return(OPE_EQ);   }
">"         {   printf("gr\n");             return(OPE_GR);   }
">+"        {   printf("gt\n");             return(OPE_GT);   }
"<"         {   printf("ls\n");             return(OPE_LR);   }
"<="        {   printf("lt\n");             return(OPE_LT);   }

"++"        {   printf("inc\n");            return(OPE_INC);   }
"--"        {   printf("dec\n");            return(OPE_DEC);   }

"="         {   printf("asign\n");          return(OPE_ASIGN);   }
"+="        {   printf("pasign\n");         return(OPE_P_ASIGN);   }
"-="        {   printf("masign\n");         return(OPE_M_ASIGN);   }
"*="        {   printf("mulasign\n");       return(OPE_ML_ASIGN);   }
"/="        {   printf("divasign\n");       return(OPE_D_ASIGN);   }
"&="        {   printf("andasign\n");       return(OPE_A_ASIGN);   }
"|="        {   printf("orasign\n");        return(OPE_O_ASIGN);   }

"->"        {   printf("arrow\n");          return(OPE_ARROW);   }

"("         {   printf("lpar\n");            return(LPAR);   }
")"         {   printf("rpar\n");            return(RPAR);   }
"."         {   printf("dot\n");            return(DOT);   }
"?"         {   printf("ques\n");           return(QUESTION);   }
":"         {   printf("col\n");            return(COLON);   }
";"         {   printf("semicol\n");        return(SEMI_COLON);   }

[1-9][0-9]*      {   printf("int\n");       /*yylval.ival = atoi(yytext);*/     return(INT); }

[a-zA-Z_]([a-zA-Z_]|[0-9])*      {   printf("variable\n");       /*yylval = atoi(yytext);*/     return(VAR); }

%%


int main2(int argc, char* argv[]) {
    return yylex();
}

