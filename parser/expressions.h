
#ifndef __expressions_h__
#define __expressions_h__

#include "parser.h"

enum OP_TYPE {
    OP_INVALID,

    /*no operation*/
    OP_TERMINAL,

    /*case '(' expression ')' */
    OP_COMPOUND,

    /*postfix_expression*/
    OP_ARRAY_ELM,
    OP_FUNCCALL,
    OP_DOT,
    OP_ARROW,
    OP_RINC,
    OP_RDEC,
    OP_STRUCT_INIT,

    /*unary_expression*/
    OP_LINC,
    OP_LDEC,
    OP_SIZEOF,

    /*cast_expression*/
    OP_CAST,

    /*multipricative_expression*/
    OP_MUL,
    OP_DIV,
    OP_MOD,

    /*additive_expression*/
    OP_PLUS,
    OP_MINUS,

    /*shift_expression*/
    OP_LSHIFT,
    OP_RSHIFT,

    /*relational_expression*/
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE,

    /*equality_expression*/
    OP_EQEQ,
    OP_NE,

    /*AND_expression*/
    OP_AND,

    /*inclusive_OR_expression*/
    OP_OR,

    /*logical_AND_expression*/
    OP_LAND,

    /*logical_OR_expression*/
    OP_LOR,

    /*conditional_expression*/
    OP_3COND,

    /*assignment_expression*/
    OP_EQ,
    OP_ASTR_EQ,
    OP_DASH_EQ,
    OP_PERC_EQ,
    OP_PLUS_EQ,
    OP_MINUS_EQ,
    OP_LSHIFT_EQ,
    OP_RSHIFT_EQ,
    OP_AMP_EQ,
    OP_HAT_EQ,
    OP_OR_EQ,
};

struct expression {
    enum OP_TYPE type;
    union {
        /*terminal node*/
        struct {
            struct token_list * tk;
        };

        /*non terminal node*/
        struct {
            struct expression * operand1;
            struct expression * operand2;
            struct expression * operand3;
        };
    };
};

struct expression* alloc_term_exp(struct token_list* tk);
struct expression* alloc_nested_exp(struct expression* exp);
struct expression* alloc_2op_exp(enum OP_TYPE ot, struct expression* op1, struct expression* op2);

void print_exp(struct expression* exp);

void primary_expression_0(void);
void primary_expression_1(void);
void primary_expression_2(void);
void primary_expression_3(void);

void postfix_expression_0(void);
void postfix_expression_1(void);
void postfix_expression_2(void);
void postfix_expression_3(void);
void postfix_expression_4(void);
void postfix_expression_5(void);
void postfix_expression_6(void);
void postfix_expression_7(void);
void postfix_expression_8(void);
void postfix_expression_9(void);

void unary_expression_0(void);
void unary_expression_1(void);
void unary_expression_2(void);
void unary_expression_3(void);
void unary_expression_4(void);
void unary_expression_5(void);


void cast_expression_1(void);

void multipricative_expression_1(void);
void multipricative_expression_2(void);
void multipricative_expression_3(void);

void additive_expression_1(void);
void additive_expression_2(void);

void shift_expression_1(void);
void shift_expression_2(void);

void relational_expression_1(void);
void relational_expression_2(void);
void relational_expression_3(void);
void relational_expression_4(void);

void equality_expression_1(void);
void equality_expression_2(void);

void AND_expression_1(void);

void exclusive_OR_expression_1(void);

void inclusive_OR_expression_1(void);

void logical_AND_expression_1(void);

void logical_OR_expression_1(void);

void conditional_expression_1(void);

void assignment_expression_1(void);

void init_expression(void);
void exit_expression(void);

#endif /*__expressions_h__*/

