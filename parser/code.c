
#include <stdio.h>

#include "code.h"
#include "utlist.h"
#include "function.h"

static struct declaration* root_decl_node;

struct declaration* set_root_decl_node(struct declaration* decl) {
    root_decl_node = decl;
    return decl;
}

/*IR: intermediate representation is an abstract syntax tree.
 * dump all elements under root_decl_node recursively.
 *  */
void dump_ir(void) {
    printf("dump Intermediate Representation of parsed tree...\n");
    struct declaration* d;
    LL_FOREACH(root_decl_node, d) {
        if (d->is_func) {
            dump_function(d->func);
        }
        else {
            dump_declaration(d, 0, 0);
        }
    }
}

void init_code(void) {
    root_decl_node = NULL;
}
