
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "expressions.h"
#include "utlist.h"


struct expression* alloc_term_exp(struct token_list* tk) {
    struct expression* e;

    e = ker_malloc(sizeof(struct expression));
    e->type = OP_TERMINAL;
    e->tk = tk;
//    printf("alloc_term_exp e: %x\n", e);
    return e;
}

struct expression* alloc_nested_exp(struct expression* exp) {
    struct expression* ret_e;
    ret_e = ker_malloc(sizeof(struct expression));
    ret_e->type = OP_COMPOUND;
    ret_e->operand1 = exp;
//    printf("alloc_term_exp ret_e: %x\n", ret_e);
    return ret_e;
}

struct expression* alloc_2op_exp (enum OP_TYPE ot, struct expression* op1, struct expression* op2) {
    struct expression* ret_e;
    ret_e = ker_malloc(sizeof(struct expression));
    ret_e->type = ot;
    ret_e->operand1 = op1;
    ret_e->operand2 = op2;
//    printf("alloc_2op_exp ret_e: %x, op1: %x, op2: %x\n", ret_e, op1, op2);
    return ret_e;
}

void print_exp(struct expression* exp) {
    printf("print_exp...\n");
}

