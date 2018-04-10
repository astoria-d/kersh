
#include <stdio.h>

#include "util.h"
#include "abs_syntax_tree.h"


struct abs_syntax_tree* alloc_term_node(struct token_list* tk) {
    struct abs_syntax_tree* ast;

    ast = ker_malloc(sizeof(struct abs_syntax_tree));
    ast->exp.type = OP_TERMINAL;
    ast->exp.tk = tk;
    return ast;
}

struct abs_syntax_tree* alloc_nested_node(struct abs_syntax_tree* ast) {
    struct abs_syntax_tree* ret_ast;
    ret_ast = ker_malloc(sizeof(struct abs_syntax_tree));
    ret_ast->exp.type = OP_COMPOUND;
    ret_ast->exp.operand1 = ast;
    return ret_ast;
}

struct abs_syntax_tree* alloc_2op_node
    (enum OP_TYPE ot, struct abs_syntax_tree* op1, struct abs_syntax_tree* op2) {
    struct abs_syntax_tree* ret_ast;
    ret_ast = ker_malloc(sizeof(struct abs_syntax_tree));
    ret_ast->exp.type = ot;
    ret_ast->exp.operand1 = op1;
    ret_ast->exp.operand2 = op2;
    return ret_ast;
}
