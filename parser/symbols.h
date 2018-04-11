
#ifndef __symbols_h__
#define __symbols_h__

#include "uthash.h"


enum SYM_TYPE {
    SYM_ENUM        ,
    SYM_TYPEDEF     ,
    SYM_STRUCT      ,
    SYM_UNION       ,
    SYM_FUNC        ,
    SYM_INSTANCE    ,
};

struct symbol {
    int                     id;
    enum SYM_TYPE           symbol_type;
    char *                  symbol_name;

    /*hash table handle.*/
    UT_hash_handle  hh;
};

void init_symbols(void);

void print_symtable(struct symbol* sym);

struct symbol* add_symbol(struct symbol **head, int sym_type, const char* sym_name);
void free_symtable(struct symbol **head);

#endif /*__symbols_h__*/

