
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "expression.h"
#include "declaration.h"
#include "utlist.h"


struct expression* alloc_term_exp(struct ctoken* tk) {
    struct expression* e;

    e = ker_malloc(sizeof(struct expression));
    e->type = OP_TERMINAL;
    e->tk = tk;
    remove_token(tk);
//    printf("alloc_term_exp e: %x\n", e);
    return e;
}

struct expression* alloc_nested_exp(struct expression* exp) {
    struct expression* ret_e;
    ret_e = ker_malloc(sizeof(struct expression));
    ret_e->type = OP_COMPOUND;
    ret_e->ope1 = exp;
//    printf("alloc_term_exp ret_e: %x\n", ret_e);
    return ret_e;
}

struct expression* alloc_2op_exp (enum OP_TYPE ot, struct expression* op1, struct expression* op2) {
    struct expression* ret_e;
    ret_e = ker_malloc(sizeof(struct expression));
    ret_e->type = ot;
    ret_e->ope1 = op1;
    ret_e->ope2 = op2;
//    printf("alloc_2op_exp ret_e: %x, op1: %x, op2: %x\n", ret_e, op1, op2);
    return ret_e;
}

struct expression* alloc_cast_exp(struct type_specifier* cast, struct expression* exp) {
    struct expression* ret_e;
    ret_e = ker_malloc(sizeof(struct expression));
    ret_e->type = OP_CAST;
    ret_e->ope1 = exp;
    ret_e->cast = cast;
    //printf("alloc_cast_exp: cast:%x\n", cast);
    return ret_e;
}

static char * two_op[] = {
        "*",
        "/",
        "%",
        "+",
        "-",
        "<<",
        ">>",
        "<",
        ">",
        "<=",
        ">=",
        "==",
        "!=",
        "&",
        "^",
        "|",
        "&&",
        "||",
};

static char * asign_op[] = {
        "=",
        "*=",
        "/=",
        "%=",
        "+=",
        "-=",
        "<<=",
        ">>=",
        "&=",
        "^=",
        "|="
};

static void dump_tk(struct ctoken* tk) {
    if (tk->token == IDEN) {
        printf("%s", tk->strval);
    }
    else {
        printf("%d", tk->lval);
    }
}

void dump_expression(struct expression* exp, int indent) {

    if (indent > 0) printf("( ");

    switch (exp->type) {
    case OP_TERMINAL:
        dump_tk(exp->tk);
        break;

    case OP_COMPOUND:
        dump_expression(exp->ope1, indent + 1);
        break;

    case OP_CAST:
        //printf("cast:%x\n", exp->cast);
        printf("( ");
        dump_typespec(exp->cast);
        printf(" ) ");
        dump_expression(exp->ope1, indent + 1);
        break;

    case OP_MUL:
    case OP_DIV:
    case OP_MOD:
    case OP_PLUS:
    case OP_MINUS:
    case OP_LSHIFT:
    case OP_RSHIFT:
    case OP_LT:
    case OP_GT:
    case OP_LE:
    case OP_GE:
    case OP_EQEQ:
    case OP_NE:
    case OP_AND:
    case OP_XOR:
    case OP_OR:
    case OP_LAND:
    case OP_LOR:
        if (exp->ope1->type == OP_TERMINAL) {
            dump_tk(exp->ope1->tk);
        }
        else {
            dump_expression(exp->ope1, indent + 1);
        }

        printf(" %s ", two_op[exp->type - OP_MUL]);

        if (exp->ope2->type == OP_TERMINAL) {
            dump_tk(exp->ope2->tk);
        }
        else {
            dump_expression(exp->ope2, indent + 1);
        }

        break;

    case OP_EQ:
    case OP_ASTR_EQ:
    case OP_DASH_EQ:
    case OP_PERC_EQ:
    case OP_PLUS_EQ:
    case OP_MINUS_EQ:
    case OP_LSHIFT_EQ:
    case OP_RSHIFT_EQ:
    case OP_AMP_EQ:
    case OP_HAT_EQ:
    case OP_OR_EQ:
        dump_tk(exp->ope1->tk);
        printf(" %s ", asign_op[exp->type - OP_EQ]);

        if (exp->ope2->type == OP_TERMINAL) {
            dump_tk(exp->ope2->tk);
        }
        else {
            dump_expression(exp->ope2, indent + 1);
        }
        break;

    default:
        printf("!!!");
    }
    if (indent > 0) printf(" )");
}

