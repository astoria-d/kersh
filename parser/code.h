
#ifndef __code_h__
#define __code_h__

#include "types.h"
#include "symbols.h"

struct code_block {
    struct type_definition*     types;
    struct statement*           statements;
    struct symbol*              symbol_table;
    struct code_block*          parent;
    struct code_block*          sub_block;
    struct code_block*          next;

    /*block locator*/
    char*                       func_name;
    unsigned int                line;
    unsigned int                level;
};

struct symbol* lookup_symbol(struct code_block* cb, const char* sym_name);

struct code_block* cb_add_compound_block
                            (struct code_block* parent, unsigned int line, unsigned int level);

struct type_definition* cb_add_enum_block (struct type_definition** head);
void cb_add_enum_elm        (struct type_definition** head, const char* elm_name, int val);
void cb_close_enum_block    (struct code_block* cb, struct type_definition* enum_tdl);

struct type_definition* cb_add_struct_block
                            (struct type_definition** head, int str_or_uni, const char* struct_name);
struct type_definition* cb_add_sub_struct_block
                            (struct type_definition* parent, int str_or_uni, const char* struct_name);
void cb_add_struct_field    (struct type_definition* parent, struct type_definition* field);
void cb_close_struct_block  (struct code_block* cb, struct type_definition* str_td);

void cb_add_declaration(struct code_block* cb, struct type_definition* decl);

struct code_block* create_code_block (void);
void free_code_block        (struct code_block* cb);

#endif /*__code_h__*/

