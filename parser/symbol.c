
#include <stdio.h>
#include <string.h>

#include "symbol.h"
#include "parser.h"
#include "util.h"

/*symbol unique id. (application specific id.)*/
static unsigned int sym_cnt;

static struct symbol *alloc_sym(void);

struct symbol* add_sym_entry(struct symbol **head, int sym_type, const char* sym_name) {
    struct symbol *sym;

    //printf(">>sym add[%s]....\n", sym_name);
    sym = alloc_sym();
    sym->symbol_type = sym_type;
    sym->symbol_name = ker_strdup(sym_name);
    HASH_ADD_STR(*head, symbol_name, sym);
    return sym;
}

static int get_new_sym_id(void) {
    return sym_cnt++;
}

static struct symbol *alloc_sym(void) {
    struct symbol *ret;

    ret = ker_malloc(sizeof(struct symbol));
    ret->id = get_new_sym_id();
    return ret;
}

static void free_symbol(struct symbol* sym) {
    ker_free(sym->symbol_name);
    ker_free(sym);
}

void free_symtable(struct symbol **head) {
    struct symbol *s1, *s2;

    //printf("head: %08x\n", *head);
    HASH_ITER(hh, *head, s1, s2) {
        HASH_DEL(*head, s1);
        free_symbol(s1);
        //printf("s1: %08x\n", s1);
    }
}

void print_symtable(struct symbol* sym) {
    struct symbol *s1, *tmp;
    const char* p;

    HASH_ITER(hh, sym, s1, tmp) {
        printf("[%50s ]: id:%d, ", s1->symbol_name, s1->id);
        switch (s1->symbol_type) {
        case SYM_ENUM        : p = "enum"; break;
        case SYM_TYPEDEF     : p = "typedef"; break;
        case SYM_STRUCT      : p = "struct"; break;
        case SYM_UNION       : p = "union"; break;
        case SYM_FUNC        : p = "func"; break;
        case SYM_INSTANCE    : p = "instance"; break;
          }
        printf("type:%s", p);
        printf("\n");
    }
}

void init_symbols(void) {
    printf("init sym table...\n");
    sym_cnt = 0;
}

