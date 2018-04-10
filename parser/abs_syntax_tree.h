
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
        struct {
            enum OP_TYPE type;
            union {
                /*terminal node*/
                struct {
                    struct token_list * tk;
                };

                /*non terminal node*/
                struct {
                    struct abs_syntax_tree * operand1;
                    struct abs_syntax_tree * operand2;
                    struct abs_syntax_tree * operand3;
                };
            };
        } exp;

        struct {
            int dummy;
        } sentence;

        struct {
            int dummy;
        } declaration;

        struct {
            int dummy;
        } function;
    };
};

struct abs_syntax_tree* alloc_term_node(struct token_list* tk);
struct abs_syntax_tree* alloc_nested_node(struct abs_syntax_tree* ast);
struct abs_syntax_tree* alloc_2op_node
        (enum OP_TYPE ot, struct abs_syntax_tree* op1, struct abs_syntax_tree* op2);


#endif /*__abs_syntax_tree_h__*/
