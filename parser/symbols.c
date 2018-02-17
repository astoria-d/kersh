
#include <stdio.h>
#include "uthash.h"

struct symbol {
    const char *name;
    int id;
    UT_hash_handle hh;
};

static unsigned int sym_cnt;
static struct symbol * symbols;



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

