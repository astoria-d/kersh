
#ifndef __expressions_h__
#define __expressions_h__

#include "types.h"

enum TP_VAL {
    TP_LVAL,
    TP_RVAL,
};

enum OP_TYPE {
    OP_INVALID,

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
    struct type_definition*     inst;
    enum TP_VAL                 lr;
    enum OP_TYPE                op;
    long                        value;
    struct token_list*          operand1;
    struct token_list*          operand2;
    struct token_list*          operand3;
    struct expression*          sub_exp1;
    struct expression*          sub_exp2;
    struct expression*          sub_exp3;
    struct expression*          next;
};

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

