
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "parser.h"
#include "expressions.h"
#include "utlist.h"


struct expression* alloc_term_exp(struct token_list* tk) {
    struct expression* e;

    e = ker_malloc(sizeof(struct expression));
    e->type = OP_TERMINAL;
    e->tk = tk;
    return e;
}

struct expression* alloc_nested_exp(struct expression* exp) {
    struct expression* ret_e;
    ret_e = ker_malloc(sizeof(struct expression));
    ret_e->type = OP_COMPOUND;
    ret_e->operand1 = exp;
    return ret_e;
}

struct expression* alloc_2op_exp (enum OP_TYPE ot, struct expression* op1, struct expression* op2) {
    struct expression* ret_e;
    ret_e = ker_malloc(sizeof(struct expression));
    ret_e->type = ot;
    ret_e->operand1 = op1;
    ret_e->operand2 = op2;
    return ret_e;
}



void identifier_0(void) {
}

void primary_expression_0(void) {
}

void primary_expression_1(void) {
}

void primary_expression_2(void) {
//    printf(" <primary_expression_2> ");
}

void primary_expression_3(void) {
    /*do nothing.*/
    //    printf(".");
}

void postfix_expression_0(void) {
}

void postfix_expression_1(void) {
    //    printf(" <postfix_expression_1> ");
}

void postfix_expression_2(void) {
    //    printf(" <postfix_expression_2> ");
}

void postfix_expression_3(void) {
    //    printf(" <postfix_expression_3> ");
}

void postfix_expression_4(void) {
    //    printf(" <postfix_expression_4> ");
}

void postfix_expression_5(void) {
    //    printf(" <postfix_expression_5> ");
}

void postfix_expression_6(void) {
    //    printf(" <postfix_expression_6> ");
}

void postfix_expression_7(void) {
    //    printf(" <postfix_expression_7> ");
}

void postfix_expression_8(void) {
    //    printf(" <postfix_expression_8> ");
}

void postfix_expression_9(void) {
    //    printf(" <postfix_expression_9> ");
}

void unary_expression_0(void) {
}

void unary_expression_1(void) {
    //    printf(" <unary_expression_1> ");
}

void unary_expression_2(void) {
    //    printf(" <unary_expression_2> ");
}

void unary_expression_3(void) {
    //    printf(" <unary_expression_3> ");
}

void unary_expression_4(void) {
    //    printf(" <unary_expression_4> ");
}

void unary_expression_5(void) {
    //    printf(" <unary_expression_5> ");
}

void cast_expression_1(void) {
    //    printf(" <cast_expression_1> ");
}

void multipricative_expression_1(void) {
}

void multipricative_expression_2(void) {
}

void multipricative_expression_3(void) {
    //    printf(" <multipricative_expression_3> ");
}

void additive_expression_1(void) {
}

void additive_expression_2(void) {
    //    printf(" <additive_expression_2> ");
}

void shift_expression_1(void) {
    //    printf(" <shift_expression_1> ");
}

void shift_expression_2(void) {
    //    printf(" <shift_expression_2> ");
}

void relational_expression_1(void) {
    //    printf(" <relational_expression_1> ");
}

void relational_expression_2(void) {
    //    printf(" <relational_expression_2> ");
}

void relational_expression_3(void) {
    //    printf(" <relational_expression_3> ");
}

void relational_expression_4(void) {
    //    printf(" <relational_expression_4> ");
}

void equality_expression_1(void) {
    //    printf(" <equality_expression_1> ");
}

void equality_expression_2(void) {
    //    printf(" <equality_expression_2> ");
}

void AND_expression_1(void) {
    //    printf(" <AND_expression_1> ");
}

void exclusive_OR_expression_1(void) {
    //    printf(" <exclusive_OR_expression_1> ");
}

void inclusive_OR_expression_1(void) {
    //    printf(" <inclusive_OR_expression_1> ");
}

void logical_AND_expression_1(void) {
    //    printf(" <logical_AND_expression_1> ");
}

void logical_OR_expression_1(void) {
    //    printf(" <logical_OR_expression_1> ");
}

void conditional_expression_1(void) {
    //    printf(" <conditional_expression_1> ");
}

void assignment_expression_1(void) {
    //    printf(" <assignment_expression_1> ");
}

void init_expression(void) {
}


