%{

/*kersh.tab.c*/

#include <stdio.h>
#include "kersh.h"
#include "kersh.tab.h"

#define     dprint(msg)    printf("  << %s...\n", msg)
    
%}

%token
BREAK CASE CHAR CONST CONTINUE DEFAULT DO ELSE ENUM EXTERN
FOR GOTO IF INLINE INT LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC STRUCT
SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE
IDEN DECIMAL_CONSTANT OCTAL_CONSTANT HEX_CONSTANT ENUM_CONSTANT
INVALID
C_CHAR S_CHAR
LBRACKET RBRACKET LPAR RPAR LBRACE RBRACE DOT ARROW
INC DEC AMP ASTR PLUS MINUS TILDA EXQL
DASH PERCENT LSHIFT RSHIFT LT GT LE GE EQEQ NE HAT OR L_AND L_OR
QUESTION COLON SEMI_COLON DOT3
EQ ASTR_EQ DASH_EQ PERC_EQ PLUS_EQ MINUS_EQ LSHIFT_EQ RSHIFT_EQ AMP_EQ HAT_EQ OR_EQ
COMMA

 /*
%left OPE_2
%left ASTR
 */


%%
code        :   /*empty*/
            |   code keyword            {dprint("keyword");}
            |   code identifier         {dprint("identifier");}
            |   code constant
            |   code string_literal
            |   code punctuator         {dprint("punctuator");}
            ;

 /*A.1.2*/
keyword     :   BREAK
            |   CASE
            |   CHAR
            |   CONST
            |   CONTINUE
            |   DEFAULT
            |   DO
            |   ELSE
            |   ENUM
            |   EXTERN
            |   FOR
            |   GOTO
            |   IF
            |   INLINE
            |   INT
            |   LONG
            |   REGISTER
            |   RETURN
            |   SHORT
            |   SIGNED
            |   SIZEOF
            |   STATIC
            |   STRUCT
            |   SWITCH
            |   TYPEDEF
            |   UNION
            |   UNSIGNED
            |   VOID
            |   VOLATILE
            |   WHILE
            ;


 /*A.1.3*/
identifier  :   IDEN
            ;
 /*
 A.1.4
 universal character name
 \u0011 \uxxxx etc. not supported...
 */


 /*A.1.5*/
constant    :   integer_constant
            |   emumeration_constant
            |   character_constant
            ;

integer_constant    :   DECIMAL_CONSTANT    {dprint("decimal constant");}
                    |   OCTAL_CONSTANT      {dprint("octal constant");}
                    |   HEX_CONSTANT        {dprint("hex constant");}
                    ;

emumeration_constant    :   ENUM_CONSTANT      {dprint("enum constant");}
                        ;

character_constant      :   C_CHAR      {dprint("char constant");}
                        ;


 /*A.1.6*/
string_literal          :   S_CHAR      {dprint("string literal");}
                        ;


 /*A.1.7*/
punctuator  :   LBRACKET
            |   RBRACKET
            |   LPAR
            |   RPAR
            |   LBRACE
            |   RBRACE
            |   DOT
            |   ARROW
            |   INC
            |   DEC
            |   AMP
            |   ASTR
            |   PLUS
            |   MINUS
            |   TILDA
            |   EXQL
            |   DASH
            |   PERCENT
            |   LSHIFT
            |   RSHIFT
            |   LT
            |   GT
            |   LE
            |   GE
            |   EQEQ
            |   NE
            |   HAT
            |   OR
            |   L_AND
            |   L_OR
            |   QUESTION
            |   COLON
            |   SEMI_COLON
            |   DOT3
            |   EQ
            |   ASTR_EQ
            |   DASH_EQ
            |   PERC_EQ
            |   PLUS_EQ
            |   MINUS_EQ
            |   LSHIFT_EQ
            |   RSHIFT_EQ
            |   AMP_EQ
            |   HAT_EQ
            |   OR_EQ
            |   COMMA
            ;

/*comment...*/

%%


/*main func...*/


int main(int argc, char* argv[]) {
    init_values();
    return yyparse();
}
