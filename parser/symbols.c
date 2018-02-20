
#include <stdio.h>
#include <string.h>

#include "symbols.h"
#include "parser.h"

/*symbol unique id. (application specific id.)*/
static unsigned int sym_cnt;
static struct symbol * symbols;

static struct symbol *work_symbol;
static char *tmp_symbol_buf;

static int get_new_sym_id(void) {
    return sym_cnt++;
}

static void clear_sym_buf(void) {
    if (tmp_symbol_buf != NULL) {
        free(tmp_symbol_buf);
    }
    tmp_symbol_buf = NULL;
}

void set_last_symbol(const char* sym_name) {
    clear_sym_buf();
    tmp_symbol_buf = strdup(sym_name);
}

void add_symbol(void) {
    printf(">>add sym [%s]", tmp_symbol_buf);
}

void add_enum_symbol(const char* enum_name, int val) {
    struct symbol *sym;

    sym = malloc(sizeof(struct symbol));
    sym->id = get_new_sym_id();
    sym->symbol_type = SYM_ENUM;
    sym->data_size = sizeof(int);
    sym->symbol_name = strdup(enum_name);
    sym->symbol_value = val;

    work_symbol = sym;
    HASH_ADD_STR(symbols, symbol_name, sym);
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
    symbols = NULL;
    tmp_symbol_buf = NULL;
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
    HASH_ITER(hh, symbols, current_sym, tmp) {
        print_sym(current_sym);
        HASH_DEL(symbols, current_sym);
        free_symbol(current_sym);
    }
    clear_sym_buf();
}

