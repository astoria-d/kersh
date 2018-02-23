
#ifndef __symbols_h__
#define __symbols_h__

#include "uthash.h"
#include "types.h"
#include "instance.h"


#define     SYM_ENUM        0
#define     SYM_TYPEDEF     1
#define     SYM_STRUCT      2
#define     SYM_UNION       3
#define     SYM_INSTANCE    4
#define     SYM_FUNC        5

struct symbol {
    int                     id;
    unsigned char           symbol_type;
    char *                  symbol_name;
    union {
        struct type_definition* type;
        struct instance*        instance;
    };

    /*hash table handle.*/
    UT_hash_handle  hh;
};

void init_symtable(void);
void clear_symtable(struct symbol *sym);
/*
void sym_add_struct_def(const char* struct_name);
void sym_add_enum(const char* enum_name, int val);
void update_enum_val(struct symbol *sym, int val);
*/
void set_sym_table(struct symbol *sym);
struct symbol* add_symbol(struct symbol **head, int sym_type, const char* sym_name);
struct symbol *alloc_sym(void);

#endif /*__symbols_h__*/

