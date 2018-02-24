

#include "kersh.tab.h"
#include "code.h"
#include "utlist.h"

static struct code_block* root_code_block;
static struct code_block* cur_code_block;

static struct code_block* create_code_block(void) {
    struct code_block* cb = malloc(sizeof (struct code_block));
    memset(cb, 0, sizeof (struct code_block));
}

static void free_code_block(struct code_block* cb) {
    struct code_block* next;

    /*free child blocks first.*/
    if (cb->sub_block) {
        free_code_block(cb->sub_block);
    }

    /*free siblings next.*/
    next = cb->next;
    while (next) {
        struct code_block* tmp;

        tmp = next->next;
        free_typedef_list(&next->types);
        free_symtable(&next->symbol_table);
        free(next);
        next = tmp;
    }
    free_typedef_list(&cb->types);
    free_symtable(&cb->symbol_table);
    free(cb);
}

void cb_add_enum_block(void) {
    struct typedef_list* tdl = NULL;

    tdl = alloc_typedef_list();
    LL_APPEND(cur_code_block->types, tdl);
    cur_code_block->cur_tdl = tdl;
}

void cb_add_enum_elm(const char* elm_name, int val) {
    struct type_definition* head;
    struct type_definition* td;

    td =alloc_typedef();
    td->type_id = TP_ENUM;
    td->name = strdup(elm_name);
    td->size = sizeof(int);
    td->value = val;

    head = &cur_code_block->cur_tdl->type;
    LL_APPEND(head, td);

}

void cb_set_enum_name(const char* enum_name) {
    struct type_definition* head;
    head = &cur_code_block->cur_tdl->type;
    head->name = strdup(enum_name);
}

void cb_close_enum_block(void) {
    struct type_definition* head;
    struct type_definition* tp = NULL;
    struct symbol* sym;

    /*insert all enum members into symbol table.*/
    head = &cur_code_block->cur_tdl->type;
    LL_FOREACH(head, tp) {
        if (tp == head && !tp->name) {
            continue;
        }
        sym = add_symbol(&cur_code_block->symbol_table, SYM_ENUM, tp->name);
        sym->type = tp;
    }
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

void init_code_block(void) {
    init_symbols();
    root_code_block = create_code_block();
    cur_code_block = root_code_block;
}

void exit_code_block(void) {
    free_code_block(root_code_block);
}

