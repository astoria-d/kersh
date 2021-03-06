
#include <stdio.h>

#include "util.h"
#include "statement.h"
#include "utlist.h"
#include "symbol.h"
#include "code.h"

struct statement* alloc_exp_statement(struct expression* exp) {
    struct statement* stm;
    stm = ker_malloc(sizeof(struct statement));
    stm->type = ST_EXPRESSION;
    stm->exp = exp;
//    printf("alloc_exp_statement st: %x, exp: %x\n", stm, exp);
    return stm;
}

struct statement* alloc_jmp_statement(enum ST_TYPE tp, struct expression* exp, struct ctoken* tk) {
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
    return blk;
}

struct block_item* alloc_stm_block(struct statement* stm) {
    struct block_item* blk;
    blk = ker_malloc(sizeof(struct block_item));
    blk->type = BI_STATEMENT;
    blk->stm = stm;
    return blk;
}

struct block_item* append_block_item(struct block_item* bl1, struct block_item* bl2) {
    LL_APPEND(bl1, bl2);
//    printf("append_block_item s1: %x, s2: %x\n", bl1, bl2);
    return bl1;
}

struct statement* alloc_cmp_statement(struct block_item* blk) {
    struct statement* stm;
    stm = ker_malloc(sizeof(struct statement));
    stm->type = ST_COMPOUND;
    stm->cp.blk = blk;
//    printf("alloc_cmp_statement stm: %x, blk: %x\n", stm, blk);
    return stm;
}

void dump_statement(struct statement* stm, int indent) {
    if(stm->type == ST_COMPOUND) {
        struct block_item *b;
        print_indent(indent);
        printf("{\n");
        LL_FOREACH(stm->cp.blk, b) {
            if (b->type == BI_DECLARATION) {
                dump_declaration(b->decl, indent + 1, 1);
            }
            else {
                dump_statement(b->stm, indent + 1);
            }
        }
        print_indent(indent);
        printf("}\n");
    }
    else {
        const char* p;

#define CASE_BREAK(type)\
    case type:                      p = #type; break;

        print_indent(indent);

        p = NULL;
        switch (stm->type) {
        CASE_BREAK(ST_LB_SIMPLE)
        CASE_BREAK(ST_LB_CASE)
        CASE_BREAK(ST_LB_DEFAULT)
        case ST_EXPRESSION:
            dump_expression(stm->exp, 0);
            printf(" ;\n");
            break;

        CASE_BREAK(ST_SL_IF)
        CASE_BREAK(ST_SL_IFELSE)
        CASE_BREAK(ST_SL_SWITCH)
        CASE_BREAK(ST_IT_WHILE)
        CASE_BREAK(ST_IT_DOWHILE)
        CASE_BREAK(ST_IT_FOR)
        CASE_BREAK(ST_JP_GOTO)
        CASE_BREAK(ST_JP_CONTINUE)
        CASE_BREAK(ST_JP_BREAK)
        case ST_JP_RETURN:
            if (stm->jp.exp) {
                printf("return ");
                dump_expression(stm->jp.exp, 1);
                printf(" ;\n");
            }
            else {
                printf("return ;\n");
            }
        }
        if (p) {
            printf("%s ;\n", p);
        }
    }
}


void block_item_list_0(struct block_item* blk) {
    struct declaration *dc;

    enter_block(blk);
    if (blk->type == BI_DECLARATION) {
        LL_FOREACH(blk->decl, dc) {
            add_symbol(dc);
        }
    }
}

void block_item_list_1(struct block_item* blk) {
    struct block_item *b, *last;

    /*get the last block item*/
    LL_FOREACH(blk, b) {
        last = b;
    }
    if (last->type == BI_DECLARATION) {
        add_symbol(last->decl);
    }
}

void compound_statement_1(struct statement* c_stm) {
    exit_block();
}

