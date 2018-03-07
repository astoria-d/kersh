
#ifndef __symbols_h__
#define __symbols_h__

#include "uthash.h"
#include "types.h"


enum SYM_TYPE {
    SYM_ENUM        ,
    SYM_TYPEDEF     ,
    SYM_STRUCT      ,
    SYM_UNION       ,
    SYM_FUNC        ,
    SYM_INSTANCE    ,
};

struct symbol {
    enum SYM_TYPE           id;
    unsigned char           symbol_type;
    char *                  symbol_name;
    struct type_definition* type;

    /*hash table handle.*/
    UT_hash_handle  hh;
};

void init_symbols(void);

/*
void sym_add_struct_def(const char* struct_name);
void sym_add_enum(const char* enum_name, int val);
void update_enum_val(struct symbol *sym, int val);
*/
struct symbol* add_symbol(struct symbol **head, int sym_type, const char* sym_name);
void free_symtable(struct symbol **head);

#endif /*__symbols_h__*/

