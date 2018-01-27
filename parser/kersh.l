%{
#include "kersh.h"
#include "kersh.tab.h"
%}



%%
[ \t\r]+      ; /*ignore white spaces...*/
\n          {   line_num++;     }


"typedef"   {   printf("%s ", yytext);     return(TYPEDEF);     }
"sizeof"    {   printf("%s ", yytext);     return(SIZEOF);      }
"enum"      {   printf("%s ", yytext);     return(ENUM);        }
"struct"    {   printf("%s ", yytext);     return(STRUCT);      }
"union"     {   printf("%s ", yytext);     return(UNION);       }

"const"     {   printf("%s ", yytext);     return(CONST);       }
"static"    {   printf("%s ", yytext);     return(STATIC);      }
"extern"    {   printf("%s ", yytext);     return(EXTERN);      }
"volatile"  {   printf("%s ", yytext);     return(VOLATILE);    }

"inline"    {   printf("%s ", yytext);     return(INLINE);      }

"do"        {   printf("%s ", yytext);     return(DO);          }
"while"     {   printf("%s ", yytext);     return(WHILE);       }
"for"       {   printf("%s ", yytext);     return(FOR);         }
"continue"  {   printf("%s ", yytext);     return(CONTINUE);    }
"break"     {   printf("%s ", yytext);     return(BREAK);       }

"goto"      {   printf("%s ", yytext);     return(GOTO);        }
"return"    {   printf("%s ", yytext);     return(RETURN);      }

"switch"    {   printf("%s ", yytext);     return(SWITCH);      }
"case"      {   printf("%s ", yytext);     return(CASE);        }
"default"   {   printf("%s ", yytext);     return(DEFAULT);     }

"if"        {   printf("%s ", yytext);     return(IF);          }
"else"      {   printf("%s ", yytext);     return(ELSE);        }


"void"      {   printf("%s ", yytext);     return(VOID);        }
"int"       {   printf("%s ", yytext);     return(INT);         }
"char"      {   printf("%s ", yytext);     return(CHAR);        }
"short"     {   printf("%s ", yytext);     return(SHORT);       }
"long"      {   printf("%s ", yytext);     return(LONG);        }
"signed"    {   printf("%s ", yytext);     return(SIGN);        }
"unsigned"  {   printf("%s ", yytext);     return(SIGN);        }

"+"         {   printf("%s ", yytext);     return(OPE_2);   }
"-"         {   printf("%s ", yytext);     return(OPE_2);   }
"*"         {   printf("%s ", yytext);     return(ASTR);    }
"/"         {   printf("%s ", yytext);     return(OPE_2);   }
"%"         {   printf("%s ", yytext);     return(OPE_2);   }
"&"         {   printf("%s ", yytext);     return(OPE_2);   }
"|"         {   printf("%s ", yytext);     return(OPE_2);   }
"~"         {   printf("%s ", yytext);     return(OPE_2);   }
"^"         {   printf("%s ", yytext);     return(OPE_2);   }
"<<"        {   printf("%s ", yytext);     return(OPE_2);   }
">>"        {   printf("%s ", yytext);     return(OPE_2);   }
"=="        {   printf("%s ", yytext);     return(OPE_2);   }
"!="        {   printf("%s ", yytext);     return(OPE_2);   }
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
"^="        {   printf("%s ", yytext);     return(OPE_ASIGN);   }
"<<="       {   printf("%s ", yytext);     return(OPE_ASIGN);   }
">>="       {   printf("%s ", yytext);     return(OPE_ASIGN);   }

"->"        {   printf("%s ", yytext);     return(OPE_ARROW);   }

"("         {   printf("%s ", yytext);     return(LPAR);   }
")"         {   printf("%s ", yytext);     return(RPAR);   }
"{"         {   printf("%s ", yytext);     return(LBRACE);   }
"}"         {   printf("%s ", yytext);     return(RBRACE);   }
"["         {   printf("%s ", yytext);     return(LBRACKET);   }
"]"         {   printf("%s ", yytext);     return(RBRACKET);   }


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

