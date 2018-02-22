
#include <stdio.h>
#include <string.h>

#include "symbols.h"
#include "parser.h"

/*symbol unique id. (application specific id.)*/
static unsigned int sym_cnt;
static struct symbol * global_symbols;

static struct symbol *work_symbol;

static int get_new_sym_id(void) {
    return sym_cnt++;
}

void sym_add_decl(void) {
}

void sym_add_struct_def(const char* struct_name) {
    struct symbol *sym;

    sym = malloc(sizeof(struct symbol));
    sym->id = get_new_sym_id();
    sym->symbol_type = SYM_STRUCT;
    sym->data_size = 0;
    sym->symbol_name = (char*) struct_name;
    sym->symbol_value = 0;

    work_symbol = sym;
    /*skip anonymous struct/union */
    if (struct_name) {
        HASH_ADD_STR(global_symbols, symbol_name, sym);
    }
}

void sym_add_enum(const char* enum_name, int val) {
    struct symbol *sym;

    sym = malloc(sizeof(struct symbol));
    sym->id = get_new_sym_id();
    sym->symbol_type = SYM_ENUM;
    sym->data_size = sizeof(int);
    sym->symbol_name = strdup(enum_name);
    sym->symbol_value = val;

    work_symbol = sym;
    HASH_ADD_STR(global_symbols, symbol_name, sym);
    /*printf(">>add sym [%s:%d]", enum_name, val);*/
}

void update_enum_val(int val) {
    /*printf("update:%d\n", val);*/
    work_symbol->symbol_value = val;
    set_enum_index(val + 1);
}

void init_symtable(void) {
    printf("init sym table...\n");
    sym_cnt = 0;
    global_symbols = NULL;
}

static void free_symbol(struct symbol* sym) {
    free(sym->symbol_name);
    free(sym);
}

static void print_sym(struct symbol* sym) {
    printf("[%50s ]: id:%d, type:%d", sym->symbol_name, sym->id, sym->symbol_type);
    if (sym->symbol_type == SYM_ENUM) {
        printf(", value:%d", sym->symbol_value);
    }
    printf("\n");
}

void clear_symtable(void) {
    struct symbol *current_sym, *tmp;

    printf("\nsymbol table clean up...\n");
    HASH_ITER(hh, global_symbols, current_sym, tmp) {
        print_sym(current_sym);
        HASH_DEL(global_symbols, current_sym);
        free_symbol(current_sym);
    }
}

