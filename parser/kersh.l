%{
#include "kersh.h"
#include "kersh.tab.h"
#include "parser.h"

#define     rtoken(name)    {pre_shift_token(yytext, name); return name;}
/*
#define     rtoken(name)    printf( "lex: " #name " %s	\n", yytext);   return(name)
*/
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

gcc_line_num        ^'#' *[^\n]*

%%
[ \t\r]+      ; /*ignore white spaces...*/
\n          {   line_num++;     }

 /* gcc preprocessor outputs line number. skip it.*/
#[^\n]*          {   /*printf("gcc line num [%s]..\n", yytext);*/}


 /*keywords*/

"typedef"   { rtoken(TYPEDEF); }
"sizeof"    { rtoken(SIZEOF); }
"enum"      { rtoken(ENUM);   }
"struct"    { rtoken(STRUCT); }
"union"     { rtoken(UNION); }

"auto"      { rtoken(AUTO); }
"const"     { rtoken(CONST); }
"static"    { rtoken(STATIC); }
"extern"    { rtoken(EXTERN); }
"volatile"  { rtoken(VOLATILE); }

"inline"    { rtoken(INLINE); }

"do"        { rtoken(DO); }
"while"     { rtoken(WHILE); }
"for"       { rtoken(FOR); }
"continue"  { rtoken(CONTINUE); }
"break"     { rtoken(BREAK); }

"goto"      { rtoken(GOTO); }
"return"    { rtoken(RETURN); }

"switch"    { rtoken(SWITCH); }
"case"      { rtoken(CASE); }
"default"   { rtoken(DEFAULT); }

"if"        { rtoken(IF); }
"else"      { rtoken(ELSE); }


"void"      { rtoken(VOID); }
"int"       { rtoken(INT); }
"char"      { rtoken(CHAR); }
"short"     { rtoken(SHORT); }
"long"      { rtoken(LONG); }
"signed"    { rtoken(SIGNED); }
"unsigned"  { rtoken(UNSIGNED); }


{nondigit}({nondigit}|{digit})*     {   /*identifier or enum or typename*/
                                        int token = check_symbol_type();
                                        rtoken(token);
                                    }

{nonzerodigit}{digit}*(u|U)?(l|L|ll|LL)?       { rtoken(DECIMAL_CONSTANT); }
{nonzerodigit}{digit}*(l|L|ll|LL)?(u|U)?       { rtoken(DECIMAL_CONSTANT); }

0{octaldigit}*(u|U)?(l|L|ll|LL)?              { rtoken(OCTAL_CONSTANT); }
0{octaldigit}*(l|L|ll|LL)?(u|U)?              { rtoken(OCTAL_CONSTANT); }

0[xX]{hexdigit}*(u|U)?(l|L|ll|LL)?            { rtoken(HEX_CONSTANT); }
0[xX]{hexdigit}*(l|L|ll|LL)?(u|U)?            { rtoken(HEX_CONSTANT); }

\'({cchar}|{simple_escape}|{octal_escape}|{hex_escape})*\'          { rtoken(C_CHAR); }


\"({schar}|{simple_escape}|{octal_escape}|{hex_escape})*\"          { rtoken(S_CHAR); }




"["         { rtoken(LBRACKET); }
"]"         { rtoken(RBRACKET); }
"("         { rtoken(LPAR); }
")"         { rtoken(RPAR); }
"{"         { pre_shift_token(yytext, LBRACE); line_break(); indent_inc(); return LBRACE; }
"}"         { indent_dec(); rtoken(RBRACE); }
"."         { rtoken(DOT); }
"->"        { rtoken(ARROW); }


"++"        { rtoken(INC); }
"--"        { rtoken(DEC); }
"&"         { rtoken(AMP); }
"*"         { rtoken(ASTR); }
"+"         { rtoken(PLUS); }
"-"         { rtoken(MINUS); }
"~"         { rtoken(TILDA); }
"!"         { rtoken(EXQL); }


"/"         { rtoken(DASH); }
"%"         { rtoken(PERCENT); }
"<<"        { rtoken(LSHIFT); }
">>"        { rtoken(RSHIFT); }
"<"         { rtoken(LT); }
">"         { rtoken(GT); }
"<="        { rtoken(LE); }
">="        { rtoken(GE); }
"=="        { rtoken(EQEQ); }
"!="        { rtoken(NE); }
"^"         { rtoken(HAT); }
"|"         { rtoken(OR); }
"&&"        { rtoken(L_AND); }
"||"        { rtoken(L_OR); }


"?"         { rtoken(QUESTION); }
":"         { pre_shift_token(yytext, COLON); line_break(); return COLON; }
";"         { pre_shift_token(yytext, SEMI_COLON); line_break(); return SEMI_COLON; }
"..."       { rtoken(DOT3); }


"="         { rtoken(EQ); }
"*="        { rtoken(ASTR_EQ); }
"/="        { rtoken(DASH_EQ); }
"%="        { rtoken(PERC_EQ); }
"+="        { rtoken(PLUS_EQ); }
"-="        { rtoken(MINUS_EQ); }
"<<="       { rtoken(LSHIFT_EQ); }
">>="       { rtoken(RSHIFT_EQ); }
"&="        { rtoken(AMP_EQ); }
"^="        { rtoken(HAT_EQ); }
"|="        { rtoken(OR_EQ); }


","         { rtoken(COMMA); }


 /*error case...*/

{digit}*{nondigit}*     {   printf(" invalid token [%s]\n", yytext);   return INVALID;  }
.                       {   printf(" invalid token [%s]\n", yytext);   return INVALID;  }

%%


int main2(int argc, char* argv[]) {
    return yylex();
}

