
#include <stdio.h>

#include "util.h"
#include "function.h"
#include "statement.h"
#include "utlist.h"

struct function* alloc_function(struct declaration* decl_spec,
            struct declaration* func_name, struct statement* func_body) {
    struct function* fnc;
    fnc = ker_malloc(sizeof(struct function));
    fnc->ret_type = decl_spec;
    fnc->name = func_name;
    fnc->body = func_body;
    return fnc;
}

void dump_function(struct function* fc) {
    struct declaration* pm;
    int i;

    dump_typespec(fc->ret_type->type_spec, 0);
    printf(" %s ", fc->name->identifer->strval);
    printf("( ");
    i = 0;
    LL_FOREACH(fc->name->param, pm) {
        if (i++ > 0) printf(", ");
        dump_typespec(pm->type_spec, 0);
        if (pm->identifer) {
            printf(" %s ", pm->identifer->strval);
        }
    }
    printf(") ");
    dump_statement(fc->body, 0);
}

void function_definition_0(struct function* fnc) {
    if (!fnc->name->is_func) {
        semantic_err("invalid function definition.\n");
    }
}
