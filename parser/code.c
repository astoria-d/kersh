
#include <stdio.h>

#include "kersh.tab.h"
#include "code.h"
#include "utlist.h"
#include "util.h"

struct type_definition* cb_add_enum_block(struct type_definition** head) {
    struct type_definition* td;

    td = alloc_typedef();
    td->type_id = TP_ENUM_DEF;
    LL_APPEND(*head, td);
    return td;
}

void cb_add_enum_elm(struct type_definition** head, const char* elm_name, int val) {
    struct type_definition* td;

    td = alloc_typedef();
    td->type_id = TP_ENUM;
    td->name = ker_strdup(elm_name);
    td->size = sizeof(int);
    td->value = val;

    LL_APPEND(*head, td);

}

void cb_close_enum_block(struct code_block* cb, struct type_definition* enum_td) {
    struct type_definition* enum_ent;
    struct symbol* sym;

    if (enum_td->name) {
        sym = add_symbol(&cb->symbol_table, SYM_ENUM, enum_td->name);
        sym->type = enum_td;
    }
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
    //printf("add struct %s\n", struct_name);

    td = alloc_typedef();
    td->type_id = str_or_uni == STRUCT ? TP_STRUCT : TP_UNION;
    LL_APPEND(*head, td);

    if (struct_name) {
        struct symbol* sym;
        td->type_name = ker_strdup(struct_name);
    }
    return td;
}

struct type_definition* cb_add_sub_struct_block(struct type_definition* parent, int str_or_uni, const char* struct_name) {
    struct type_definition* sub_type;

    /*add sub type to the parent.*/
    sub_type = alloc_typedef();
    sub_type->type_id = str_or_uni == STRUCT ? TP_STRUCT : TP_UNION;
    if (struct_name) sub_type->type_name = ker_strdup(struct_name);
    LL_APPEND(parent->members, sub_type);

    return sub_type;
}

void cb_close_struct_block(struct code_block* cb, struct type_definition* str_td) {
    struct symbol* sym;
    struct type_definition* t;

    /*check if the closing struct is declared under the code block directly.*/
    t = cb->types;
    while (t->next != NULL) {
        t = t->next;
    }

    if (t == str_td && str_td->type_name) {
        sym = add_symbol(&cb->symbol_table, SYM_STRUCT, str_td->type_name);
        sym->type = str_td;
    }
}

void cb_add_struct_field(struct type_definition* parent, struct type_definition* field) {
    int free_fld;
    //printf("add field %s\n", field->name);

    free_fld = 0;
    if (field->type_id == TP_STRUCT || field->type_id == TP_UNION) {
        /*set type definition.*/
        struct type_definition* prev;

        if (field->ql.internal_def) {
            prev = parent->members;
            while (prev) {
                /*get the previous field. check if that is struct definition.*/
                if (prev->next == NULL)
                    break;
                prev = prev->next;
            }
            if (field->name) prev->name = ker_strdup (field->name);
            prev->ql.internal_def = 1;
            free_fld = 1;
        }
        else {
            //TODO! look up sym table.
            LL_APPEND(parent->members, field);
        }
    }
    else {
        LL_APPEND(parent->members, field);
    }
    if (parent->type_id == TP_STRUCT) {
        parent->size += field->size;
    }
    else {
        /*case parent union.*/
        if (parent->size < field->size) {
            parent->size = field->size;
        }
    }
    if (free_fld) free_typedef(&field);
}

struct code_block* create_code_block(void) {
    struct code_block* cb = ker_malloc(sizeof (struct code_block));
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
    printf("typedef clean up...\n");
    LL_FOREACH_SAFE(cb, next, tmp) {
        print_typedef(&next->types, 0);
        free_typedef(&next->types);
        free_symtable(&next->symbol_table);
        ker_free(next);
    }
}

struct type_definition* cb_add_declaration(struct code_block* cb, struct type_definition* decl) {
    return NULL;
}
