
#include <stdio.h>
#include <string.h>

#include "symbols.h"
#include "parser.h"
#include "util.h"

/*symbol unique id. (application specific id.)*/
static unsigned int sym_cnt;

static int get_new_sym_id(void) {
    return sym_cnt++;
}

void sym_add_decl(void) {
}

static struct symbol *alloc_sym(void) {
    struct symbol *ret;

    ret = ker_malloc(sizeof(struct symbol));
    memset(ret, 0, sizeof(struct symbol));
    ret->id = get_new_sym_id();
    return ret;
}


struct symbol* add_symbol(struct symbol **head, int sym_type, const char* sym_name) {
    struct symbol *sym;

    //printf(">>sym add[%s]....\n", sym_name);
    sym = alloc_sym();
    sym->symbol_type = sym_type;
    sym->symbol_name = ker_strdup(sym_name);
    HASH_ADD_STR(*head, symbol_name, sym);
    return sym;
}

/*
void update_enum_val(struct symbol* sym, int val) {
    sym->symbol_value = val;
    set_enum_index(val + 1);
}
*/

void init_symbols(void) {
    printf("init sym table...\n");
    sym_cnt = 0;
}

static void free_symbol(struct symbol* sym) {
    ker_free(sym->symbol_name);
    ker_free(sym);
}

static void print_symtable(struct symbol* sym) {
    struct symbol *current_sym, *tmp;

    printf("[%50s ]: id:%d, type:%d", sym->symbol_name, sym->id, sym->symbol_type);
/*    if (sym->symbol_type == SYM_ENUM) {
        printf(", value:%d", sym->symbol_value);
    }*/
    printf("\n");
}

void free_symtable(struct symbol **head) {
    struct symbol *s1, *s2;

    //printf("head: %08x\n", *head);
    printf("\nsymbol table clean up...\n");
    HASH_ITER(hh, *head, s1, s2) {
        print_symtable(s1);
        HASH_DEL(*head, s1);
        free_symbol(s1);
        //printf("s1: %08x\n", s1);
    }
}

