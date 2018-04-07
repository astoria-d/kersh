
#ifndef __statements_h__
#define __statements_h__

#include "code.h"
#include "expressions.h"

enum ST_TYPE {
    ST_INVALID = 0  , /*invalid type...*/
    ST_LABEL        ,
    ST_COMPOUND     ,
    ST_EXPRESSION   ,
    ST_SELECT       ,
    ST_ITERATION    ,
    ST_JUMP         ,
};

enum LB_TYPE {
    LB_SIMPLE,
    LB_CASE,
    LB_DEFAULT,
};

enum SL_TYPE {
    LB_IF,
    LB_IFELSE,
    LB_SWITCH,
};

enum IL_TYPE {
    IL_WHILE,
    IL_DOWHILE,
    IL_FOR,
};

enum JP_TYPE {
    JP_GOTO,
    JP_CONTINUE,
    JP_BREAK,
    JP_RETURN,
};

struct statement {
    enum ST_TYPE            statement_type;

    union {
        struct {
            enum LB_TYPE            label_type;
            union {
                const char*         label_name;     /*for simple label statement*/
                long                value;          /*for case label statement*/
            };
        } label ;

        struct {
            struct code_block*      code;
        } compound ;

        struct {
            struct expression*      exp;
        } expression ;

        struct {
            enum SL_TYPE            select_type;
            struct expression*      exp;
        } select ;

        struct {
            enum IL_TYPE            iteration_type;
            struct expression*      exp;
        } iteration ;

        struct {
            enum JP_TYPE            jump_type;
            struct expression*      exp;
        } jump ;
    };

    struct statement*       inner_statement;
    struct statement*       next;
};

#endif /*__statements_h__*/

