
#ifndef __abs_syntax_tree_h__
#define __abs_syntax_tree_h__

#include "parser.h"
#include "expressions.h"

enum SYNTAX_NODE_TYPE {
    SNT_EXPRESSION,
    SNT_SENTENCE,
    SNT_DECLARATION,
    SNT_FUNCTION,
};

struct abs_syntax_tree {
    enum SYNTAX_NODE_TYPE node_type;

    union {
        struct expression exp;

        struct sentence{
            int dummy;
        } snt;

        struct declaration {
            int dummy;
        } decl;

        struct function {
            int dummy;
        } fnc;
    };
};



#endif /*__abs_syntax_tree_h__*/
