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
TYPE_NAME


%token
ARROW
INC
DEC
LSHIFT
RSHIFT
LE
GE
EQEQ
NE
L_AND
L_OR
DOT3
ASTR_EQ
DASH_EQ
PERC_EQ
PLUS_EQ
MINUS_EQ
LSHIFT_EQ
RSHIFT_EQ
AMP_EQ
HAT_EQ
OR_EQ

%%

code        :   /*empty*/
            |   code statement
            ;

statement   :   expression ';'      {printf("\n");}
            ;

 /*
lexer       :   {}
            |   lexer keyword
            |   lexer identifier
            |   lexer constant
            |   lexer string_literal
            |   lexer punctuator
            ;
 */

 /*A.1.2
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
 */

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

integer_constant    :   DECIMAL_CONSTANT
                    |   OCTAL_CONSTANT
                    |   HEX_CONSTANT
                    ;

emumeration_constant    :   ENUM_CONSTANT
                        ;

character_constant      :   C_CHAR
                        ;


 /*A.1.6*/
string_literal          :   S_CHAR
                        ;


 /*A.1.7
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
 */



primary_expression  :   identifier
                    |   constant
                    |   string_literal
                    |   '(' expression ')'
                    ;


 /*temporarily....*/
type_name       :   TYPE_NAME
                ;
initializer_list    :   constant
                    ;

 /*A2.1*/
postfix_expression  :   primary_expression
                    |   postfix_expression '[' expression ']'
                    |   postfix_expression '(' argument_expression_list ')'
                    |   postfix_expression '(' ')'
                    |   postfix_expression '.' identifier
                    |   postfix_expression ARROW identifier
                    |   postfix_expression INC
                    |   postfix_expression DEC
                    |   '(' type_name ')' '{' initializer_list '}'
                    |   '(' type_name ')' '{' initializer_list ',' '}'
                    ;

argument_expression_list    :   assignment_expression
                            |   argument_expression_list ',' assignment_expression
                            ;

unary_expression    :   postfix_expression
                    |   INC unary_expression
                    |   DEC unary_expression
                    |   unary_operator cast_expression
                    |   SIZEOF unary_expression
                    |   SIZEOF '(' type_name ')'
                    ;

unary_operator      :   '&'
                    |   '*'
                    |   '+'
                    |   '-'
                    |   '~'
                    |   '!'
                    ;

cast_expression     :   unary_expression
                    |   '(' type_name ')'
                    ;

multipricative_expression   :   cast_expression
                            |   multipricative_expression '*' cast_expression
                            |   multipricative_expression '/' cast_expression
                            |   multipricative_expression '%' cast_expression
                            ;

additive_expression     :   multipricative_expression
                        |   additive_expression '+' multipricative_expression
                        |   additive_expression '-' multipricative_expression
                        ;

shift_expression        :   additive_expression
                        |   shift_expression LSHIFT additive_expression
                        |   shift_expression RSHIFT additive_expression
                        ;

retional_expression     :   shift_expression
                        |   retional_expression '<' shift_expression
                        |   retional_expression '>' shift_expression
                        |   retional_expression LE shift_expression
                        |   retional_expression GE shift_expression
                        ;

equality_expression     :   retional_expression
                        |   equality_expression EQEQ retional_expression
                        |   equality_expression NE retional_expression
                        ;

AND_expression          :   equality_expression
                        |   AND_expression '&' equality_expression
                        ;

exclusive_OR_expression     :   AND_expression
                            |   exclusive_OR_expression '^' AND_expression
                            ;

inclusive_OR_expression     :   exclusive_OR_expression
                            |   inclusive_OR_expression '|' exclusive_OR_expression
                            ;

logical_AND_expression      :   inclusive_OR_expression
                            |   logical_AND_expression L_AND inclusive_OR_expression
                            ;

logical_OR_expression       :   logical_AND_expression
                            |   logical_OR_expression L_OR logical_AND_expression
                            ;

conditional_expression      :   logical_OR_expression
                            |   logical_OR_expression '?' expression ':' conditional_expression
                            ;

assignment_expression       :   conditional_expression
                            |   unary_expression assignment_operator assignment_expression
                            ;

assignment_operator         :   '='
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
                            ;

expression      :   assignment_expression
                |   expression ',' assignment_expression
                ;

constant_expression :   conditional_expression
                    ;


/*comment...*/

%%


/*main func...*/


int main(int argc, char* argv[]) {
    init_values();
    return yyparse();
}
