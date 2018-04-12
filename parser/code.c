
#include <stdio.h>

#include "code.h"

static struct declaration* root_decl_node;

void init_code(void) {
    root_decl_node = NULL;
}

struct declaration* set_root_decl_node(struct declaration* decl) {
    root_decl_node = decl;
    return decl;
}
