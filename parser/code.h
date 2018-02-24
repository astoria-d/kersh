
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
    struct type_def_list*   types;
    struct code_list*       code;
    struct symbol*          symbol_table;
    struct code_block*      sub_block;
    struct code_block*      parent_block;
    struct code_block*      next;
};

void init_code_block(void);
void exit_code_block(void);
void cb_add_emu_def(const char* enum_name, int val);
void cb_add_struct_def(int str_or_uni, const char* struct_name);

#endif /*__code_h__*/

