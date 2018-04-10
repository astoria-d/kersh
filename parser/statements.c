
#include <stdio.h>

#include "util.h"
#include "statements.h"
#include "utlist.h"


struct statement* alloc_exp_statement(struct expression* exp) {
    struct statement* stm;
    stm = ker_malloc(sizeof(struct statement));
    stm->type = ST_EXPRESSION;
    stm->exp = exp;
    printf("alloc_exp_statement st: %x, exp: %x\n", stm, exp);
    return stm;
}

struct statement* alloc_cmp_statement(struct statement* stm) {
    struct statement* ret_st;
    ret_st = ker_malloc(sizeof(struct statement));
    ret_st->type = ST_COMPOUND;
    ret_st->cp.sub_stm = stm;
    printf("alloc_exp_statement ret_st: %x, stm: %x\n", ret_st, stm);
    return ret_st;
}

struct statement* append_block_item(struct statement* s1, struct statement* s2) {
    s1->cp.next = s2;
    printf("append_block_item s1: %x, s2: %x\n", s1, s2);
    return s1;
}

struct statement* alloc_jmp_statement(enum ST_TYPE tp, struct expression* exp, struct token_list* tk) {
    struct statement* stm;
    stm = ker_malloc(sizeof(struct statement));
    stm->type = tp;
    stm->jp.tk = tk;
    stm->jp.exp = exp;
    printf("alloc_jmp_statement st: %x, exp: %x\n", stm, exp);
    return stm;
}
