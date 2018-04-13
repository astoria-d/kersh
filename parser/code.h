
#ifndef __code_h__
#define __code_h__

#include "declaration.h"
#include "symbol.h"

struct declaration* set_root_decl_node(struct declaration* decl);

void dump_ir(void);

void add_symbol(struct declaration* decl);
struct symbol* lookup_symbol(const char* sym_name);

void enter_block(struct block_item* blk);
void exit_block(void);

void init_code(void);
void exit_code(void);

#endif /*__code_h__*/

