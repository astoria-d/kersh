%{

/*kersh.tab.c*/

#include <stdio.h>
#include "parser.h"
#include "kersh.tab.h"
#include "idtbl.h"
#include "reduce.h"
#include "statements.h"

#define SEM_OK 0
#define SEM_NG 1
static unsigned int semantic_check;

#define     dprint(msg)    printf("  << %s...\n", msg)

#define     POST_REDUCE(rule_id)   post_reduce_action(rule_id);\
                                   if (semantic_check == SEM_NG) YYABORT;

int yylex (void);
void yyerror (char const *s);

%}

%token
AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO ELSE ENUM EXTERN
FOR GOTO IF INLINE INT LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC STRUCT
SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE
INVALID
TYPEDEF_NAME

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%token
ARROW INC DEC LSHIFT RSHIFT LE GE EQEQ NE L_AND L_OR DOT3


%token
ATTRIBUTE

%union {
    struct token_list* tk;
    struct abs_syntax_tree* ast;
    struct expression* exp;
    struct statement* stm;
}

%token <tk> IDEN DECIMAL_CONSTANT OCTAL_CONSTANT HEX_CONSTANT ENUM_CONSTANT C_CHAR S_CHAR
            '=' ASTR_EQ DASH_EQ PERC_EQ PLUS_EQ MINUS_EQ LSHIFT_EQ RSHIFT_EQ AMP_EQ HAT_EQ OR_EQ

%type <tk>  identifier constant integer_constant emumeration_constant character_constant string_literal
            assignment_operator

%type <exp> primary_expression argument_expression_list assignment_expression postfix_expression
            unary_expression cast_expression multipricative_expression additive_expression
            shift_expression relational_expression equality_expression AND_expression
            exclusive_OR_expression inclusive_OR_expression logical_AND_expression
            logical_OR_expression conditional_expression expression constant_expression

%type <stm> statement labeled_statement compound_statement block_item_list block_item
            expression_statement selection_statement iteration_statement jump_statement

%start translation_unit

%%

 /*A.1.3 Identifiers*/
identifier  :   IDEN                                                                                                                {$$ = $1; POST_REDUCE(indx_identifier_0) }
            ;
 /*
 A.1.4
 universal character name
 \u0011 \uxxxx etc. not supported...
 */


 /*A.1.5 Constants*/
constant    :   integer_constant                                                                                                    {$$ = $1; POST_REDUCE(indx_constant_0) }
            |   emumeration_constant                                                                                                {$$ = $1; POST_REDUCE(indx_constant_1) }
            |   character_constant                                                                                                  {$$ = $1; POST_REDUCE(indx_constant_2) }
            ;

integer_constant    :   DECIMAL_CONSTANT                                                                                            {$$ = $1; POST_REDUCE(indx_integer_constant_0) }
                    |   OCTAL_CONSTANT                                                                                              {$$ = $1; POST_REDUCE(indx_integer_constant_1) }
                    |   HEX_CONSTANT                                                                                                {$$ = $1; POST_REDUCE(indx_integer_constant_2) }
                    ;

 /*kersh original. can't solve the conflicts.*/
emumeration_constant    :   ENUM_CONSTANT                                                                                           {$$ = $1; POST_REDUCE(indx_emumeration_constant_0) }
                        ;

character_constant      :   C_CHAR                                                                                                  {$$ = $1; POST_REDUCE(indx_character_constant_0) }
                        ;


 /*A.1.6 String literals*/
string_literal          :   S_CHAR                                                                                                  {$$ = $1; POST_REDUCE(indx_string_literal_0) }
                        ;

 /*A2.1 Expressions*/
primary_expression  :   identifier                                                                                                  {$$ = alloc_term_exp($1); POST_REDUCE(indx_primary_expression_0) }
                    |   constant                                                                                                    {$$ = alloc_term_exp($1); POST_REDUCE(indx_primary_expression_1) }
                    |   string_literal                                                                                              {$$ = alloc_term_exp($1); POST_REDUCE(indx_primary_expression_2) }
                    |   '(' expression ')'                                                                                          {$$ = alloc_nested_exp($2); POST_REDUCE(indx_primary_expression_3) }
                    ;

postfix_expression  :   primary_expression                                                                                          {$$ = $1; POST_REDUCE(indx_postfix_expression_0) }
                    |   postfix_expression '[' expression ']'                                                                       {POST_REDUCE(indx_postfix_expression_1) }
                    |   postfix_expression '(' argument_expression_list ')'                                                         {POST_REDUCE(indx_postfix_expression_2) }
                    |   postfix_expression '(' ')'                                                                                  {POST_REDUCE(indx_postfix_expression_3) }
                    |   postfix_expression '.' identifier                                                                           {POST_REDUCE(indx_postfix_expression_4) }
                    |   postfix_expression ARROW identifier                                                                         {POST_REDUCE(indx_postfix_expression_5) }
                    |   postfix_expression INC                                                                                      {POST_REDUCE(indx_postfix_expression_6) }
                    |   postfix_expression DEC                                                                                      {POST_REDUCE(indx_postfix_expression_7) }
                    |   '(' type_name ')' '{' initializer_list '}'                                                                  {POST_REDUCE(indx_postfix_expression_8) }
                    |   '(' type_name ')' '{' initializer_list ',' '}'                                                              {POST_REDUCE(indx_postfix_expression_9) }
                    ;

argument_expression_list    :   assignment_expression                                                                               {$$ = $1; POST_REDUCE(indx_argument_expression_list_0) }
                            |   argument_expression_list ',' assignment_expression                                                  {POST_REDUCE(indx_argument_expression_list_1) }
                            ;

unary_expression    :   postfix_expression                                                                                          {$$ = $1; POST_REDUCE(indx_unary_expression_0) }
                    |   INC unary_expression                                                                                        {POST_REDUCE(indx_unary_expression_1) }
                    |   DEC unary_expression                                                                                        {POST_REDUCE(indx_unary_expression_2) }
                    |   unary_operator cast_expression                                                                              {POST_REDUCE(indx_unary_expression_3) }
                    |   SIZEOF unary_expression                                                                                     {POST_REDUCE(indx_unary_expression_4) }
                    |   SIZEOF '(' type_name ')'                                                                                    {POST_REDUCE(indx_unary_expression_5) }
                    ;

unary_operator      :   '&'                                                                                                         {POST_REDUCE(indx_unary_operator_0) }
                    |   '*'                                                                                                         {POST_REDUCE(indx_unary_operator_1) }
                    |   '+'                                                                                                         {POST_REDUCE(indx_unary_operator_2) }
                    |   '-'                                                                                                         {POST_REDUCE(indx_unary_operator_3) }
                    |   '~'                                                                                                         {POST_REDUCE(indx_unary_operator_4) }
                    |   '!'                                                                                                         {POST_REDUCE(indx_unary_operator_5) }
                    ;

cast_expression     :   unary_expression                                                                                            {$$ = $1; POST_REDUCE(indx_cast_expression_0) }
                    |   '(' type_name ')' cast_expression                                                                           {POST_REDUCE(indx_cast_expression_1) }
                    ;

multipricative_expression   :   cast_expression                                                                                     {$$ = $1; POST_REDUCE(indx_multipricative_expression_0) }
                            |   multipricative_expression '*' cast_expression                                                       {$$ = alloc_2op_exp(OP_MUL, $1, $3); POST_REDUCE(indx_multipricative_expression_1) }
                            |   multipricative_expression '/' cast_expression                                                       {$$ = alloc_2op_exp(OP_DIV, $1, $3); POST_REDUCE(indx_multipricative_expression_2) }
                            |   multipricative_expression '%' cast_expression                                                       {$$ = alloc_2op_exp(OP_MOD, $1, $3); POST_REDUCE(indx_multipricative_expression_3) }
                            ;

additive_expression     :   multipricative_expression                                                                               {$$ = $1; POST_REDUCE(indx_additive_expression_0) }
                        |   additive_expression '+' multipricative_expression                                                       {$$ = alloc_2op_exp(OP_PLUS, $1, $3); POST_REDUCE(indx_additive_expression_1) }
                        |   additive_expression '-' multipricative_expression                                                       {$$ = alloc_2op_exp(OP_MINUS, $1, $3); POST_REDUCE(indx_additive_expression_2) }
                        ;

shift_expression        :   additive_expression                                                                                     {$$ = $1; POST_REDUCE(indx_shift_expression_0) }
                        |   shift_expression LSHIFT additive_expression                                                             {POST_REDUCE(indx_shift_expression_1) }
                        |   shift_expression RSHIFT additive_expression                                                             {POST_REDUCE(indx_shift_expression_2) }
                        ;

relational_expression   :   shift_expression                                                                                        {$$ = $1; POST_REDUCE(indx_relational_expression_0) }
                        |   relational_expression '<' shift_expression                                                              {POST_REDUCE(indx_relational_expression_1) }
                        |   relational_expression '>' shift_expression                                                              {POST_REDUCE(indx_relational_expression_2) }
                        |   relational_expression LE shift_expression                                                               {POST_REDUCE(indx_relational_expression_3) }
                        |   relational_expression GE shift_expression                                                               {POST_REDUCE(indx_relational_expression_4) }
                        ;

equality_expression     :   relational_expression                                                                                   {$$ = $1; POST_REDUCE(indx_equality_expression_0) }
                        |   equality_expression EQEQ relational_expression                                                          {POST_REDUCE(indx_equality_expression_1) }
                        |   equality_expression NE relational_expression                                                            {POST_REDUCE(indx_equality_expression_2) }
                        ;

AND_expression          :   equality_expression                                                                                     {$$ = $1; POST_REDUCE(indx_AND_expression_0) }
                        |   AND_expression '&' equality_expression                                                                  {POST_REDUCE(indx_AND_expression_1) }
                        ;

exclusive_OR_expression     :   AND_expression                                                                                      {$$ = $1; POST_REDUCE(indx_exclusive_OR_expression_0) }
                            |   exclusive_OR_expression '^' AND_expression                                                          {POST_REDUCE(indx_exclusive_OR_expression_1) }
                            ;

inclusive_OR_expression     :   exclusive_OR_expression                                                                             {$$ = $1; POST_REDUCE(indx_inclusive_OR_expression_0) }
                            |   inclusive_OR_expression '|' exclusive_OR_expression                                                 {POST_REDUCE(indx_inclusive_OR_expression_1) }
                            ;

logical_AND_expression      :   inclusive_OR_expression                                                                             {$$ = $1; POST_REDUCE(indx_logical_AND_expression_0) }
                            |   logical_AND_expression L_AND inclusive_OR_expression                                                {POST_REDUCE(indx_logical_AND_expression_1) }
                            ;

logical_OR_expression       :   logical_AND_expression                                                                              {$$ = $1; POST_REDUCE(indx_logical_OR_expression_0) }
                            |   logical_OR_expression L_OR logical_AND_expression                                                   {POST_REDUCE(indx_logical_OR_expression_1) }
                            ;

conditional_expression      :   logical_OR_expression                                                                               {$$ = $1; POST_REDUCE(indx_conditional_expression_0) }
                            |   logical_OR_expression '?' expression ':' conditional_expression                                     {POST_REDUCE(indx_conditional_expression_1) }
                            ;

assignment_expression       :   conditional_expression                                                                              {$$ = $1; POST_REDUCE(indx_assignment_expression_0) }
                            |   unary_expression assignment_operator assignment_expression                                          {$$ = alloc_2op_exp(get_exp_op($2), $1, $3); POST_REDUCE(indx_assignment_expression_1) }
                            ;

assignment_operator         :   '='                                                                                                 {$$ = $1; POST_REDUCE(indx_assignment_operator_0) }
                            |   ASTR_EQ                                                                                             {$$ = $1; POST_REDUCE(indx_assignment_operator_1) }
                            |   DASH_EQ                                                                                             {$$ = $1; POST_REDUCE(indx_assignment_operator_2) }
                            |   PERC_EQ                                                                                             {$$ = $1; POST_REDUCE(indx_assignment_operator_3) }
                            |   PLUS_EQ                                                                                             {$$ = $1; POST_REDUCE(indx_assignment_operator_4) }
                            |   MINUS_EQ                                                                                            {$$ = $1; POST_REDUCE(indx_assignment_operator_5) }
                            |   LSHIFT_EQ                                                                                           {$$ = $1; POST_REDUCE(indx_assignment_operator_6) }
                            |   RSHIFT_EQ                                                                                           {$$ = $1; POST_REDUCE(indx_assignment_operator_7) }
                            |   AMP_EQ                                                                                              {$$ = $1; POST_REDUCE(indx_assignment_operator_8) }
                            |   HAT_EQ                                                                                              {$$ = $1; POST_REDUCE(indx_assignment_operator_9) }
                            |   OR_EQ                                                                                               {$$ = $1; POST_REDUCE(indx_assignment_operator_10) }
                            ;

expression      :   assignment_expression                                                                                           {$$ = $1; POST_REDUCE(indx_expression_0) }
                |   expression ',' assignment_expression                                                                            {POST_REDUCE(indx_expression_1) }
                ;

constant_expression :   conditional_expression                                                                                      {$$ = $1; POST_REDUCE(indx_constant_expression_0) }
                    ;


 /*A2.2 Declarations*/
declaration     :   declaration_specifiers ';'                                                                                      {POST_REDUCE(indx_declaration_0) }
                |   declaration_specifiers init_declarator_list ';'                                                                 {POST_REDUCE(indx_declaration_1) }
                ;

declaration_specifiers  :   storage_class_specifier                                                                                 {POST_REDUCE(indx_declaration_specifiers_0) }
                        |   storage_class_specifier declaration_specifiers                                                          {POST_REDUCE(indx_declaration_specifiers_1) }
                        |   type_specifier                                                                                          {POST_REDUCE(indx_declaration_specifiers_2) }
                        |   type_specifier declaration_specifiers                                                                   {POST_REDUCE(indx_declaration_specifiers_3) }
                        |   type_qualifier                                                                                          {POST_REDUCE(indx_declaration_specifiers_4) }
                        |   type_qualifier declaration_specifiers                                                                   {POST_REDUCE(indx_declaration_specifiers_5) }
                        |   function_speficier                                                                                      {POST_REDUCE(indx_declaration_specifiers_6) }
                        |   function_speficier declaration_specifiers                                                               {POST_REDUCE(indx_declaration_specifiers_7) }
                        ;

 /* not supported...
                        |   alignment_specifier declaration_specifiers
                        |   alignment_specifier
 */

init_declarator_list    :   init_declarator                                                                                         {POST_REDUCE(indx_init_declarator_list_0) }
                        |   init_declarator_list ',' init_declarator                                                                {POST_REDUCE(indx_init_declarator_list_1) }
                        ;

init_declarator         :   declarator                                                                                              {POST_REDUCE(indx_init_declarator_0) }
                        |   declarator '=' initializer                                                                              {POST_REDUCE(indx_init_declarator_1) }
                        ;

storage_class_specifier     :   TYPEDEF                                                                                             {POST_REDUCE(indx_storage_class_specifier_0) }
                            |   EXTERN                                                                                              {POST_REDUCE(indx_storage_class_specifier_1) }
                            |   STATIC                                                                                              {POST_REDUCE(indx_storage_class_specifier_2) }
                            |   AUTO                                                                                                {POST_REDUCE(indx_storage_class_specifier_3) }
                            |   REGISTER                                                                                            {POST_REDUCE(indx_storage_class_specifier_4) }
                            ;

type_specifier  :   VOID                                                                                                            {POST_REDUCE(indx_type_specifier_0) }
                |   CHAR                                                                                                            {POST_REDUCE(indx_type_specifier_1) }
                |   SHORT                                                                                                           {POST_REDUCE(indx_type_specifier_2) }
                |   INT                                                                                                             {POST_REDUCE(indx_type_specifier_3) }
                |   LONG                                                                                                            {POST_REDUCE(indx_type_specifier_4) }
                |   SIGNED                                                                                                          {POST_REDUCE(indx_type_specifier_5) }
                |   UNSIGNED                                                                                                        {POST_REDUCE(indx_type_specifier_6) }
                |   struct_or_union_specifier                                                                                       {POST_REDUCE(indx_type_specifier_7) }
                |   enum_specifier                                                                                                  {POST_REDUCE(indx_type_specifier_8) }
                |   typedef_name                                                                                                    {POST_REDUCE(indx_type_specifier_9) }
                ;


struct_or_union_specifier   :   struct_or_union '{' struct_declaration_list '}'                                                     {POST_REDUCE(indx_struct_or_union_specifier_0) }
                            |   struct_or_union identifier '{' struct_declaration_list '}'                                          {POST_REDUCE(indx_struct_or_union_specifier_1) }
                            |   struct_or_union identifier                                                                          {POST_REDUCE(indx_struct_or_union_specifier_2) }
                            ;

struct_or_union     :   STRUCT                                                                                                      {POST_REDUCE(indx_struct_or_union_0) }
                    |   UNION                                                                                                       {POST_REDUCE(indx_struct_or_union_1) }
                    ;

struct_declaration_list     :   struct_declaration                                                                                  {POST_REDUCE(indx_struct_declaration_list_0) }
                            |   struct_declaration_list struct_declaration                                                          {POST_REDUCE(indx_struct_declaration_list_1) }
                            ;

struct_declaration      :   specifier_qualifier_list ';'                                                                            {POST_REDUCE(indx_struct_declaration_0) }
                        |   specifier_qualifier_list struct_declarator_list ';'                                                     {POST_REDUCE(indx_struct_declaration_1) }
                        ;

specifier_qualifier_list    :   type_specifier                                                                                      {POST_REDUCE(indx_specifier_qualifier_list_0) }
                            |   type_specifier specifier_qualifier_list                                                             {POST_REDUCE(indx_specifier_qualifier_list_1) }
                            |   type_qualifier                                                                                      {POST_REDUCE(indx_specifier_qualifier_list_2) }
                            |   type_qualifier specifier_qualifier_list                                                             {POST_REDUCE(indx_specifier_qualifier_list_3) }
                            ;

struct_declarator_list      :   struct_declarator                                                                                   {POST_REDUCE(indx_struct_declarator_list_0) }
                            |   struct_declarator_list ',' struct_declarator                                                        {POST_REDUCE(indx_struct_declarator_list_1) }
                            ;

struct_declarator   :   declarator                                                                                                  {POST_REDUCE(indx_struct_declarator_0) }
                    |   ':' constant_expression                                                                                     {POST_REDUCE(indx_struct_declarator_1) }
                    |   declarator ':' constant_expression                                                                          {POST_REDUCE(indx_struct_declarator_2) }
                    ;

enum_specifier      :   ENUM '{' emumerator_list '}'                                                                                {POST_REDUCE(indx_enum_specifier_0) }
                    |   ENUM identifier '{' emumerator_list '}'                                                                     {POST_REDUCE(indx_enum_specifier_1) }
                    |   ENUM '{' emumerator_list ',' '}'                                                                            {POST_REDUCE(indx_enum_specifier_2) }
                    |   ENUM identifier '{' emumerator_list ',' '}'                                                                 {POST_REDUCE(indx_enum_specifier_3) }
                    |   ENUM identifier                                                                                             {POST_REDUCE(indx_enum_specifier_4) }
                    ;

emumerator_list     :   emumerator                                                                                                  {POST_REDUCE(indx_emumerator_list_0) }
                    |   emumerator_list ',' emumerator                                                                              {POST_REDUCE(indx_emumerator_list_1) }
                    ;

emumerator      :   emumeration_constant                                                                                            {POST_REDUCE(indx_emumerator_0) }
                |   emumeration_constant '=' constant_expression                                                                    {POST_REDUCE(indx_emumerator_1) }
                ;

type_qualifier      :   CONST                                                                                                       {POST_REDUCE(indx_type_qualifier_0) }
                    |   VOLATILE                                                                                                    {POST_REDUCE(indx_type_qualifier_1) }
                    ;

 /* gcc function attributes...*/

attribute_param_list    :   identifier                                                                                              {POST_REDUCE(indx_attribute_param_list_0) }
                        |   attribute_param_list ',' identifier                                                                     {POST_REDUCE(indx_attribute_param_list_1) }
                        ;

attribute_list          :   ATTRIBUTE '(' '(' ')' ')'                                                                               {POST_REDUCE(indx_attribute_list_0) }
                        |   ATTRIBUTE '(' '(' IDEN ')' ')'                                                                          {POST_REDUCE(indx_attribute_list_1) }
                        |   ATTRIBUTE '(' '(' IDEN ','  attribute_param_list ')' ')'                                                {POST_REDUCE(indx_attribute_list_2) }
                        ;

function_speficier  :   INLINE                                                                                                      {POST_REDUCE(indx_function_speficier_0) }
                    |   attribute_list                                                                                              {POST_REDUCE(indx_function_speficier_1) }
                    ;

declarator      :   direct_declarator                                                                                               {POST_REDUCE(indx_declarator_0) }
                |   pointer direct_declarator                                                                                       {POST_REDUCE(indx_declarator_1) }
                ;

direct_declarator   :   identifier                                                                                                  {POST_REDUCE(indx_direct_declarator_0) }
                    |   '(' declarator ')'                                                                                          {POST_REDUCE(indx_direct_declarator_1) }
                    |   direct_declarator '[' ']'                                                                                   {POST_REDUCE(indx_direct_declarator_2) }
                    |   direct_declarator '[' assignment_expression ']'                                                             {POST_REDUCE(indx_direct_declarator_3) }
                    |   direct_declarator '[' type_qualifier ']'                                                                    {POST_REDUCE(indx_direct_declarator_4) }
                    |   direct_declarator '[' type_qualifier assignment_expression ']'                                              {POST_REDUCE(indx_direct_declarator_5) }
                    |   direct_declarator '[' STATIC assignment_expression ']'                                                      {POST_REDUCE(indx_direct_declarator_6) }
                    |   direct_declarator '[' STATIC type_qualifier assignment_expression ']'                                       {POST_REDUCE(indx_direct_declarator_7) }
                    |   direct_declarator '[' type_qualifier STATIC assignment_expression ']'                                       {POST_REDUCE(indx_direct_declarator_8) }
                    |   direct_declarator '[' '*' ']'                                                                               {POST_REDUCE(indx_direct_declarator_9) }
                    |   direct_declarator '[' type_qualifier '*' ']'                                                                {POST_REDUCE(indx_direct_declarator_10) }
                    |   direct_declarator '(' parameter_type_list ')'                                                               {POST_REDUCE(indx_direct_declarator_11) }
                    |   direct_declarator '(' ')'                                                                                   {POST_REDUCE(indx_direct_declarator_12) }
                    |   direct_declarator '(' identifier_list ')'                                                                   {POST_REDUCE(indx_direct_declarator_13) }
                    ;

pointer     :   '*'                                                                                                                 {POST_REDUCE(indx_pointer_0) }
            |   '*' type_qualifier_list                                                                                             {POST_REDUCE(indx_pointer_1) }
            |   '*' pointer                                                                                                         {POST_REDUCE(indx_pointer_2) }
            |   '*' type_qualifier_list pointer                                                                                     {POST_REDUCE(indx_pointer_3) }
            ;

type_qualifier_list     :   type_qualifier                                                                                          {POST_REDUCE(indx_type_qualifier_list_0) }
                        |   type_qualifier_list type_qualifier                                                                      {POST_REDUCE(indx_type_qualifier_list_1) }
                        ;

parameter_type_list     :   parameter_list                                                                                          {POST_REDUCE(indx_parameter_type_list_0) }
                        |   parameter_list ',' DOT3                                                                                 {POST_REDUCE(indx_parameter_type_list_1) }
                        ;

parameter_list      :   parameter_declaration                                                                                       {POST_REDUCE(indx_parameter_list_0) }
                    |   parameter_list ',' parameter_declaration                                                                    {POST_REDUCE(indx_parameter_list_1) }
                    ;

parameter_declaration   :   declaration_specifiers declarator                                                                       {POST_REDUCE(indx_parameter_declaration_0) }
                        |   declaration_specifiers                                                                                  {POST_REDUCE(indx_parameter_declaration_1) }
                        |   declaration_specifiers abstract_declarator                                                              {POST_REDUCE(indx_parameter_declaration_2) }
                        ;

identifier_list     :   identifier                                                                                                  {POST_REDUCE(indx_identifier_list_0) }
                    |   identifier_list ',' identifier                                                                              {POST_REDUCE(indx_identifier_list_1) }
                    ;

type_name       :   specifier_qualifier_list                                                                                        {POST_REDUCE(indx_type_name_0) }
                |   specifier_qualifier_list abstract_declarator                                                                    {POST_REDUCE(indx_type_name_1) }
                ;

abstract_declarator :   pointer                                                                                                     {POST_REDUCE(indx_abstract_declarator_0) }
                    |   direct_abstract_declarator                                                                                  {POST_REDUCE(indx_abstract_declarator_1) }
                    |   pointer direct_abstract_declarator                                                                          {POST_REDUCE(indx_abstract_declarator_2) }
                    ;

direct_abstract_declarator      :   '(' abstract_declarator ')'                                                                     {POST_REDUCE(indx_direct_abstract_declarator_0) }
                                |   '[' ']'                                                                                         {POST_REDUCE(indx_direct_abstract_declarator_1) }
                                |   '[' assignment_expression ']'                                                                   {POST_REDUCE(indx_direct_abstract_declarator_2) }
                                |   '[' type_qualifier_list ']'                                                                     {POST_REDUCE(indx_direct_abstract_declarator_3) }
                                |   '[' type_qualifier_list assignment_expression ']'                                               {POST_REDUCE(indx_direct_abstract_declarator_4) }
                                |   direct_abstract_declarator '[' ']'                                                              {POST_REDUCE(indx_direct_abstract_declarator_5) }
                                |   direct_abstract_declarator '[' assignment_expression ']'                                        {POST_REDUCE(indx_direct_abstract_declarator_6) }
                                |   direct_abstract_declarator '[' type_qualifier_list ']'                                          {POST_REDUCE(indx_direct_abstract_declarator_7) }
                                |   direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'                    {POST_REDUCE(indx_direct_abstract_declarator_8) }
                                |   '[' STATIC assignment_expression ']'                                                            {POST_REDUCE(indx_direct_abstract_declarator_9) }
                                |   '[' STATIC type_qualifier_list assignment_expression ']'                                        {POST_REDUCE(indx_direct_abstract_declarator_10) }
                                |   direct_abstract_declarator '[' STATIC assignment_expression ']'                                 {POST_REDUCE(indx_direct_abstract_declarator_11) }
                                |   '[' type_qualifier_list STATIC assignment_expression ']'                                        {POST_REDUCE(indx_direct_abstract_declarator_12) }
                                |   direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'             {POST_REDUCE(indx_direct_abstract_declarator_13) }
                                |   '[' '*' ']'                                                                                     {POST_REDUCE(indx_direct_abstract_declarator_14) }
                                |   direct_abstract_declarator '[' '*' ']'                                                          {POST_REDUCE(indx_direct_abstract_declarator_15) }
                                |   direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'             {POST_REDUCE(indx_direct_abstract_declarator_16) }
                                |   '(' ')'                                                                                         {POST_REDUCE(indx_direct_abstract_declarator_17) }
                                |   '(' parameter_type_list ')'                                                                     {POST_REDUCE(indx_direct_abstract_declarator_18) }
                                |   direct_abstract_declarator '(' ')'                                                              {POST_REDUCE(indx_direct_abstract_declarator_19) }
                                |   direct_abstract_declarator '(' parameter_type_list ')'                                          {POST_REDUCE(indx_direct_abstract_declarator_20) }
                                ;

 /*kersh original. can't solve the conflicts.*/
typedef_name    :   TYPEDEF_NAME                                                                                                    {POST_REDUCE(indx_typedef_name_0) }
                ;

initializer     :   assignment_expression                                                                                           {POST_REDUCE(indx_initializer_0) }
                |   '{' initializer_list '}'                                                                                        {POST_REDUCE(indx_initializer_1) }
                |   '{' initializer_list ',' '}'                                                                                    {POST_REDUCE(indx_initializer_2) }
                ;

initializer_list    :   initializer                                                                                                 {POST_REDUCE(indx_initializer_list_0) }
                    |   designation initializer                                                                                     {POST_REDUCE(indx_initializer_list_1) }
                    |   initializer_list ',' initializer                                                                            {POST_REDUCE(indx_initializer_list_2) }
                    |   initializer_list ',' designation initializer                                                                {POST_REDUCE(indx_initializer_list_3) }
                    ;

designation     :   designator_list '='                                                                                             {POST_REDUCE(indx_designation_0) }

designator_list :   designator                                                                                                      {POST_REDUCE(indx_designator_list_0) }
                |   designator_list designator                                                                                      {POST_REDUCE(indx_designator_list_1) }
                ;

designator      :   '[' constant_expression ']'                                                                                     {POST_REDUCE(indx_designator_0) }
                |   '.' identifier                                                                                                  {POST_REDUCE(indx_designator_1) }
                ;

 /*A2.3 Statements*/
statement   :   labeled_statement                                                                                                   {$$ = $1; POST_REDUCE(indx_statement_0) }
            |   compound_statement                                                                                                  {$$ = $1; POST_REDUCE(indx_statement_1) }
            |   expression_statement                                                                                                {$$ = $1; POST_REDUCE(indx_statement_2) }
            |   selection_statement                                                                                                 {$$ = $1; POST_REDUCE(indx_statement_3) }
            |   iteration_statement                                                                                                 {$$ = $1; POST_REDUCE(indx_statement_4) }
            |   jump_statement                                                                                                      {$$ = $1; POST_REDUCE(indx_statement_5) }
            ;

labeled_statement   :   identifier ':' statement                                                                                    {POST_REDUCE(indx_labeled_statement_0) }
                    |   CASE constant_expression ':' statement                                                                      {POST_REDUCE(indx_labeled_statement_1) }
                    |   DEFAULT ':' statement                                                                                       {POST_REDUCE(indx_labeled_statement_2) }
                    ;

compound_statement  :   '{' '}'                                                                                                     {POST_REDUCE(indx_compound_statement_0) }
                    |   '{' block_item_list '}'                                                                                     {$$ = alloc_cmp_statement($2); POST_REDUCE(indx_compound_statement_1) }
                    ;

block_item_list     :   block_item                                                                                                  {$$ = $1; printf("block_item: %x\n", $1); POST_REDUCE(indx_block_item_list_0) }
                    |   block_item_list block_item                                                                                  {$$ = append_block_item($1, $2); POST_REDUCE(indx_block_item_list_1) }
                    ;

block_item      :   declaration                                                                                                     {POST_REDUCE(indx_block_item_0) }
                |   statement                                                                                                       {$$ = $1; printf("statement: %x\n", $1); POST_REDUCE(indx_block_item_1) }
                ;

expression_statement    :   ';'                                                                                                     {POST_REDUCE(indx_expression_statement_0) }
                        |   expression ';'                                                                                          {$$ = alloc_exp_statement($1); POST_REDUCE(indx_expression_statement_1) }
                        ;

selection_statement     :   IF '(' expression ')' statement %prec LOWER_THAN_ELSE                                                   {POST_REDUCE(indx_selection_statement_0) }
                        |   IF '(' expression ')' statement ELSE statement                                                          {POST_REDUCE(indx_selection_statement_1) }
                        |   SWITCH '(' expression ')' statement                                                                     {POST_REDUCE(indx_selection_statement_2) }
                        ;

iteration_statement     :   WHILE '(' expression ')' statement                                                                      {POST_REDUCE(indx_iteration_statement_0) }
                        |   DO statement WHILE '(' expression ')' ';'                                                               {POST_REDUCE(indx_iteration_statement_1) }
                        |   FOR '(' ';' ';' ')' statement                                                                           {POST_REDUCE(indx_iteration_statement_2) }
                        |   FOR '(' ';' ';' expression ')' statement                                                                {POST_REDUCE(indx_iteration_statement_3) }
                        |   FOR '(' ';' expression ';' ')' statement                                                                {POST_REDUCE(indx_iteration_statement_4) }
                        |   FOR '(' ';' expression ';' expression ')' statement                                                     {POST_REDUCE(indx_iteration_statement_5) }
                        |   FOR '(' expression ';' ';' ')' statement                                                                {POST_REDUCE(indx_iteration_statement_6) }
                        |   FOR '(' expression ';' ';' expression ')' statement                                                     {POST_REDUCE(indx_iteration_statement_7) }
                        |   FOR '(' expression ';' expression ';' ')' statement                                                     {POST_REDUCE(indx_iteration_statement_8) }
                        |   FOR '(' expression ';' expression ';' expression ')' statement                                          {POST_REDUCE(indx_iteration_statement_9) }
                        |   FOR '(' declaration ';' ')' statement                                                                   {POST_REDUCE(indx_iteration_statement_10) }
                        |   FOR '(' declaration ';' expression ')' statement                                                        {POST_REDUCE(indx_iteration_statement_11) }
                        |   FOR '(' declaration expression ';' ')' statement                                                        {POST_REDUCE(indx_iteration_statement_12) }
                        |   FOR '(' declaration expression ';' expression ')' statement                                             {POST_REDUCE(indx_iteration_statement_13) }
                        ;

jump_statement      :   GOTO identifier ';'                                                                                         {$$ = alloc_jmp_statement(ST_JP_GOTO, NULL, $2);        POST_REDUCE(indx_jump_statement_0) }
                    |   CONTINUE ';'                                                                                                {$$ = alloc_jmp_statement(ST_JP_CONTINUE, NULL, NULL);  POST_REDUCE(indx_jump_statement_1) }
                    |   BREAK ';'                                                                                                   {$$ = alloc_jmp_statement(ST_JP_BREAK, NULL, NULL);     POST_REDUCE(indx_jump_statement_2) }
                    |   RETURN ';'                                                                                                  {$$ = alloc_jmp_statement(ST_JP_RETURN, NULL, NULL);    POST_REDUCE(indx_jump_statement_3) }
                    |   RETURN expression ';'                                                                                       {$$ = alloc_jmp_statement(ST_JP_RETURN, $2, NULL);      POST_REDUCE(indx_jump_statement_4) }
                    ;


 /*A2.4 External definitions*/
translation_unit    :   external_declaration                                                                                        {POST_REDUCE(indx_translation_unit_0) }
                    |   translation_unit external_declaration                                                                       {POST_REDUCE(indx_translation_unit_1) }
                    ;

external_declaration    :   function_definition                                                                                     {POST_REDUCE(indx_external_declaration_0) }
                        |   declaration                                                                                             {POST_REDUCE(indx_external_declaration_1) }
                        ;

function_definition     :   declaration_specifiers declarator compound_statement                                                    {POST_REDUCE(indx_function_definition_0) }
                        |   declaration_specifiers declarator declaration_list compound_statement                                   {POST_REDUCE(indx_function_definition_1) }
                        ;

declaration_list        :   declaration                                                                                             {POST_REDUCE(indx_declaration_list_0) }
                        |   declaration_list declaration                                                                            {POST_REDUCE(indx_declaration_list_1) }
                        ;


%%


/*main func...*/

static unsigned int line_num;

int main(int argc, char* argv[]) {
    int ret;
    int need_close;
    extern FILE* yyin;

    if (argc < 2) {
        yyin = stdin;
        need_close = 0;
    }
    else {
        yyin = fopen (argv[1], "r");
        need_close = 1;
    }

    if (yyin == NULL) {
        printf("failed to open input file [%s].\n", argv[1]);
        return 100;
    }

    printf("%s start parser...\n", argv[0]);
    line_num = 1;
    init_parser();
    ret = yyparse();
    printf("\nparse finished.\n==========================\n");
    exit_parser();
    printf("parser exit.\n");

    if (need_close) {
        fclose(yyin);
    }
    return ret;
}

void line_inc(void) {
    line_num++;
}

unsigned int get_line_num(void) {
    return line_num;
}

/*bison required functions...*/

void yyerror (char const *s) {
    fprintf (stderr, "line: %d,\n   %s\n", line_num, s);
}

int yywrap (void ) {
    return 1;
}

void init_semantic_check(void) {
    semantic_check = SEM_OK;
}

void semantic_err(const char* msg) {
    yyerror(msg);
    semantic_check = SEM_NG;
}
