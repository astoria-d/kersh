
#ifndef __code_h__
#define __code_h__

#include "declaration.h"

struct declaration* set_root_decl_node(struct declaration* decl);

void dump_ir(void);

void add_sym_root(struct declaration* decl);

void init_code(void);
void exit_code(void);

#endif /*__code_h__*/

