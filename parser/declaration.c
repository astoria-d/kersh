
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "declaration.h"
#include "utlist.h"
#include "code.h"

struct type_specifier* alloc_type_spec(struct ctoken* tk) {
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

    case TYPEDEF_NAME:
        ts->type = TS_TDEFNAME;
        ts->identifer = tk;
        remove_token(tk);
        break;

    case SIGNED:
        ts->is_unsigned = 0;
        break;
    case UNSIGNED:
        ts->is_unsigned = 1;
        break;

    case CONST:
        ts->ql.is_const = 1;
        break;
    case VOLATILE:
        ts->ql.is_volatile = 1;
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

struct declaration* alloc_decl_spec(struct ctoken* tk) {
    struct declaration* dspec;
    dspec = ker_malloc(sizeof(struct declaration));
    add_decl_spec(dspec, tk);
//    printf("alloc_declarator st: %x, exp: %x\n", dcr, tk);
    return dspec;
}

struct declaration* add_type_spec(struct declaration* dc, struct type_specifier* ts) {
    dc->type_spec = ts;
    if (ts->type == TS_STRUCT_SPEC) dc->is_struct = 1;
    if (ts->type == TS_UNION_SPEC) dc->is_union = 1;
    return dc;
}

struct declaration* add_decl_spec(struct declaration* dc, struct ctoken* tk) {
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

struct declaration* alloc_declarator(struct ctoken* tk) {
    struct declaration* dcr;
    dcr = ker_malloc(sizeof(struct declaration));
    dcr->identifer = tk;
    remove_token(tk);
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

struct type_specifier* alloc_enum_spec(struct ctoken* tk, struct declaration* enumerators) {
    struct type_specifier* tspec;

    tspec = ker_malloc(sizeof(struct type_specifier));
    tspec->type = TS_ENUM_SPEC;
    tspec->members = enumerators;
    tspec->identifer = tk;
    remove_token(tk);
    return tspec;
}

struct declaration* alloc_enumerator(struct ctoken* tk, struct expression* exp) {
    struct declaration* decl;
    //printf("enum...\n");
    decl = ker_malloc(sizeof(struct declaration));
    decl->is_enum = 1;
    decl->identifer = tk;
    decl->init_exp = exp;
    remove_token(tk);
    return decl;
}

struct type_specifier* alloc_struct_spec(struct ctoken* tk, struct ctoken* iden, struct declaration* str_decl) {
    struct type_specifier* tspec;

    tspec = ker_malloc(sizeof(struct type_specifier));
    if (tk->token == TK_STRUCT) {
        tspec->type = TS_STRUCT_SPEC;
    }
    else {
        tspec->type = TS_UNION_SPEC;
    }
    tspec->members = str_decl;
    tspec->identifer = iden;
    remove_token(tk);
    remove_token(iden);
    return tspec;
}

void dump_typespec(struct type_specifier* ts, int indent) {
    const char* p;
    print_indent(indent);

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
    case TS_TDEFNAME:
        p = ts->identifer->strval;
        break;
    case TS_ENUM_SPEC:
        if (ts->identifer) {
            printf("enum %s", ts->identifer->strval);
        }
        else {
            printf("enum");
        }
        if (ts->members) {
            printf(" { ");
            dump_declaration(ts->members, 0, 0);
            printf("}");
        }
        break;
    case TS_STRUCT_SPEC:
    case TS_UNION_SPEC:
        if (ts->type == TS_STRUCT_SPEC) {
            printf("struct");
        }
        else {
            printf("union");
        }
        if (ts->identifer->strval) {
            printf(" %s ", ts->identifer->strval);
        }
        if (ts->members) {
            struct declaration* fld;
            printf("{\n");
            LL_FOREACH(ts->members, fld) {
                //print_indent(indent);
                if (fld->is_struct || fld->is_union) {
                    dump_typespec(fld->type_spec, indent + 1);
                    printf(" %s ;\n", fld->identifer->strval);
                }
                else {
                    dump_declaration(fld, indent + 1, 0);
                }
            }
            print_indent(indent);
            printf("}");
        }
        break;
    }
    if (p) printf("%s", p);

    if (ts->next) {
        printf(" ");
        dump_typespec(ts->next, 0);
    }
}

void dump_declaration(struct declaration* decl, int indent, int iterate) {
    struct declaration* d;
    LL_FOREACH(decl, d) {
        if (d->is_func) continue;
        print_indent(indent);

        if (d->dc.is_typedef) {
            printf("typedef ");
        }
        if (d->dc.is_extern) {
            printf("extern ");
        }
        if (d->dc.is_static) {
            printf("static ");
        }
        if (d->dc.is_auto) {
            printf("auto ");
        }
        if (d->dc.is_register) {
            printf("register ");
        }
        if (d->dc.is_const) {
            printf("const ");
        }
        if (d->dc.is_volatile) {
            printf("volatile ");
        }
        if (d->dc.is_inline) {
            printf("inline ");
        }

        if (!d->is_enum) {
            /*enumerator doesn't have the typespec.*/
            dump_typespec(d->type_spec, 0);
            printf(" ");
            if (d->identifer) {
                printf("%s ;\n", d->identifer->strval);
            }
            else {
                printf(";\n");
            }
        }
        else {
            printf("%s", d->identifer->strval);
            if (d->init_exp) {
                printf(" = ");
                dump_expression(d->init_exp, 0);
            }
            printf(", ");
        }

        if (!iterate) break;
    }
}

/*declaration semantics check.*/
void declaration_1(struct declaration* dcl) {
    //printf("declaration semantics chec\n");
    if (dcl->dc.is_typedef) {
        /*register the typedef_name.*/
    }
}

/*register symbol table.*/
void translation_unit_0(struct declaration* dcl) {
    add_symbol(dcl);
}

void translation_unit_1(struct declaration* dcl) {
    struct declaration *d, *last;
    LL_FOREACH(dcl, d) {
        last = d;
    }
    add_symbol(last);
}
