
#ifndef __symbols_h__
#define __symbols_h__

#include "uthash.h"


#define     SYM_ENUM        0
#define     SYM_TYPEDEF     1
#define     SYM_STRUCT      2
#define     SYM_UNION       3
#define     SYM_GLOBAL_VAR  4
#define     SYM_FUNC        5

void set_last_symbol(const char* sym_name);

void init_symtable(void);
void clear_symtable(void);
void add_symbol(void);
void add_enum_symbol(const char* enum_name, int val);
void update_enum_val(int val);

struct symbol {
    unsigned char   symbol_type;
    unsigned int    data_size;
    unsigned int    symbol_value;
    int             id;

    /*hash table handle.*/
    UT_hash_handle  hh;

    char *          symbol_name;
};


#endif /*__symbols_h__*/

