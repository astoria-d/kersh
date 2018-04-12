
#include <stdio.h>

#include "util.h"
#include "function.h"
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
