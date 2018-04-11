
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "declaration.h"
#include "utlist.h"


struct declaration* alloc_declarator(struct token_list* tk) {
    struct declaration* dcr;
    dcr = ker_malloc(sizeof(struct declaration));
    dcr->identifer = tk;
//    printf("alloc_declarator st: %x, exp: %x\n", dcr, tk);
    return dcr;
}

struct declaration* append_declarator(struct declaration* d1, struct declaration* d2) {
    LL_APPEND(d1, d2);
    return d1;
}

void dump_declaration(struct declaration* decl) {
    struct declaration* d;
    LL_FOREACH(decl, d) {
        printf("declaration %s\n", d->identifer->strval);
    }
}
