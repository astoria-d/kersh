
#ifndef __statement_h__
#define __statement_h__

#include "expression.h"
#include "declaration.h"
#include "symbol.h"

enum ST_TYPE {
    ST_INVALID = 0  , /*invalid type...*/

    /*label statement*/
    ST_LB_SIMPLE,
    ST_LB_CASE,
    ST_LB_DEFAULT,

    /*compound statement*/
    ST_COMPOUND,

    /*expression statement*/
    ST_EXPRESSION,

    /*select statement*/
    ST_SL_IF,
    ST_SL_IFELSE,
    ST_SL_SWITCH,

    /*iteration statement*/
    ST_IT_WHILE,
    ST_IT_DOWHILE,
    ST_IT_FOR,

    /*jump statement*/
    ST_JP_GOTO,
    ST_JP_CONTINUE,
    ST_JP_BREAK,
    ST_JP_RETURN,
};

enum BI_TYPE {
    BI_DECLARATION,
    BI_STATEMENT,
};

struct block_item {
    enum BI_TYPE                type;
    union {
        struct statement*       stm;
        struct declaration*     decl;
    };
    struct block_item*          next;
};

struct statement {
    enum ST_TYPE                    type;

    union {
        struct {
            struct ctoken*          tk;     /*for simple label statement*/
            struct statement*       exp;    /*for case label statement*/
            struct statement*       stm;
        } lb;

        /*for compound statement*/
        struct {
            struct block_item*          blk;
            struct symbol*              sym;
        } cp;

        /*for expression statement*/
        struct expression*          exp;

        struct {
            struct expression*      exp;
            struct statement *      if_stm;
            struct statement *      if_else;
        } sl;

        struct {
            struct expression*      exp1;
            struct expression*      exp2;
            struct statement *      stm;
        } it;

        struct {
            struct ctoken*          tk;     /*goto identifier*/
            struct expression*      exp;
        } jp;
    };
};

struct statement* alloc_exp_statement(struct expression* exp);
struct statement* alloc_jmp_statement(enum ST_TYPE tp, struct expression* exp, struct ctoken* tk);

struct block_item* alloc_decl_block(struct declaration* decl);
struct block_item* alloc_stm_block(struct statement* stm);
struct block_item* append_block_item(struct block_item* bl1, struct block_item* bl2);
struct statement* alloc_cmp_statement(struct block_item* blk);

void dump_statement(struct statement* stm, int indent);

void compound_statement_1(struct statement* c_stm);

#endif /*__statement_h__*/

