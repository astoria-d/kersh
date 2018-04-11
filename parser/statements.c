
#include <stdio.h>

#include "util.h"
#include "statements.h"
#include "utlist.h"


struct statement* alloc_exp_statement(struct expression* exp) {
    struct statement* stm;
    stm = ker_malloc(sizeof(struct statement));
    stm->type = ST_EXPRESSION;
    stm->exp = exp;
//    printf("alloc_exp_statement st: %x, exp: %x\n", stm, exp);
    return stm;
}

struct statement* alloc_jmp_statement(enum ST_TYPE tp, struct expression* exp, struct token_list* tk) {
    struct statement* stm;
    stm = ker_malloc(sizeof(struct statement));
    stm->type = tp;
    stm->jp.tk = tk;
    stm->jp.exp = exp;
//    printf("alloc_jmp_statement st: %x, exp: %x\n", stm, exp);
    return stm;
}

struct block_item* alloc_decl_block(struct declaration* decl) {
    struct block_item* blk;
    blk = ker_malloc(sizeof(struct block_item));
    blk->type = BI_DECLARATION;
    blk->decl = decl;
}

struct block_item* alloc_stm_block(struct statement* stm) {
    struct block_item* blk;
    blk = ker_malloc(sizeof(struct block_item));
    blk->type = BI_STATEMENT;
    blk->stm = stm;
}

struct block_item* append_block_item(struct block_item* bl1, struct block_item* bl2) {
    bl1->next = bl2;
//    printf("append_block_item s1: %x, s2: %x\n", bl1, bl2);
    return bl1;
}

struct statement* alloc_cmp_statement(struct block_item* blk) {
    struct statement* stm;
    stm = ker_malloc(sizeof(struct statement));
    stm->type = ST_COMPOUND;
    stm->blk = blk;
//    printf("alloc_cmp_statement stm: %x, blk: %x\n", stm, blk);
    return stm;
}

void dump_statement(struct statement* stm) {
    printf("dump_statement\n");
}
