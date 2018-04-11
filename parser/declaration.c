
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "declaration.h"
#include "utlist.h"


struct declaration* alloc_declarator(struct token_list* tk) {
    struct declaration* dcr;
    dcr = ker_malloc(sizeof(struct declaration));
    dcr->name = tk;
//    printf("alloc_declarator st: %x, exp: %x\n", dcr, tk);
    return dcr;
}

void dump_declaration(struct declaration* decl) {
    printf("declaration\n");
}
