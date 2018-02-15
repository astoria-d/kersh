%{

/*kersh.tab.c*/

#include <stdio.h>
#include "kersh.h"
#include "kersh.tab.h"

#define     dprint(msg)    printf("  << %s...\n", msg)

#define     line_break()    printf("\n")

%}

%token
AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO ELSE ENUM EXTERN
FOR GOTO IF INLINE INT LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC STRUCT
SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE
IDEN DECIMAL_CONSTANT OCTAL_CONSTANT HEX_CONSTANT ENUM_CONSTANT
INVALID
C_CHAR S_CHAR
TYPEDEF_NAME

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

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

%start translation_unit

%%

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

 /*A.1.3 Identifiers*/
identifier  :   IDEN
            ;
 /*
 A.1.4
 universal character name
 \u0011 \uxxxx etc. not supported...
 */


 /*A.1.5 Constants*/
constant    :   integer_constant
            |   emumeration_constant
            |   character_constant
            ;

integer_constant    :   DECIMAL_CONSTANT
                    |   OCTAL_CONSTANT
                    |   HEX_CONSTANT
                    ;

 /*kersh original. can't solve the conflicts.*/
emumeration_constant    :   ENUM_CONSTANT
                        ;

character_constant      :   C_CHAR
                        ;


 /*A.1.6 String literals*/
string_literal          :   S_CHAR
                        ;


 /*A.1.7 Punctuators
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



 /*A2.1 Expressions*/
primary_expression  :   identifier
                    |   constant
                    |   string_literal
                    |   '(' expression ')'
                    ;

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
                    |   '(' type_name ')' cast_expression
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


 /*A2.2 Declarations*/
declaration     :   declaration_specifiers ';'                          {line_break();}
                |   declaration_specifiers init_declarator_list ';'     {line_break();}
                ;

declaration_specifiers  :   storage_class_specifier
                        |   storage_class_specifier declaration_specifiers
                        |   type_specifier
                        |   type_specifier declaration_specifiers
                        |   type_qualifier
                        |   type_qualifier declaration_specifiers
                        |   function_speficier
                        |   function_speficier declaration_specifiers
                        ;

 /* not supported...
                        |   alignment_specifier declaration_specifiers
                        |   alignment_specifier
 */

init_declarator_list    :   init_declarator
                        |   init_declarator_list ',' init_declarator
                        ;

init_declarator         :   declarator
                        |   declarator '=' initializer
                        ;

storage_class_specifier     :   TYPEDEF
                            |   EXTERN
                            |   STATIC
                            |   AUTO
                            |   REGISTER
                            ;

type_specifier  :   VOID
                |   CHAR
                |   SHORT
                |   INT
                |   LONG
                |   SIGNED
                |   UNSIGNED
                |   struct_or_union_specifier
                |   enum_specifier
                |   typedef_name
                ;


struct_or_union_specifier   :   struct_or_union '{'                                 {line_break();}
                                struct_declaration_list '}'
                            |   struct_or_union identifier '{'                      {line_break();}
                                struct_declaration_list '}'
                            |   struct_or_union identifier
                            ;

struct_or_union     :   STRUCT
                    |   UNION
                    ;

struct_declaration_list     :   struct_declaration
                            |   struct_declaration_list struct_declaration
                            ;

struct_declaration      :   specifier_qualifier_list ';'                            {line_break();}
                        |   specifier_qualifier_list struct_declarator_list ';'     {line_break();}
                        ;

specifier_qualifier_list    :   type_specifier
                            |   type_specifier specifier_qualifier_list
                            |   type_qualifier
                            |   type_qualifier specifier_qualifier_list
                            ;

struct_declarator_list      :   struct_declarator
                            |   struct_declarator_list ',' struct_declarator
                            ;

struct_declarator   :   declarator
                    |   ':' constant_expression
                    |   declarator ':' constant_expression
                    ;

enum_specifier      :   ENUM '{' emumerator_list '}'
                    |   ENUM identifier '{' emumerator_list '}'
                    |   ENUM '{' emumerator_list ',' '}'
                    |   ENUM identifier '{' emumerator_list ',' '}'
                    |   ENUM identifier
                    ;

emumerator_list     :   emumerator
                    |   emumerator_list ',' emumerator
                    ;

emumerator      :   emumeration_constant
                |   emumeration_constant '=' constant_expression
                ;

type_qualifier      :   CONST
                    |   VOLATILE
                    ;

function_speficier  :   INLINE
                    ;

declarator      :   direct_declarator
                |   pointer direct_declarator
                ;

direct_declarator   :   identifier
                    |   '(' declarator ')'
                    |   direct_declarator '[' ']'
                    |   direct_declarator '[' assignment_expression ']'
                    |   direct_declarator '[' type_qualifier ']'
                    |   direct_declarator '[' type_qualifier assignment_expression ']'
                    |   direct_declarator '[' STATIC assignment_expression ']'
                    |   direct_declarator '[' STATIC type_qualifier assignment_expression ']'
                    |   direct_declarator '[' type_qualifier STATIC assignment_expression ']'
                    |   direct_declarator '[' '*' ']'
                    |   direct_declarator '[' type_qualifier '*' ']'
                    |   direct_declarator '(' parameter_type_list ')'
                    |   direct_declarator '(' ')'
                    |   direct_declarator '(' identifier_list ')'
                    ;

pointer     :   '*'
            |   '*' type_qualifier_list
            |   '*' pointer
            |   '*' type_qualifier_list pointer
            ;

type_qualifier_list     :   type_qualifier
                        |   type_qualifier_list type_qualifier
                        ;

parameter_type_list     :   parameter_list
                        |   parameter_list ',' DOT3
                        ;

parameter_list      :   parameter_declaration
                    |   parameter_list ',' parameter_declaration
                    ;

parameter_declaration   :   declaration_specifiers declarator
                        |   declaration_specifiers
                        |   declaration_specifiers abstract_declarator
                        ;

identifier_list     :   identifier
                    |   identifier_list ',' identifier
                    ;

type_name       :   specifier_qualifier_list
                |   specifier_qualifier_list abstract_declarator
                ;

abstract_declarator :   pointer
                    |   direct_abstract_declarator
                    |   pointer direct_abstract_declarator
                    ;

direct_abstract_declarator      :   '(' abstract_declarator ')'
                                |   '[' ']'
                                |   '[' assignment_expression ']'
                                |   '[' type_qualifier_list ']'
                                |   '[' type_qualifier_list assignment_expression ']'
                                |   direct_abstract_declarator '[' ']'
                                |   direct_abstract_declarator '[' assignment_expression ']'
                                |   direct_abstract_declarator '[' type_qualifier_list ']'
                                |   direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
                                |   '[' STATIC assignment_expression ']'
                                |   '[' STATIC type_qualifier_list assignment_expression ']'
                                |   direct_abstract_declarator '[' STATIC assignment_expression ']'
                                |   direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
                                |   '[' type_qualifier_list STATIC assignment_expression ']'
                                |   direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
                                |   '[' '*' ']'
                                |   direct_abstract_declarator '[' '*' ']'
                                |   '(' ')'
                                |   '(' parameter_type_list ')'
                                |   direct_abstract_declarator '(' ')'
                                |   direct_abstract_declarator '(' parameter_type_list ')'
                                ;

 /*kersh original. can't solve the conflicts.*/
typedef_name    :   TYPEDEF_NAME
                ;

initializer     :   assignment_expression
                |   '{' initializer_list '}'
                |   '{' initializer_list ',' '}'
                ;

initializer_list    :   initializer
                    |   designation initializer
                    |   initializer_list ',' initializer
                    |   initializer_list ',' designation initializer
                    ;

designation     :   designator_list '='

designator_list :   designator
                |   designator_list designator
                ;

designator      :   '[' constant_expression ']'
                |   '.' identifier
                ;

 /*A2.3 Statements*/
statement   :   labeled_statement
            |   compound_statement
            |   expression-statement
            |   selection_statement
            |   iteration_statement
            |   jump_statement
            ;

labeled_statement   :   identifier ':' statement
                    |   CASE constant_expression ':' statement
                    |   DEFAULT ':' statement
                    ;

compound_statement  :   '{' '}'
                    |   '{'                                 {line_break();}
                        block_item_list '}'                 {line_break();}
                    ;

block_item_list     :   block_item
                    |   block_item_list block_item
                    ;

block_item      :   declaration
                |   statement
                ;

expression-statement    :   ';'
                        |   expression ';'                  {line_break();}
                        ;

selection_statement     :   IF '(' expression ')' statement %prec LOWER_THAN_ELSE   {/*conflict workaround*/}
                        |   IF '(' expression ')' statement ELSE statement
                        |   SWITCH '(' expression ')' statement
                        ;

iteration_statement     :   WHILE '(' expression ')' statement
                        |   DO statement WHILE '(' expression ')' ';'                   {line_break();}
                        |   FOR '(' ';' ';' ')' statement
                        |   FOR '(' ';' ';' expression ')' statement
                        |   FOR '(' ';' expression ';' ')' statement
                        |   FOR '(' ';' expression ';' expression ')' statement
                        |   FOR '(' expression ';' ';' ')' statement
                        |   FOR '(' expression ';' ';' expression ')' statement
                        |   FOR '(' expression ';' expression ';' ')' statement
                        |   FOR '(' expression ';' expression ';' expression ')' statement
                        |   FOR '(' declaration ';' ')' statement
                        |   FOR '(' declaration ';' expression ')' statement
                        |   FOR '(' declaration expression ';' ')' statement
                        |   FOR '(' declaration expression ';' expression ')' statement
                        ;

jump_statement      :   GOTO identifier ';'                         {line_break();}
                    |   CONTINUE ';'                                {line_break();}
                    |   BREAK ';'                                   {line_break();}
                    |   RETURN ';'                                  {line_break();}
                    |   RETURN expression ';'                       {line_break();}
                    ;


 /*A2.4 External definitions*/
translation_unit    :   external_declaration
                    |   translation_unit external_declaration
                    ;

external_declaration    :   function_definition
                        |   declaration
                        ;

function_definition     :   declaration_specifiers declarator compound_statement
                        |   declaration_specifiers declarator declaration_list compound_statement
                        ;

declaration_list        :   declaration
                        |   declaration_list declaration
                        ;


%%


/*main func...*/


int main(int argc, char* argv[]) {
    init_values();
    return yyparse();
}
