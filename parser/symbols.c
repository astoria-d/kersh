
#include <stdio.h>
#include <string.h>

#include "symbols.h"
#include "parser.h"

/*symbol unique id. (application specific id.)*/
static unsigned int sym_cnt;

static struct symbol *global_symbols;
static struct symbol *work_symbol;

static int get_new_sym_id(void) {
    return sym_cnt++;
}

void sym_add_decl(void) {
}

static void add_sym(struct symbol *sym) {
/*    printf(">>addsym:%d...", sym->id);*/

    sym->parent_symbol =
        (work_symbol == NULL ? global_symbols :
            (work_symbol->parent_symbol == NULL ?
                global_symbols : work_symbol->parent_symbol));

    work_symbol = sym;
    if (sym->symbol_name) {
        if (global_symbols) {
            HASH_ADD_STR(sym->parent_symbol, symbol_name, sym);
        }
        else {
            HASH_ADD_STR(global_symbols, symbol_name, sym);
        }
    }
    else {
        /* anonymous struct/union case */
        if (global_symbols) {
            HASH_ADD_INT(sym->parent_symbol, id, sym);
        }
        else {
            HASH_ADD_INT(global_symbols, id, sym);
        }
    }
}

static struct symbol *alloc_sym(void) {
    struct symbol *ret;

    ret = malloc(sizeof(struct symbol));
    memset(ret, 0, sizeof(struct symbol));
    ret->id = get_new_sym_id();
    return ret;
}

void sym_add_struct_def(const char* struct_name) {
    struct symbol *sym;

    sym = alloc_sym();
    sym->symbol_type = SYM_STRUCT;
    sym->symbol_name = (char*) struct_name;
    add_sym(sym);
}

void sym_add_enum(const char* enum_name, int val) {
    struct symbol *sym;

    sym = alloc_sym();
    sym->symbol_type = SYM_ENUM;
    sym->data_size = sizeof(int);
    sym->symbol_name = strdup(enum_name);
    sym->symbol_value = val;
    add_sym(sym);
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
    work_symbol = NULL;
}

static void free_symbol(struct symbol* sym) {
    free(sym->symbol_name);
    free(sym);
}

static void print_sym(struct symbol* sym) {
    struct symbol *current_sym, *tmp;

    printf("[%50s ]: id:%d, type:%d, size:%d", sym->symbol_name, sym->id, sym->symbol_type, sym->data_size);
    if (sym->symbol_type == SYM_ENUM) {
        printf(", value:%d", sym->symbol_value);
    }
    printf("\n");
/*    HASH_ITER(hh, sym->child_symbol, current_sym, tmp) {
        print_sym(current_sym);
    }
*/
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

