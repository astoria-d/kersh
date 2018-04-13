
#include <stdio.h>

#include "util.h"
#include "code.h"
#include "utlist.h"
#include "function.h"

static struct declaration*  root_decl_node;
static struct symbol*       root_sym_table;

struct block_walk {
    struct block_item*          blk;
    struct block_walk*          next;
    struct block_walk*          prev;
};

static struct block_walk*       block_head;
static struct block_walk*       cur_block;

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

/*add_symbol adds the symbol to current working block.*/
void add_symbol(struct declaration* decl) {
    struct symbol** sym_tbl;

    if (cur_block == NULL) {
        sym_tbl = &root_sym_table;
    }
    else {
        sym_tbl = &root_sym_table;
    }

    if (decl->is_func) {
        add_sym_entry(sym_tbl, SYM_FUNC, decl->func->name->identifer->strval);
    }
    else if (decl->dc.is_typedef) {
        add_sym_entry(sym_tbl, SYM_TYPEDEF, decl->identifer->strval);
    }
    else {
        add_sym_entry(sym_tbl, SYM_INSTANCE, decl->identifer->strval);
    }
}

struct symbol* lookup_symbol(const char* sym_name) {
    struct symbol* sym_tbl;
    struct symbol* ret;

    if (cur_block == NULL) {
        sym_tbl = root_sym_table;
    }
    else {
        sym_tbl = root_sym_table;
    }

    HASH_FIND_STR(sym_tbl, sym_name, ret);
    return ret;

}

void enter_block(struct block_item* blk) {
    struct block_walk* bw;
    bw = ker_malloc(sizeof(struct block_walk));
    bw->blk = blk;
    DL_APPEND(block_head, bw);
    cur_block = bw;
}

void exit_block(void) {
    struct block_walk* bw;
    bw = cur_block;
    cur_block = cur_block->prev;
    DL_DELETE(block_head, bw);
}


void init_code(void) {
    printf("init code...\n");
    root_decl_node = NULL;
    root_sym_table = NULL;
    cur_block = NULL;
    block_head = NULL;
}

void exit_code(void) {
    printf("exit code...\n");
    free_symtable(&root_sym_table);
}
