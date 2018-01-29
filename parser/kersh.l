%{
#include "kersh.h"
#include "kersh.tab.h"

#define     pret(name)    {   printf("%s ", yytext);     return(name);     }

%}

nondigit            [_a-zA-Z]
digit               [0-9]
nonzerodigit        [1-9]
octaldigit          [0-7]
hexdigit            [a-fA-F0-9]

%%
[ \t\r]+      ; /*ignore white spaces...*/
\n          {   line_num++;     }

 /*keywords*/

"typedef"   pret(TYPEDEF)
"sizeof"    pret(SIZEOF)
"enum"      pret(ENUM)
"struct"    pret(STRUCT)
"union"     pret(UNION)

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


 /*
"+"         |
"-"         |
"*"         |
"/"         |
"%"         |
"&"         |
"|"         |
"~"         |
"^"         |
"<<"        |
">>"        |
"=="        |
"!="        |
">"         |
">+"        |
"<"         |
"<="        pret(OPE_2)

"++"        |
"--"        pret(OPE_INC)

"="         |
"+="        |
"-="        |
"*="        |
"/="        |
"&="        |
"|="        |
"^="        |
"<<="       |
">>="       pret(OPE_ASIGN)

"->"        pret(OPE_ARROW)

"("         pret(LPAR)
")"         pret(RPAR)
"{"         pret(LBRACE)
"}"         pret(RBRACE)
"["         pret(LBRACKET)
"]"         pret(RBRACKET)


"."         pret(DOT)
","         pret(COMMA)
"?"         pret(QUESTION)
":"         pret(COLON)
";"         pret(SEMI_COLON)
 */

{nondigit}({nondigit}|{digit})*     {
                                        if (1) pret(IDENTIFIER)
                                        else pret(ENUM_CONSTANT) /*TODO!!! must work to check if identifier is enum or not.*/
                                    }

 /*
 universal character name
 \u0011 \uxxxx etc. not supported...
 */

{nonzerodigit}{digit}*(u|U)?(l|L|ll|LL)?       pret(DECIMAL_CONSTANT)
{nonzerodigit}{digit}*(l|L|ll|LL)?(u|U)?       pret(DECIMAL_CONSTANT)

0{octaldigit}*              pret(OCTAL_CONSTANT)

0[xX]{hexdigit}*            pret(HEX_CONSTANT)

\'[^\'\\\n]\'                    pret(C_CHAR)

\'\\['"\\abfnrtv]\'   pret(ESCAPE_SEQ)

 /*octal escape seq*/
\'\\{octaldigit}{octaldigit}?{octaldigit}?\'    pret(ESCAPE_SEQ)

 /*hex escape seq*/
\'\\x{hexdigit}*\'                             pret(ESCAPE_SEQ)


 /*error case...*/

{digit}*{nondigit}*          pret(INVALID)
.                           pret(INVALID)

%%


int main2(int argc, char* argv[]) {
    return yylex();
}

