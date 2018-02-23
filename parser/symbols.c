
#include <stdio.h>
#include <string.h>

#include "symbols.h"
#include "parser.h"

/*symbol unique id. (application specific id.)*/
static unsigned int sym_cnt;

static int get_new_sym_id(void) {
    return sym_cnt++;
}

void sym_add_decl(void) {
}

struct symbol *alloc_sym(void) {
    struct symbol *ret;

    ret = malloc(sizeof(struct symbol));
    memset(ret, 0, sizeof(struct symbol));
    ret->id = get_new_sym_id();
    return ret;
}


struct symbol* add_symbol(struct symbol **head, int sym_type, const char* sym_name) {
    struct symbol *sym;

    //printf(">>sym add[%s]....\n", sym_name);
    sym = alloc_sym();
    sym->symbol_type = sym_type;
    sym->symbol_name = strdup(sym_name);
    HASH_ADD_STR(*head, symbol_name, sym);
    return sym;
}

/*
void update_enum_val(struct symbol* sym, int val) {
    sym->symbol_value = val;
    set_enum_index(val + 1);
}
*/

void init_symtable(void) {
    printf("init sym table...\n");
    sym_cnt = 0;
}

static void free_symbol(struct symbol* sym) {
    free(sym->symbol_name);
    free(sym);
}

static void print_sym(struct symbol* sym) {
    struct symbol *current_sym, *tmp;

    printf("[%50s ]: id:%d, type:%d", sym->symbol_name, sym->id, sym->symbol_type);
/*    if (sym->symbol_type == SYM_ENUM) {
        printf(", value:%d", sym->symbol_value);
    }*/
    printf("\n");
}

void clear_symtable(struct symbol *sym) {
    struct symbol *s1, *s2;

    printf("\nsymbol table clean up...\n");
    HASH_ITER(hh, sym, s1, s2) {
        print_sym(s1);
        HASH_DEL(sym, s1);
        free_symbol(s1);
    }
}

