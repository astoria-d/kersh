
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
    const char* ts;
    ts = NULL;
    switch (fc->ret_type->type_spec->type) {
    case TS_VOID:
        ts = "void";
        break;
    case TS_CHAR:
        ts = "char";
        break;
    case TS_SHORT:
        ts = "short";
        break;
    case TS_INT:
        ts = "int";
        break;
    case TS_LONG:
        ts = "long";
        break;
    }

    printf("%s %s {\n", ts, fc->name->identifer->strval);
    dump_statement(fc->body);
    printf("}\n");
}
