
#ifndef __function_h__
#define __function_h__

#include "parser.h"
#include "statement.h"

struct function {
    struct declaration*         ret_type;
    struct declaration*         name;
    struct statement*           body;
};

struct function* alloc_function(struct declaration* decl_spec,
            struct declaration* func_name, struct statement* func_body);

void dump_function(struct function* fc);

#endif /*__function_h__*/

