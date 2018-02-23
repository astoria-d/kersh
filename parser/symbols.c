
#include <stdio.h>
#include <string.h>

#include "symbols.h"
#include "parser.h"

/*symbol unique id. (application specific id.)*/
static unsigned int sym_cnt;

static struct symbol *current_sym_table;

void set_sym_table(struct symbol *sym) {
    current_sym_table = sym;
}

static int get_new_sym_id(void) {
    return sym_cnt++;
}

void sym_add_decl(void) {
}

static struct symbol *alloc_sym(void) {
    struct symbol *ret;

    ret = malloc(sizeof(struct symbol));
    memset(ret, 0, sizeof(struct symbol));
    ret->id = get_new_sym_id();
    return ret;
}


struct symbol* add_symbol(int sym_type, const char* sym_name, struct type_definition* tdef) {
    struct symbol *sym;

    sym = alloc_sym();
    sym->symbol_type = sym_type;
    sym->symbol_name = (char*) sym_name;
    sym->type = tdef;
    HASH_ADD_STR(current_sym_table, symbol_name, sym);
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
    current_sym_table = NULL;
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

void clear_symtable(void) {
    struct symbol *current_sym, *tmp;

    printf("\nsymbol table clean up...\n");
    HASH_ITER(hh, current_sym_table, current_sym, tmp) {
        print_sym(current_sym);
        HASH_DEL(current_sym_table, current_sym);
        free_symbol(current_sym);
    }
}

