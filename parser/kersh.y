%{

/*kersh.tab.c*/

#include <stdio.h>
#include "kersh.h"
#include "kersh.tab.h"
#include "parser.h"
#include "symbols.h"
#include "idtbl.h"
#include "reduce.h"

#define     dprint(msg)    printf("  << %s...\n", msg)

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

 /*A.1.3 Identifiers*/
identifier  :   IDEN                                                                                                                {post_reduce_action(identifier_0); }
            ;
 /*
 A.1.4
 universal character name
 \u0011 \uxxxx etc. not supported...
 */


 /*A.1.5 Constants*/
constant    :   integer_constant                                                                                                    {post_reduce_action(indx_constant_0); }
            |   emumeration_constant                                                                                                {post_reduce_action(indx_constant_1); }
            |   character_constant                                                                                                  {post_reduce_action(indx_constant_2); }
            ;

integer_constant    :   DECIMAL_CONSTANT                                                                                            {post_reduce_action(indx_integer_constant_0); }
                    |   OCTAL_CONSTANT                                                                                              {post_reduce_action(indx_integer_constant_1); }
                    |   HEX_CONSTANT                                                                                                {post_reduce_action(indx_integer_constant_2); }
                    ;

 /*kersh original. can't solve the conflicts.*/
emumeration_constant    :   ENUM_CONSTANT                                                                                           {post_reduce_action(indx_emumeration_constant_0); }
                        ;

character_constant      :   C_CHAR                                                                                                  {post_reduce_action(indx_character_constant_0); }
                        ;


 /*A.1.6 String literals*/
string_literal          :   S_CHAR                                                                                                  {post_reduce_action(indx_string_literal_0); }
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
primary_expression  :   identifier                                                                                                  {post_reduce_action(indx_primary_expression_0); }
                    |   constant                                                                                                    {post_reduce_action(indx_primary_expression_1); }
                    |   string_literal                                                                                              {post_reduce_action(indx_primary_expression_2); }
                    |   '(' expression ')'                                                                                          {post_reduce_action(indx_primary_expression_3); }
                    ;

postfix_expression  :   primary_expression                                                                                          {post_reduce_action(indx_postfix_expression_0); }
                    |   postfix_expression '[' expression ']'                                                                       {post_reduce_action(indx_postfix_expression_1); }
                    |   postfix_expression '(' argument_expression_list ')'                                                         {post_reduce_action(indx_postfix_expression_2); }
                    |   postfix_expression '(' ')'                                                                                  {post_reduce_action(indx_postfix_expression_3); }
                    |   postfix_expression '.' identifier                                                                           {post_reduce_action(indx_postfix_expression_4); }
                    |   postfix_expression ARROW identifier                                                                         {post_reduce_action(indx_postfix_expression_5); }
                    |   postfix_expression INC                                                                                      {post_reduce_action(indx_postfix_expression_6); }
                    |   postfix_expression DEC                                                                                      {post_reduce_action(indx_postfix_expression_7); }
                    |   '(' type_name ')' '{' initializer_list '}'                                                                  {post_reduce_action(indx_postfix_expression_8); }
                    |   '(' type_name ')' '{' initializer_list ',' '}'                                                              {post_reduce_action(indx_postfix_expression_9); }
                    ;

argument_expression_list    :   assignment_expression                                                                               {post_reduce_action(indx_argument_expression_list_0); }
                            |   argument_expression_list ',' assignment_expression                                                  {post_reduce_action(indx_argument_expression_list_1); }
                            ;

unary_expression    :   postfix_expression                                                                                          {post_reduce_action(indx_unary_expression_0); }
                    |   INC unary_expression                                                                                        {post_reduce_action(indx_unary_expression_1); }
                    |   DEC unary_expression                                                                                        {post_reduce_action(indx_unary_expression_2); }
                    |   unary_operator cast_expression                                                                              {post_reduce_action(indx_unary_expression_3); }
                    |   SIZEOF unary_expression                                                                                     {post_reduce_action(indx_unary_expression_4); }
                    |   SIZEOF '(' type_name ')'                                                                                    {post_reduce_action(indx_unary_expression_5); }
                    ;

unary_operator      :   '&'                                                                                                         {post_reduce_action(indx_unary_operator_0); }
                    |   '*'                                                                                                         {post_reduce_action(indx_unary_operator_1); }
                    |   '+'                                                                                                         {post_reduce_action(indx_unary_operator_2); }
                    |   '-'                                                                                                         {post_reduce_action(indx_unary_operator_3); }
                    |   '~'                                                                                                         {post_reduce_action(indx_unary_operator_4); }
                    |   '!'                                                                                                         {post_reduce_action(indx_unary_operator_5); }
                    ;

cast_expression     :   unary_expression                                                                                            {post_reduce_action(indx_cast_expression_0); }
                    |   '(' type_name ')' cast_expression                                                                           {post_reduce_action(indx_cast_expression_1); }
                    ;

multipricative_expression   :   cast_expression                                                                                     {post_reduce_action(indx_multipricative_expression_0); }
                            |   multipricative_expression '*' cast_expression                                                       {post_reduce_action(indx_multipricative_expression_1); }
                            |   multipricative_expression '/' cast_expression                                                       {post_reduce_action(indx_multipricative_expression_2); }
                            |   multipricative_expression '%' cast_expression                                                       {post_reduce_action(indx_multipricative_expression_3); }
                            ;

additive_expression     :   multipricative_expression                                                                               {post_reduce_action(indx_additive_expression_0); }
                        |   additive_expression '+' multipricative_expression                                                       {post_reduce_action(indx_additive_expression_1); }
                        |   additive_expression '-' multipricative_expression                                                       {post_reduce_action(indx_additive_expression_2); }
                        ;

shift_expression        :   additive_expression                                                                                     {post_reduce_action(indx_shift_expression_0); }
                        |   shift_expression LSHIFT additive_expression                                                             {post_reduce_action(indx_shift_expression_1); }
                        |   shift_expression RSHIFT additive_expression                                                             {post_reduce_action(indx_shift_expression_2); }
                        ;

retional_expression     :   shift_expression                                                                                        {post_reduce_action(indx_retional_expression_0); }
                        |   retional_expression '<' shift_expression                                                                {post_reduce_action(indx_retional_expression_1); }
                        |   retional_expression '>' shift_expression                                                                {post_reduce_action(indx_retional_expression_2); }
                        |   retional_expression LE shift_expression                                                                 {post_reduce_action(indx_retional_expression_3); }
                        |   retional_expression GE shift_expression                                                                 {post_reduce_action(indx_retional_expression_4); }
                        ;

equality_expression     :   retional_expression                                                                                     {post_reduce_action(indx_equality_expression_0); }
                        |   equality_expression EQEQ retional_expression                                                            {post_reduce_action(indx_equality_expression_1); }
                        |   equality_expression NE retional_expression                                                              {post_reduce_action(indx_equality_expression_2); }
                        ;

AND_expression          :   equality_expression                                                                                     {post_reduce_action(indx_AND_expression_0); }
                        |   AND_expression '&' equality_expression                                                                  {post_reduce_action(indx_AND_expression_1); }
                        ;

exclusive_OR_expression     :   AND_expression                                                                                      {post_reduce_action(indx_exclusive_OR_expression_0); }
                            |   exclusive_OR_expression '^' AND_expression                                                          {post_reduce_action(indx_exclusive_OR_expression_1); }
                            ;

inclusive_OR_expression     :   exclusive_OR_expression                                                                             {post_reduce_action(indx_inclusive_OR_expression_0); }
                            |   inclusive_OR_expression '|' exclusive_OR_expression                                                 {post_reduce_action(indx_inclusive_OR_expression_1); }
                            ;

logical_AND_expression      :   inclusive_OR_expression                                                                             {post_reduce_action(indx_logical_AND_expression_0); }
                            |   logical_AND_expression L_AND inclusive_OR_expression                                                {post_reduce_action(indx_logical_AND_expression_1); }
                            ;

logical_OR_expression       :   logical_AND_expression                                                                              {post_reduce_action(indx_logical_OR_expression_0); }
                            |   logical_OR_expression L_OR logical_AND_expression                                                   {post_reduce_action(indx_logical_OR_expression_1); }
                            ;

conditional_expression      :   logical_OR_expression                                                                               {post_reduce_action(indx_conditional_expression_0); }
                            |   logical_OR_expression '?' expression ':' conditional_expression                                     {post_reduce_action(indx_conditional_expression_1); }
                            ;

assignment_expression       :   conditional_expression                                                                              {post_reduce_action(indx_assignment_expression_0); }
                            |   unary_expression assignment_operator assignment_expression                                          {post_reduce_action(indx_assignment_expression_1); }
                            ;

assignment_operator         :   '='                                                                                                 {post_reduce_action(indx_assignment_operator_0); }
                            |   ASTR_EQ                                                                                             {post_reduce_action(indx_assignment_operator_1); }
                            |   DASH_EQ                                                                                             {post_reduce_action(indx_assignment_operator_2); }
                            |   PERC_EQ                                                                                             {post_reduce_action(indx_assignment_operator_3); }
                            |   PLUS_EQ                                                                                             {post_reduce_action(indx_assignment_operator_4); }
                            |   MINUS_EQ                                                                                            {post_reduce_action(indx_assignment_operator_5); }
                            |   LSHIFT_EQ                                                                                           {post_reduce_action(indx_assignment_operator_6); }
                            |   RSHIFT_EQ                                                                                           {post_reduce_action(indx_assignment_operator_7); }
                            |   AMP_EQ                                                                                              {post_reduce_action(indx_assignment_operator_8); }
                            |   HAT_EQ                                                                                              {post_reduce_action(indx_assignment_operator_9); }
                            |   OR_EQ                                                                                               {post_reduce_action(indx_assignment_operator_10); }
                            ;

expression      :   assignment_expression                                                                                           {post_reduce_action(indx_expression_0); }
                |   expression ',' assignment_expression                                                                            {post_reduce_action(indx_expression_1); }
                ;

constant_expression :   conditional_expression                                                                                      {post_reduce_action(indx_constant_expression_0); }
                    ;


 /*A2.2 Declarations*/
declaration     :   declaration_specifiers ';'                                                                                      {post_reduce_action(indx_declaration_0); }
                |   declaration_specifiers init_declarator_list ';'                                                                 {post_reduce_action(indx_declaration_1); }
                ;

declaration_specifiers  :   storage_class_specifier                                                                                 {post_reduce_action(indx_declaration_specifiers_0); }
                        |   storage_class_specifier declaration_specifiers                                                          {post_reduce_action(indx_declaration_specifiers_1); }
                        |   type_specifier                                                                                          {post_reduce_action(indx_declaration_specifiers_2); }
                        |   type_specifier declaration_specifiers                                                                   {post_reduce_action(indx_declaration_specifiers_3); }
                        |   type_qualifier                                                                                          {post_reduce_action(indx_declaration_specifiers_4); }
                        |   type_qualifier declaration_specifiers                                                                   {post_reduce_action(indx_declaration_specifiers_5); }
                        |   function_speficier                                                                                      {post_reduce_action(indx_declaration_specifiers_6); }
                        |   function_speficier declaration_specifiers                                                               {post_reduce_action(indx_declaration_specifiers_7); }
                        ;

 /* not supported...
                        |   alignment_specifier declaration_specifiers
                        |   alignment_specifier
 */

init_declarator_list    :   init_declarator                                                                                         {post_reduce_action(indx_init_declarator_list_0); }
                        |   init_declarator_list ',' init_declarator                                                                {post_reduce_action(indx_init_declarator_list_1); }
                        ;

init_declarator         :   declarator                                                                                              {post_reduce_action(indx_init_declarator_0); }
                        |   declarator '=' initializer                                                                              {post_reduce_action(indx_init_declarator_1); }
                        ;

storage_class_specifier     :   TYPEDEF                                                                                             {post_reduce_action(indx_storage_class_specifier_0); }
                            |   EXTERN                                                                                              {post_reduce_action(indx_storage_class_specifier_1); }
                            |   STATIC                                                                                              {post_reduce_action(indx_storage_class_specifier_2); }
                            |   AUTO                                                                                                {post_reduce_action(indx_storage_class_specifier_3); }
                            |   REGISTER                                                                                            {post_reduce_action(indx_storage_class_specifier_4); }
                            ;

type_specifier  :   VOID                                                                                                            {post_reduce_action(indx_type_specifier_0); }
                |   CHAR                                                                                                            {post_reduce_action(indx_type_specifier_1); }
                |   SHORT                                                                                                           {post_reduce_action(indx_type_specifier_2); }
                |   INT                                                                                                             {post_reduce_action(indx_type_specifier_3); }
                |   LONG                                                                                                            {post_reduce_action(indx_type_specifier_4); }
                |   SIGNED                                                                                                          {post_reduce_action(indx_type_specifier_5); }
                |   UNSIGNED                                                                                                        {post_reduce_action(indx_type_specifier_6); }
                |   struct_or_union_specifier                                                                                       {post_reduce_action(indx_type_specifier_7); }
                |   enum_specifier                                                                                                  {post_reduce_action(indx_type_specifier_8); }
                |   typedef_name                                                                                                    {post_reduce_action(indx_type_specifier_9); }
                ;


struct_or_union_specifier   :   struct_or_union '{' struct_declaration_list '}'                                                     {post_reduce_action(indx_struct_or_union_specifier_0); }
                            |   struct_or_union identifier '{' struct_declaration_list '}'                                          {post_reduce_action(indx_struct_or_union_specifier_1); }
                            |   struct_or_union identifier                                                                          {post_reduce_action(indx_struct_or_union_specifier_2); }
                            ;

struct_or_union     :   STRUCT                                                                                                      {post_reduce_action(indx_struct_or_union_0); }
                    |   UNION                                                                                                       {post_reduce_action(indx_struct_or_union_1); }
                    ;

struct_declaration_list     :   struct_declaration                                                                                  {post_reduce_action(indx_struct_declaration_list_0); }
                            |   struct_declaration_list struct_declaration                                                          {post_reduce_action(indx_struct_declaration_list_1); }
                            ;

struct_declaration      :   specifier_qualifier_list ';'                                                                            {post_reduce_action(indx_struct_declaration_0); }
                        |   specifier_qualifier_list struct_declarator_list ';'                                                     {post_reduce_action(indx_struct_declaration_1); }
                        ;

specifier_qualifier_list    :   type_specifier                                                                                      {post_reduce_action(indx_specifier_qualifier_list_0); }
                            |   type_specifier specifier_qualifier_list                                                             {post_reduce_action(indx_specifier_qualifier_list_1); }
                            |   type_qualifier                                                                                      {post_reduce_action(indx_specifier_qualifier_list_2); }
                            |   type_qualifier specifier_qualifier_list                                                             {post_reduce_action(indx_specifier_qualifier_list_3); }
                            ;

struct_declarator_list      :   struct_declarator                                                                                   {post_reduce_action(indx_struct_declarator_list_0); }
                            |   struct_declarator_list ',' struct_declarator                                                        {post_reduce_action(indx_struct_declarator_list_1); }
                            ;

struct_declarator   :   declarator                                                                                                  {post_reduce_action(indx_struct_declarator_0); }
                    |   ':' constant_expression                                                                                     {post_reduce_action(indx_struct_declarator_1); }
                    |   declarator ':' constant_expression                                                                          {post_reduce_action(indx_struct_declarator_2); }
                    ;

enum_specifier      :   ENUM '{' emumerator_list '}'                                                                                {post_reduce_action(indx_enum_specifier_0); }
                    |   ENUM identifier '{' emumerator_list '}'                                                                     {post_reduce_action(indx_enum_specifier_1); }
                    |   ENUM '{' emumerator_list ',' '}'                                                                            {post_reduce_action(indx_enum_specifier_2); }
                    |   ENUM identifier '{' emumerator_list ',' '}'                                                                 {post_reduce_action(indx_enum_specifier_3); }
                    |   ENUM identifier                                                                                             {post_reduce_action(indx_enum_specifier_4); }
                    ;

emumerator_list     :   emumerator                                                                                                  {post_reduce_action(indx_emumerator_list_0); }
                    |   emumerator_list ',' emumerator                                                                              {post_reduce_action(indx_emumerator_list_1); }
                    ;

emumerator      :   emumeration_constant                                                                                            {post_reduce_action(indx_emumerator_0); }
                |   emumeration_constant '=' constant_expression                                                                    {post_reduce_action(indx_emumerator_1); }
                ;

type_qualifier      :   CONST                                                                                                       {post_reduce_action(indx_type_qualifier_0); }
                    |   VOLATILE                                                                                                    {post_reduce_action(indx_type_qualifier_1); }
                    ;

function_speficier  :   INLINE                                                                                                      {post_reduce_action(indx_function_speficier_0); }
                    ;

declarator      :   direct_declarator                                                                                               {post_reduce_action(indx_declarator_0); }
                |   pointer direct_declarator                                                                                       {post_reduce_action(indx_declarator_1); }
                ;

direct_declarator   :   identifier                                                                                                  {post_reduce_action(indx_direct_declarator_0); }
                    |   '(' declarator ')'                                                                                          {post_reduce_action(indx_direct_declarator_1); }
                    |   direct_declarator '[' ']'                                                                                   {post_reduce_action(indx_direct_declarator_2); }
                    |   direct_declarator '[' assignment_expression ']'                                                             {post_reduce_action(indx_direct_declarator_3); }
                    |   direct_declarator '[' type_qualifier ']'                                                                    {post_reduce_action(indx_direct_declarator_4); }
                    |   direct_declarator '[' type_qualifier assignment_expression ']'                                              {post_reduce_action(indx_direct_declarator_5); }
                    |   direct_declarator '[' STATIC assignment_expression ']'                                                      {post_reduce_action(indx_direct_declarator_6); }
                    |   direct_declarator '[' STATIC type_qualifier assignment_expression ']'                                       {post_reduce_action(indx_direct_declarator_7); }
                    |   direct_declarator '[' type_qualifier STATIC assignment_expression ']'                                       {post_reduce_action(indx_direct_declarator_8); }
                    |   direct_declarator '[' '*' ']'                                                                               {post_reduce_action(indx_direct_declarator_9); }
                    |   direct_declarator '[' type_qualifier '*' ']'                                                                {post_reduce_action(indx_direct_declarator_10); }
                    |   direct_declarator '(' parameter_type_list ')'                                                               {post_reduce_action(indx_direct_declarator_11); }
                    |   direct_declarator '(' ')'                                                                                   {post_reduce_action(indx_direct_declarator_12); }
                    |   direct_declarator '(' identifier_list ')'                                                                   {post_reduce_action(indx_direct_declarator_13); }
                    ;

pointer     :   '*'                                                                                                                 {post_reduce_action(indx_pointer_0); }
            |   '*' type_qualifier_list                                                                                             {post_reduce_action(indx_pointer_1); }
            |   '*' pointer                                                                                                         {post_reduce_action(indx_pointer_2); }
            |   '*' type_qualifier_list pointer                                                                                     {post_reduce_action(indx_pointer_3); }
            ;

type_qualifier_list     :   type_qualifier                                                                                          {post_reduce_action(indx_type_qualifier_list_0); }
                        |   type_qualifier_list type_qualifier                                                                      {post_reduce_action(indx_type_qualifier_list_1); }
                        ;

parameter_type_list     :   parameter_list                                                                                          {post_reduce_action(indx_parameter_type_list_0); }
                        |   parameter_list ',' DOT3                                                                                 {post_reduce_action(indx_parameter_type_list_1); }
                        ;

parameter_list      :   parameter_declaration                                                                                       {post_reduce_action(indx_parameter_list_0); }
                    |   parameter_list ',' parameter_declaration                                                                    {post_reduce_action(indx_parameter_list_1); }
                    ;

parameter_declaration   :   declaration_specifiers declarator                                                                       {post_reduce_action(indx_parameter_declaration_0); }
                        |   declaration_specifiers                                                                                  {post_reduce_action(indx_parameter_declaration_1); }
                        |   declaration_specifiers abstract_declarator                                                              {post_reduce_action(indx_parameter_declaration_2); }
                        ;

identifier_list     :   identifier                                                                                                  {post_reduce_action(indx_identifier_list_0); }
                    |   identifier_list ',' identifier                                                                              {post_reduce_action(indx_identifier_list_1); }
                    ;

type_name       :   specifier_qualifier_list                                                                                        {post_reduce_action(indx_type_name_0); }
                |   specifier_qualifier_list abstract_declarator                                                                    {post_reduce_action(indx_type_name_1); }
                ;

abstract_declarator :   pointer                                                                                                     {post_reduce_action(indx_abstract_declarator_0); }
                    |   direct_abstract_declarator                                                                                  {post_reduce_action(indx_abstract_declarator_1); }
                    |   pointer direct_abstract_declarator                                                                          {post_reduce_action(indx_abstract_declarator_2); }
                    ;

direct_abstract_declarator      :   '(' abstract_declarator ')'                                                                     {post_reduce_action(indx_direct_abstract_declarator_0); }
                                |   '[' ']'                                                                                         {post_reduce_action(indx_direct_abstract_declarator_1); }
                                |   '[' assignment_expression ']'                                                                   {post_reduce_action(indx_direct_abstract_declarator_2); }
                                |   '[' type_qualifier_list ']'                                                                     {post_reduce_action(indx_direct_abstract_declarator_3); }
                                |   '[' type_qualifier_list assignment_expression ']'                                               {post_reduce_action(indx_direct_abstract_declarator_4); }
                                |   direct_abstract_declarator '[' ']'                                                              {post_reduce_action(indx_direct_abstract_declarator_5); }
                                |   direct_abstract_declarator '[' assignment_expression ']'                                        {post_reduce_action(indx_direct_abstract_declarator_6); }
                                |   direct_abstract_declarator '[' type_qualifier_list ']'                                          {post_reduce_action(indx_direct_abstract_declarator_7); }
                                |   direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'                    {post_reduce_action(indx_direct_abstract_declarator_8); }
                                |   '[' STATIC assignment_expression ']'                                                            {post_reduce_action(indx_direct_abstract_declarator_9); }
                                |   '[' STATIC type_qualifier_list assignment_expression ']'                                        {post_reduce_action(indx_direct_abstract_declarator_10); }
                                |   direct_abstract_declarator '[' STATIC assignment_expression ']'                                 {post_reduce_action(indx_direct_abstract_declarator_11); }
                                |   '[' type_qualifier_list STATIC assignment_expression ']'                                        {post_reduce_action(indx_direct_abstract_declarator_12); }
                                |   direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'             {post_reduce_action(indx_direct_abstract_declarator_13); }
                                |   '[' '*' ']'                                                                                     {post_reduce_action(indx_direct_abstract_declarator_14); }
                                |   direct_abstract_declarator '[' '*' ']'                                                          {post_reduce_action(indx_direct_abstract_declarator_15); }
                                |   direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'             {post_reduce_action(indx_direct_abstract_declarator_16); }
                                |   '(' ')'                                                                                         {post_reduce_action(indx_direct_abstract_declarator_17); }
                                |   '(' parameter_type_list ')'                                                                     {post_reduce_action(indx_direct_abstract_declarator_18); }
                                |   direct_abstract_declarator '(' ')'                                                              {post_reduce_action(indx_direct_abstract_declarator_19); }
                                |   direct_abstract_declarator '(' parameter_type_list ')'                                          {post_reduce_action(indx_direct_abstract_declarator_20); }
                                ;

 /*kersh original. can't solve the conflicts.*/
typedef_name    :   TYPEDEF_NAME                                                                                                    {post_reduce_action(indx_typedef_name_0); }
                ;

initializer     :   assignment_expression                                                                                           {post_reduce_action(indx_initializer_0); }
                |   '{' initializer_list '}'                                                                                        {post_reduce_action(indx_initializer_1); }
                |   '{' initializer_list ',' '}'                                                                                    {post_reduce_action(indx_initializer_2); }
                ;

initializer_list    :   initializer                                                                                                 {post_reduce_action(indx_initializer_list_0); }
                    |   designation initializer                                                                                     {post_reduce_action(indx_initializer_list_1); }
                    |   initializer_list ',' initializer                                                                            {post_reduce_action(indx_initializer_list_2); }
                    |   initializer_list ',' designation initializer                                                                {post_reduce_action(indx_initializer_list_3); }
                    ;

designation     :   designator_list '='                                                                                             {post_reduce_action(indx_designation_0); }

designator_list :   designator                                                                                                      {post_reduce_action(indx_designator_list_0); }
                |   designator_list designator                                                                                      {post_reduce_action(indx_designator_list_1); }
                ;

designator      :   '[' constant_expression ']'                                                                                     {post_reduce_action(indx_designator_0); }
                |   '.' identifier                                                                                                  {post_reduce_action(indx_designator_1); }
                ;

 /*A2.3 Statements*/
statement   :   labeled_statement                                                                                                   {post_reduce_action(indx_statement_0); }
            |   compound_statement                                                                                                  {post_reduce_action(indx_statement_1); }
            |   expression_statement                                                                                                {post_reduce_action(indx_statement_2); }
            |   selection_statement                                                                                                 {post_reduce_action(indx_statement_3); }
            |   iteration_statement                                                                                                 {post_reduce_action(indx_statement_4); }
            |   jump_statement                                                                                                      {post_reduce_action(indx_statement_5); }
            ;

labeled_statement   :   identifier ':' statement                                                                                    {post_reduce_action(indx_labeled_statement_0); }
                    |   CASE constant_expression ':' statement                                                                      {post_reduce_action(indx_labeled_statement_1); }
                    |   DEFAULT ':' statement                                                                                       {post_reduce_action(indx_labeled_statement_2); }
                    ;

compound_statement  :   '{' '}'                                                                                                     {post_reduce_action(indx_compound_statement_0); }
                    |   '{' block_item_list '}'                                                                                     {post_reduce_action(indx_compound_statement_1); }
                    ;

block_item_list     :   block_item                                                                                                  {post_reduce_action(indx_block_item_list_0); }
                    |   block_item_list block_item                                                                                  {post_reduce_action(indx_block_item_list_1); }
                    ;

block_item      :   declaration                                                                                                     {post_reduce_action(indx_block_item_0); }
                |   statement                                                                                                       {post_reduce_action(indx_block_item_1); }
                ;

expression_statement    :   ';'                                                                                                     {post_reduce_action(indx_expression_statement_0); }
                        |   expression ';'                                                                                          {post_reduce_action(indx_expression_statement_1); }
                        ;

selection_statement     :   IF '(' expression ')' statement %prec LOWER_THAN_ELSE                                                   {post_reduce_action(indx_selection_statement_0); }
                        |   IF '(' expression ')' statement ELSE statement                                                          {post_reduce_action(indx_selection_statement_1); }
                        |   SWITCH '(' expression ')' statement                                                                     {post_reduce_action(indx_selection_statement_2); }
                        ;

iteration_statement     :   WHILE '(' expression ')' statement                                                                      {post_reduce_action(indx_iteration_statement_0); }
                        |   DO statement WHILE '(' expression ')' ';'                                                               {post_reduce_action(indx_iteration_statement_1); }
                        |   FOR '(' ';' ';' ')' statement                                                                           {post_reduce_action(indx_iteration_statement_2); }
                        |   FOR '(' ';' ';' expression ')' statement                                                                {post_reduce_action(indx_iteration_statement_3); }
                        |   FOR '(' ';' expression ';' ')' statement                                                                {post_reduce_action(indx_iteration_statement_4); }
                        |   FOR '(' ';' expression ';' expression ')' statement                                                     {post_reduce_action(indx_iteration_statement_5); }
                        |   FOR '(' expression ';' ';' ')' statement                                                                {post_reduce_action(indx_iteration_statement_6); }
                        |   FOR '(' expression ';' ';' expression ')' statement                                                     {post_reduce_action(indx_iteration_statement_7); }
                        |   FOR '(' expression ';' expression ';' ')' statement                                                     {post_reduce_action(indx_iteration_statement_8); }
                        |   FOR '(' expression ';' expression ';' expression ')' statement                                          {post_reduce_action(indx_iteration_statement_9); }
                        |   FOR '(' declaration ';' ')' statement                                                                   {post_reduce_action(indx_iteration_statement_10); }
                        |   FOR '(' declaration ';' expression ')' statement                                                        {post_reduce_action(indx_iteration_statement_11); }
                        |   FOR '(' declaration expression ';' ')' statement                                                        {post_reduce_action(indx_iteration_statement_12); }
                        |   FOR '(' declaration expression ';' expression ')' statement                                             {post_reduce_action(indx_iteration_statement_13); }
                        ;

jump_statement      :   GOTO identifier ';'                                                                                         {post_reduce_action(indx_jump_statement_0); }
                    |   CONTINUE ';'                                                                                                {post_reduce_action(indx_jump_statement_1); }
                    |   BREAK ';'                                                                                                   {post_reduce_action(indx_jump_statement_2); }
                    |   RETURN ';'                                                                                                  {post_reduce_action(indx_jump_statement_3); }
                    |   RETURN expression ';'                                                                                       {post_reduce_action(indx_jump_statement_4); }
                    ;


 /*A2.4 External definitions*/
translation_unit    :   external_declaration                                                                                        {post_reduce_action(indx_translation_unit_0); }
                    |   translation_unit external_declaration                                                                       {post_reduce_action(indx_translation_unit_1); }
                    ;

external_declaration    :   function_definition                                                                                     {post_reduce_action(indx_external_declaration_0); }
                        |   declaration                                                                                             {post_reduce_action(indx_external_declaration_1); }
                        ;

function_definition     :   declaration_specifiers declarator compound_statement                                                    {post_reduce_action(indx_function_definition_0); }
                        |   declaration_specifiers declarator declaration_list compound_statement                                   {post_reduce_action(indx_function_definition_1); }
                        ;

declaration_list        :   declaration                                                                                             {post_reduce_action(indx_declaration_list_0); }
                        |   declaration_list declaration                                                                            {post_reduce_action(indx_declaration_list_1); }
                        ;


%%


/*main func...*/


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
    init_parser();
    init_symtable();
    ret = yyparse();
    clear_symtable();
    exit_parser();
    printf("parser done.\n");

    if (need_close) {
        fclose(yyin);
    }
    return ret;
}
