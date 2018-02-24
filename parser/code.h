
#ifndef __code_h__
#define __code_h__

#include "types.h"
#include "symbols.h"
#include "instance.h"

struct code_list {
    unsigned char       asm_code;
    struct code_list    *next;
};

struct code_block {
    struct typedef_list*    types;
    struct code_list*       code;
    struct symbol*          symbol_table;
    struct code_block*      sub_block;
    struct code_block*      parent_block;
    struct code_block*      next;

    struct typedef_list* cur_tdl;
};

void init_code_block(void);
void exit_code_block(void);

void cb_add_enum_block(void);
void cb_close_enum_block(void);
void cb_add_enum_elm(const char* elm_name, int val);
void cb_set_enum_name(const char* enum_name);

void cb_add_struct_block(int str_or_uni, const char* struct_name);
void cb_close_struct_block(void);
void cb_add_struct_field(struct typedef_list* field);

#endif /*__code_h__*/

