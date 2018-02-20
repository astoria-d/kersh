
#include <stdio.h>
#include <string.h>
#include "uthash.h"

struct symbol {
    const char *name;
    int id;
    UT_hash_handle hh;
};

static unsigned int sym_cnt;
static struct symbol * symbols;

static const char* last_symbol;

void set_last_symbol(const char* sym_name) {
    /*TODO must deallocate it!!*/
    last_symbol = strdup(sym_name);
}

void add_symbol(void) {
    printf(">>add sym [%s]", last_symbol);
}

void add_enum_symbol(const char* enum_name, int val) {
    printf(">>add sym [%s:%d]", enum_name, val);
}

void init_symtable(void) {
    sym_cnt = 0;
    symbols = NULL;
}

void clear_symtable(void) {
    struct symbol *current_sym, *tmp;
    HASH_ITER(hh, symbols, current_sym, tmp) {
        HASH_DEL(symbols, current_sym);
        free(current_sym);
    }
    printf("\ndone.\n");
}

