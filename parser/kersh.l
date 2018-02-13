%{
#include "kersh.h"
#include "kersh.tab.h"

#if 0
#define     pret(name)    {   printf( "lex: " #name " %s	\n", yytext);   return(name);  }
#else
#define     pret(name)    {   printf( "%s ", yytext);   return(name);  }
#endif

%}

nondigit            [_a-zA-Z]
digit               [0-9]
nonzerodigit        [1-9]
octaldigit          [0-7]
hexdigit            [a-fA-F0-9]
cchar               [^\'\\\n]
schar               [^\"\\\n]
simple_escape       \\['"\\abfnrtv]
octal_escape        \\{octaldigit}{octaldigit}?{octaldigit}?
hex_escape          \\x{hexdigit}*

%%
[ \t\r]+      ; /*ignore white spaces...*/
\n          {   line_num++;     }

 /*keywords*/

"typedef"   pret(TYPEDEF)
"sizeof"    pret(SIZEOF)
"enum"      pret(ENUM)
"struct"    pret(STRUCT)
"union"     pret(UNION)

"auto"      pret(AUTO)
"const"     pret(CONST)
"static"    pret(STATIC)
"extern"    pret(EXTERN)
"volatile"  pret(VOLATILE)

"inline"    pret(INLINE)

"do"        pret(DO)
"while"     pret(WHILE)
"for"       pret(FOR)
"continue"  pret(CONTINUE)
"break"     pret(BREAK)

"goto"      pret(GOTO)
"return"    pret(RETURN)

"switch"    pret(SWITCH)
"case"      pret(CASE)
"default"   pret(DEFAULT)

"if"        pret(IF)
"else"      pret(ELSE)


"void"      pret(VOID)
"int"       pret(INT)
"char"      pret(CHAR)
"short"     pret(SHORT)
"long"      pret(LONG)
"signed"    pret(SIGNED)
"unsigned"  pret(UNSIGNED)


{nondigit}({nondigit}|{digit})*     {
                                        if (1) pret(IDEN)
                                        pret(ENUM_CONSTANT) /*TODO!!! must work to check if identifier is enum or not.*/
                                        pret(TYPEDEF_NAME) /*TODO!!! must work to check if identifier is typedef name.*/
                                    }

{nonzerodigit}{digit}*(u|U)?(l|L|ll|LL)?       pret(DECIMAL_CONSTANT)
{nonzerodigit}{digit}*(l|L|ll|LL)?(u|U)?       pret(DECIMAL_CONSTANT)

0{octaldigit}*(u|U)?(l|L|ll|LL)?              pret(OCTAL_CONSTANT)
0{octaldigit}*(l|L|ll|LL)?(u|U)?              pret(OCTAL_CONSTANT)

0[xX]{hexdigit}*(u|U)?(l|L|ll|LL)?            pret(HEX_CONSTANT)
0[xX]{hexdigit}*(l|L|ll|LL)?(u|U)?            pret(HEX_CONSTANT)

\'({cchar}|{simple_escape}|{octal_escape}|{hex_escape})*\'          pret(C_CHAR)


\"({schar}|{simple_escape}|{octal_escape}|{hex_escape})*\"          pret(S_CHAR)




"["         pret(LBRACKET)
"]"         pret(RBRACKET)
"("         pret(LPAR)
")"         pret(RPAR)
"{"         pret(LBRACE)
"}"         pret(RBRACE)
"."         pret(DOT)
"->"        pret(ARROW)


"++"        pret(INC)
"--"        pret(DEC)
"&"         pret(AMP)
"*"         pret(ASTR)
"+"         pret(PLUS)
"-"         pret(MINUS)
"~"         pret(TILDA)
"!"         pret(EXQL)


"/"         pret(DASH)
"%"         pret(PERCENT)
"<<"        pret(LSHIFT)
">>"        pret(RSHIFT)
"<"         pret(LT)
">"         pret(GT)
"<="        pret(LE)
">="        pret(GE)
"=="        pret(EQEQ)
"!="        pret(NE)
"^"         pret(HAT)
"|"         pret(OR)
"&&"        pret(L_AND)
"||"        pret(L_OR)


"?"         pret(QUESTION)
":"         pret(COLON)
";"         pret(SEMI_COLON)
"..."       pret(DOT3)


"="         pret(EQ)
"*="        pret(ASTR_EQ)
"/="        pret(DASH_EQ)
"%="        pret(PERC_EQ)
"+="        pret(PLUS_EQ)
"-="        pret(MINUS_EQ)
"<<="       pret(LSHIFT_EQ)
">>="       pret(RSHIFT_EQ)
"&="        pret(AMP_EQ)
"^="        pret(HAT_EQ)
"|="        pret(OR_EQ)


","         pret(COMMA)


 /*error case...*/

{digit}*{nondigit}*     {   printf(" invalid token [%s]\n", yytext);   return INVALID;  }
.                       {   printf(" invalid token [%s]\n", yytext);   return INVALID;  }

%%


int main2(int argc, char* argv[]) {
    return yylex();
}

