
#ifndef __statements_h__
#define __statements_h__

#include "code.h"
#include "expressions.h"

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

struct statement {
    enum ST_TYPE                    type;

    union {
        struct {
            struct token_list*      tk;     /*for simple label statement*/
            struct statement*       exp;    /*for case label statement*/
            struct statement*       stm;
        } lb;

        /*for compound statement*/
        struct {
            struct statement*           sub_stm;
            struct statement*           next;
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
            struct token_list*      tk;     /*goto identifier*/
            struct expression*      exp;
        } jp;
    };
};

struct statement* alloc_exp_statement(struct expression* exp);
struct statement* alloc_cmp_statement(struct statement* stm);
struct statement* append_block_item(struct statement* s1, struct statement* s2);
struct statement* alloc_jmp_statement(enum ST_TYPE tp, struct expression* exp, struct token_list* tk);

#endif /*__statements_h__*/

