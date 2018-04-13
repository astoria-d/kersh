
#include <stdio.h>

#include "code.h"
#include "utlist.h"
#include "function.h"
#include "symbol.h"

static struct declaration*  root_decl_node;
static struct symbol*       root_sym_table;

struct declaration* set_root_decl_node(struct declaration* decl) {
    root_decl_node = decl;
    return decl;
}

/*IR: intermediate representation is an abstract syntax tree.
 * dump all elements under root_decl_node recursively.
 *  */
void dump_ir(void) {
    printf("=======================================\n");
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
    printf("=======================================\n");
    printf("dump symbol table...\n");
    print_symtable(root_sym_table);
}

void add_sym_root(struct declaration* decl) {
    if (decl->is_func) {
        add_symbol(&root_sym_table, SYM_FUNC, decl->func->name->identifer->strval);
    }
    else if (decl->dc.is_typedef) {
        add_symbol(&root_sym_table, SYM_TYPEDEF, decl->identifer->strval);
    }
    else {
        add_symbol(&root_sym_table, SYM_INSTANCE, decl->identifer->strval);
    }
}


void init_code(void) {
    printf("init code...\n");
    root_decl_node = NULL;
    root_sym_table = NULL;
}

void exit_code(void) {
    printf("exit code...\n");
    free_symtable(&root_sym_table);
}
