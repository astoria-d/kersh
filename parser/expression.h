
#ifndef __expression_h__
#define __expression_h__

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

    /*XOR expression*/
    OP_XOR,

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
            struct ctoken * tk;
        };

        /*non terminal node*/
        struct {
            struct expression *         ope1;
            union {
                struct expression *     ope2;
                struct type_specifier*  cast;
            };
            struct expression *         ope3;
        };
    };
};

struct expression* alloc_term_exp(struct ctoken* tk);
struct expression* alloc_nested_exp(struct expression* exp);
struct expression* alloc_2op_exp(enum OP_TYPE ot, struct expression* op1, struct expression* op2);
struct expression* alloc_cast_exp(struct type_specifier* cast, struct expression* exp);

void dump_expression(struct expression* exp, int indent);

#endif /*__expression_h__*/
