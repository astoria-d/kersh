

#include "kersh.tab.h"
#include "code.h"

static struct code_block* root_code_block;
static struct code_block* cur_code_block;

static struct code_block* create_code_block(void) {
    struct code_block* cb = malloc(sizeof (struct code_block));
    memset(cb, 0, sizeof (struct code_block));
}

static void free_code_block(struct code_block* cb) {
    struct code_block* next;

    if (cb->sub_block) {
        free_code_block(cb->sub_block);
    }

    next = cb->next;
    while (next) {
        struct code_block* tmp;

        tmp = next->next;
        free_symtable(&next->symbol_table);
        free(next);
        next = tmp;
    }
    free_symtable(&cb->symbol_table);
    free(cb);
}

void init_code_block(void) {
    init_symbols();
    root_code_block = create_code_block();
    cur_code_block = root_code_block;
}

void exit_code_block(void) {
    free_code_block(root_code_block);
}

void cb_add_enum_block(void) {
}

void cb_add_enum_elm(const char* elm_name, int val) {
    struct type_definition* tp = NULL;
    struct symbol* sym;

    sym = add_symbol(&cur_code_block->symbol_table, SYM_ENUM, elm_name);
    sym->type = tp;
}

void cb_close_enum_block(const char* enum_name) {
}

void cb_discard_enum_block(void) {
}

void cb_add_struct_def(int str_or_uni, const char* struct_name) {
    struct type_definition* tp = NULL;

    if(cur_code_block == root_code_block) {
        struct symbol* sym;
        sym = add_symbol(&cur_code_block->symbol_table, 
            str_or_uni == STRUCT ? SYM_STRUCT : SYM_UNION, struct_name);
        sym->type = tp;
    }

//    add_sub_block(cb);
//    cur_code_block = cb;
}

void cb_exit_cb(void) {
    cur_code_block = cur_code_block->parent_block;
}

void add_sub_block(struct code_block* cb) {
}

