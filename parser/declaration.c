
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "declaration.h"
#include "utlist.h"

struct type_specifier* alloc_type_spec(struct token_list* tk) {
    struct type_specifier* ts;
    ts = ker_malloc(sizeof(struct type_specifier));
    switch (tk->token) {
    case VOID:
        ts->type = TS_VOID;
        break;
    case CHAR:
        ts->type = TS_CHAR;
        break;
    case SHORT:
        ts->type = TS_SHORT;
        break;
    case INT:
        ts->type = TS_INT;
        break;
    case LONG:
        ts->type = TS_LONG;
        break;

    case SIGNED:
        ts->is_unsigned = 0;
        break;
    case UNSIGNED:
        ts->is_unsigned = 1;
        break;
    }
    return ts;
}

struct type_specifier* append_type_spec(struct type_specifier* ts1, struct type_specifier* ts2) {
    LL_APPEND(ts1, ts2);
    return ts1;
}

struct declaration* declare(struct declaration* dclspec, struct declaration* declarator) {
    struct declaration* d;
    LL_FOREACH(declarator, d) {
        d->type_spec = dclspec->type_spec;
        d->dc = dclspec->dc;
    }
    return declarator;
}

struct declaration* alloc_decl_spec_from_ts(struct type_specifier* ts) {
    struct declaration* dspec;
    dspec = ker_malloc(sizeof(struct declaration));
    dspec->type_spec = ts;
//    printf("alloc_decl_spec_from_ts dspec: %x, ts: %x\n", dspec, ts);
    return dspec;
}

struct declaration* alloc_decl_spec(struct token_list* tk) {
    struct declaration* dspec;
    dspec = ker_malloc(sizeof(struct declaration));
    add_decl_spec(dspec, tk);
//    printf("alloc_declarator st: %x, exp: %x\n", dcr, tk);
    return dspec;
}

struct declaration* add_type_spec(struct declaration* dc, struct type_specifier* ts) {
    dc->type_spec = ts;
    return dc;
}

struct declaration* add_decl_spec(struct declaration* dc, struct token_list* tk) {
    switch (tk->token) {
    case TYPEDEF:
        dc->dc.is_typedef = 1;
        break;
    case EXTERN:
        dc->dc.is_extern = 1;
        break;
    case STATIC:
        dc->dc.is_static = 1;
        break;
    case AUTO:
        dc->dc.is_auto = 1;
        break;
    case REGISTER:
        dc->dc.is_register = 1;
        break;
    case CONST:
        dc->dc.is_const = 1;
        break;
    case VOLATILE:
        dc->dc.is_volatile = 1;
        break;
    case INLINE:
        dc->dc.is_inline = 1;
        break;
    }
    return dc;
}

struct declaration* alloc_declarator(struct token_list* tk) {
    struct declaration* dcr;
    dcr = ker_malloc(sizeof(struct declaration));
    dcr->identifer = tk;
//    printf("alloc_declarator st: %x, exp: %x\n", dcr, tk);
    return dcr;
}

struct declaration* append_declarator(struct declaration* d1, struct declaration* d2) {
    LL_APPEND(d1, d2);
    return d1;
}

struct declaration* alloc_dec_from_func(struct function* func) {
    struct declaration* decl;
    decl = ker_malloc(sizeof(struct declaration));
    decl->is_func = 1;
    decl->func = func;
//    printf("alloc_declarator st: %x, exp: %x\n", dcr, tk);
    return decl;
}

void dump_typespec(struct type_specifier* ts) {
    const char* p;

    if (ts->is_unsigned) {
        printf("unsigned");
    }

    p = NULL;
    switch (ts->type) {
    case TS_VOID:
        p = "void";
        break;
    case TS_CHAR:
        p = "char";
        break;
    case TS_SHORT:
        p = "short";
        break;
    case TS_INT:
        p = "int";
        break;
    case TS_LONG:
        p = "long";
        break;
    }
    if (p) printf("%s", p);

    if (ts->next) {
        printf(" ");
        dump_typespec(ts->next);
    }
}

void dump_declaration(struct declaration* decl, int indent) {
    struct declaration* d;
    LL_FOREACH(decl, d) {
        print_indent(indent);
        dump_typespec(d->type_spec);
        printf(" ");
        printf("%s ;\n", d->identifer->strval);
    }
}
