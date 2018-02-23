

#include "code.h"

static struct code_block* root_code_block;
static struct code_block* cur_code_block;

struct code_block* create_code_block(void) {
    struct code_block* cb = malloc(sizeof (struct code_block));
    memset(cb, 0, sizeof (struct code_block));
}

void free_code_block(struct code_block* cb) {
    struct code_block* next;

    if (cb->sub_block) {
        free_code_block(cb->sub_block);
    }

    next = cb->next;
    while (next) {
        struct code_block* tmp;

        tmp = next->next;
        clear_symtable(next->symbol_table);
        free(next);
        next = tmp;
    }
    clear_symtable(cb->symbol_table);
    free(cb);
}

void init_code_block(void) {
    init_symtable();
    root_code_block = create_code_block();
    cur_code_block = root_code_block;
}

void clear_code_block(void) {
    free_code_block(root_code_block);
}

void cb_add_emu_def(const char* enum_name, int val) {
    struct type_definition* tp = NULL;
    struct symbol* sym;

    sym = add_symbol(&cur_code_block->symbol_table, SYM_ENUM, enum_name);
    sym->type = tp;


}

void add_sub_block(void) {
}

void add_next_block(void) {
}

