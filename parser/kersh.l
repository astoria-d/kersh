%{
#include "parser.h"
#include "kersh.tab.h"

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

%%
[ \t\r]+      ; /*ignore white spaces...*/
\n          {   line_inc();     }

 /* gcc preprocessor outputs line number. skip it.*/
#[^\n]*          {   /*printf("gcc line num [%s]..\n", yytext);*/}


 /*keywords*/

 /*operator*/
"["         { rtoken(LBRACKET); }
"]"         { rtoken(RBRACKET); }
"("         { rtoken(LPAR); }
")"         { rtoken(RPAR); }
"{"         { rtoken(LBRACE); }
"}"         { rtoken(RBRACE); }
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
":"         { rtoken(COLON); }
";"         { rtoken(SEMI_COLON); }
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

"sizeof"    { rtoken(SIZEOF); }

 /*strage_class_specifier*/
"typedef"   { rtoken(TYPEDEF); }
"extern"    { rtoken(EXTERN); }
"static"    { rtoken(STATIC); }
"auto"      { rtoken(AUTO); }

 /*type_specifier*/
"void"      { rtoken(VOID); }
"char"      { rtoken(CHAR); }
"short"     { rtoken(SHORT); }
"int"       { rtoken(INT); }
"long"      { rtoken(LONG); }
"signed"    { rtoken(SIGNED); }
"unsigned"  { rtoken(UNSIGNED); }

"struct"    { rtoken(STRUCT); }
"union"     { rtoken(UNION); }
"enum"      { rtoken(ENUM);   }

 /*type_qualifier*/
"const"     { rtoken(CONST); }
"volatile"  { rtoken(VOLATILE); }


 /*function_speficier*/
"inline"    { rtoken(INLINE); }


 /*labeled_statement*/
"switch"    { rtoken(SWITCH); }
"case"      { rtoken(CASE); }
"default"   { rtoken(DEFAULT); }

 /*selection_statement*/
"if"        { rtoken(IF); }
"else"      { rtoken(ELSE); }

 /*iteration_statement*/
"do"        { rtoken(DO); }
"while"     { rtoken(WHILE); }
"for"       { rtoken(FOR); }


 /*jump_statement*/
"goto"      { rtoken(GOTO); }
"continue"  { rtoken(CONTINUE); }
"break"     { rtoken(BREAK); }
"return"    { rtoken(RETURN); }


 /* https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html
GNU extensions add these keywords:
__FUNCTION__ __PRETTY_FUNCTION__ __alignof __alignof__ __asm
__asm__ __attribute __attribute__ __builtin_offsetof __builtin_va_arg
__complex __complex__ __const __extension__ __func__ __imag __imag__ 
__inline __inline__ __label__ __null __real __real__ 
__restrict __restrict__ __signed __signed__ __thread __typeof
__volatile __volatile__ 
 */

"__inline"      { rtoken(INLINE); }
"__inline__"    { rtoken(INLINE); }
"__signed"      { rtoken(SIGNED); }
"__signed__"    { rtoken(SIGNED); }
"__volatile"    { rtoken(VOLATILE); }
"__volatile__"  { rtoken(VOLATILE); }

 /*don't know how to handle this key word...*/
"__extension__"  ;

"__attribute"       { rtoken(ATTRIBUTE); }
"__attribute__"     { rtoken(ATTRIBUTE); }


 /*constant*/
{nonzerodigit}{digit}*(u|U)?(l|L|ll|LL)?       { rtoken(DECIMAL_CONSTANT); }
{nonzerodigit}{digit}*(l|L|ll|LL)?(u|U)?       { rtoken(DECIMAL_CONSTANT); }

0{octaldigit}*(u|U)?(l|L|ll|LL)?              { rtoken(OCTAL_CONSTANT); }
0{octaldigit}*(l|L|ll|LL)?(u|U)?              { rtoken(OCTAL_CONSTANT); }

0[xX]{hexdigit}*(u|U)?(l|L|ll|LL)?            { rtoken(HEX_CONSTANT); }
0[xX]{hexdigit}*(l|L|ll|LL)?(u|U)?            { rtoken(HEX_CONSTANT); }

\'({cchar}|{simple_escape}|{octal_escape}|{hex_escape})*\'          { rtoken(C_CHAR); }


\"({schar}|{simple_escape}|{octal_escape}|{hex_escape})*\"          { rtoken(S_CHAR); }


 /*identifier*/
{nondigit}({nondigit}|{digit})*     {   /*identifier or enum or typename*/
                                        int token = check_token_type(yytext);
                                        rtoken(token);
                                    }

 /*error case...*/

{digit}*{nondigit}*     {   printf(" invalid token [%s]\n", yytext);   return INVALID;  }
.                       {   printf(" invalid token [%s]\n", yytext);   return INVALID;  }

%%


int main2(int argc, char* argv[]) {
    return yylex();
}

