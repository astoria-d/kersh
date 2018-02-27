
#include <stdio.h>

#include "kersh.tab.h"
#include "code.h"
#include "utlist.h"

struct code_block* create_code_block(void) {
    struct code_block* cb = malloc(sizeof (struct code_block));
    memset(cb, 0, sizeof (struct code_block));
    return cb;
}

void free_code_block(struct code_block* cb) {
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

struct typedef_list* cb_add_enum_block(struct code_block* cb) {
    struct typedef_list* tdl = NULL;

    tdl = alloc_typedef_list();
    tdl->type.type_id = TP_ENUM;
    LL_APPEND(cb->types, tdl);
    return tdl;
}

void cb_add_enum_elm(struct typedef_list* tdl, const char* elm_name, int val) {
    struct type_definition* head;
    struct type_definition* td;

    td =alloc_typedef();
    td->type_id = TP_ENUM;
    td->name = strdup(elm_name);
    td->size = sizeof(int);
    td->value = val;

    head = &tdl->type;
    LL_APPEND(head, td);

}

void cb_close_enum_block(struct code_block* cb) {
    struct type_definition* head;
    struct type_definition* tp = NULL;
    struct symbol* sym;

    /*insert all enum members into symbol table.*/
    head = &cb->types->type;
    LL_FOREACH(head, tp) {
        if (tp == head && !tp->name) {
            continue;
        }
        sym = add_symbol(&cb->symbol_table, SYM_ENUM, tp->name);
        sym->type = tp;
    }
}

struct typedef_list* cb_add_struct_block(struct code_block* cb, int str_or_uni, const char* struct_name) {
    struct typedef_list* tdl = NULL;
    //printf("add struct %s\n", struct_name);

    tdl = alloc_typedef_list();
    tdl->type.type_id = str_or_uni == STRUCT ? TP_STRUCT : TP_UNION;
    LL_APPEND(cb->types, tdl);

    if (struct_name) {
        struct symbol* sym;
        tdl->type.name = strdup(struct_name);
        sym = add_symbol(&cb->symbol_table, str_or_uni, struct_name);
        sym->type = &tdl->type;
    }
    return tdl;
}

struct typedef_list* cb_add_sub_struct_block(struct typedef_list* parent, int str_or_uni, const char* struct_name) {
    struct type_definition* head;
    struct type_definition* sub_type;

    /*add sub type to the parent.*/
    sub_type = alloc_typedef();
    sub_type->type_id = str_or_uni == STRUCT ? TP_STRUCT : TP_UNION;
    if (struct_name) sub_type->name = strdup(struct_name);
    head = &parent->type.subtypes->type;
    LL_APPEND(head, sub_type);

    /*also add field to the parent.*/
    head = &parent->type;
    LL_APPEND(head, sub_type);

    return sub_type;
}

void cb_close_struct_block(struct code_block* cb) {
    /*do nothing...*/
}

void cb_add_struct_field(struct typedef_list* tdl, struct type_definition* field) {
    struct type_definition* head;

    if (!field) {
        printf("add anonymous field\n");
        return;
    }
    printf("add field %s\n", field->name);
    head = &tdl->type;
    LL_APPEND(head, field);
}

void cb_exit_cb(void) {
    /*do nothing.*/
}

void add_sub_block(struct code_block* cb) {
}

