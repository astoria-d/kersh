
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
    struct code_block *next, *tmp;

    /*free child blocks first.*/
    if (cb->sub_block) {
        free_code_block(cb->sub_block);
    }

    /*free siblings next.*/
    printf("\ntypedef clean up...\n");
    LL_FOREACH_SAFE(cb, next, tmp) {
        print_typedef(&next->types, 0);
        free_typedef(&next->types);
        free_symtable(&next->symbol_table);
        free(next);
    }
}

struct type_definition* cb_add_enum_block(struct type_definition** head) {
    struct type_definition* td;

    td = alloc_typedef();
    td->type_id = TP_ENUM;
    LL_APPEND(*head, td);
    return td;
}

void cb_add_enum_elm(struct type_definition** head, const char* elm_name, int val) {
    struct type_definition* td;

    td = alloc_typedef();
    td->type_id = TP_ENUM;
    td->name = strdup(elm_name);
    td->size = sizeof(int);
    td->value = val;

    LL_APPEND(*head, td);

}

void cb_close_enum_block(struct code_block* cb, struct type_definition* enum_td) {
    struct type_definition* enum_ent;
    struct symbol* sym;

    /*insert all enum members into symbol table.*/
    LL_FOREACH(enum_td->members, enum_ent) {
        if (!enum_ent->name) {
            continue;
        }
        sym = add_symbol(&cb->symbol_table, SYM_ENUM, enum_ent->name);
        sym->type = enum_ent;
    }
}

struct type_definition* cb_add_struct_block(struct type_definition** head, int str_or_uni, const char* struct_name) {
    struct type_definition* td;
    printf("add struct %s\n", struct_name);

    td = alloc_typedef();
    td->type_id = str_or_uni == STRUCT ? TP_STRUCT : TP_UNION;
    LL_APPEND(*head, td);

    if (struct_name) {
        struct symbol* sym;
        td->type_name = strdup(struct_name);
//        sym = add_symbol(&cb->symbol_table, str_or_uni, struct_name);
//        sym->type = &td;
    }
    return td;
}

struct type_definition* cb_add_sub_struct_block(struct type_definition* parent, int str_or_uni, const char* struct_name) {
    struct type_definition* sub_type;

    /*add sub type to the parent.*/
    sub_type = alloc_typedef();
    sub_type->type_id = str_or_uni == STRUCT ? TP_STRUCT : TP_UNION;
    if (struct_name) sub_type->type_name = strdup(struct_name);
    LL_APPEND(parent->members, sub_type);

    return sub_type;
}

void cb_close_struct_block(struct code_block* cb, struct type_definition* str_td) {
    struct symbol* sym;

    if (!str_td->name) return ;
    sym = add_symbol(&cb->symbol_table, SYM_ENUM, str_td->name);
    sym->type = str_td;
}

void cb_add_struct_field(struct type_definition* parent, struct type_definition* field) {
    //if ((parent->type_id == TP_STRUCT || parent->type_id == TP_UNION) && !parent->members) {
    if (!field->name) {
        printf("add struct definition & field\n");
        if (field->name) parent->name = strdup(field->name);
        return;
    }
    printf("add field %s\n", field->name);
    LL_APPEND(parent->members, field);
}

void cb_exit_cb(void) {
    /*do nothing.*/
}

void add_sub_block(struct code_block* cb) {
}

