%{

/*kersh.tab.c*/

#include <stdio.h>
#include "kersh.h"
#include "kersh.tab.h"

%}

%token
IDENTIFIER DECIMAL_CONSTANT OCTAL_CONSTANT HEX_CONSTANT
TYPEDEF SIZEOF ENUM STRUCT UNION
CONST STATIC EXTERN VOLATILE INLINE
DO WHILE FOR CONTINUE BREAK
GOTO RETURN
SWITCH CASE DEFAULT
IF ELSE
VOID INT CHAR SHORT LONG SIGNED UNSIGNED
INVALID

 /*OPE_2 ASTR OPE_INC OPE_ASIGN
OPE_ARROW DOT COMMA QUESTION COLON SEMI_COLON
LPAR RPAR LBRACE RBRACE LBRACKET RBRACKET
%left OPE_2
%left ASTR
 */


%%
code        :   /*empty*/
            |   code IDENTIFIER     {   printf("  << identifier...\n");   }
            |   code constant       {   printf("  << constant..\n");   }
            |   code keyword        {   printf("  << keyword...\n");   }
            ;
 /*
            |  string_literal
            |  punctuator
 */

constant    :   integer_constant
            ;

integer_constant    :   DECIMAL_CONSTANT
                    |   OCTAL_CONSTANT
                    |   HEX_CONSTANT
                    ;

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
            |   RETURN
            |   SHORT
            |   SIGNED
            |   SIZEOF
            |   STATIC
            |   STRUCT
            |   SWITCH
            |   TYPEDEF
            |   UNION
            |   VOID
            |   VOLATILE
            |   WHILE
            ;

/*comment...*/

%%


/*main func...*/


int main(int argc, char* argv[]) {
    init_values();
    return yyparse();
}
