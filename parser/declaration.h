
#ifndef __declaration_h__
#define __declaration_h__

#include "parser.h"
#include "function.h"

enum TS_TYPE {
    TS_INVALID = 0  , /*invalid type...*/
    TS_VOID         ,
    TS_CHAR         ,
    TS_SHORT        ,
    TS_INT          ,
    TS_LONG         ,
    TS_STRUCT_SPEC  ,
    TS_UNION_SPEC   ,
    TS_ENUM_SPEC    ,
    TS_TDEF_SPEC    ,
};

struct declaration;

struct type_specifier {
    enum TS_TYPE            type;
    struct ctoken*          identifer;
    unsigned char           is_unsigned;
    struct declaration*     members;

    /*type qualifier*/
    struct {
        unsigned char       is_const        : 1;
        unsigned char       is_volatile     : 1;
    } ql;

    struct type_specifier*  next;
};

struct declaration {

    /*declaration or function.*/
    unsigned char           is_func;
    union {
        /*case declaration. declaration has type and identifier*/
        struct {
            struct type_specifier*      type_spec;
            struct ctoken*              identifer;
        };
        /*case function definition.*/
        struct function* func;
    };

    unsigned int                size;
    long                        value;          /*enum value*/

    /*declaration specifier*/
    struct {
        unsigned char       is_typedef      : 1;
        unsigned char       is_extern       : 1;
        unsigned char       is_static       : 1;
        unsigned char       is_auto         : 1;
        unsigned char       is_register     : 1;
        unsigned char       is_const        : 1;
        unsigned char       is_volatile     : 1;
        unsigned char       is_inline       : 1;
    } dc;

    struct attribute {
        unsigned char       is_pointer      : 1;
        unsigned char       is_array        : 1;
        unsigned char       has_init_val    : 1;
    } atr;
    int                         pointer_cnt;

    struct declaration*         next;
};

struct type_specifier* alloc_type_spec(struct ctoken* tk);
struct type_specifier* append_type_spec(struct type_specifier* ts1, struct type_specifier* ts2);

struct declaration* declare(struct declaration* dclspec, struct declaration* declarator);

struct declaration* alloc_decl_spec(struct ctoken* tk);
struct declaration* alloc_decl_spec_from_ts(struct type_specifier* ts);
struct declaration* add_type_spec(struct declaration* dc, struct type_specifier* ts);
struct declaration* add_decl_spec(struct declaration* dc, struct ctoken* tk);

struct declaration* alloc_declarator(struct ctoken* tk);
struct declaration* append_declarator(struct declaration* d1, struct declaration* d2);

#define append_declaration append_declarator

struct declaration* alloc_dec_from_func(struct function* func);

void dump_typespec(struct type_specifier* ts);
void dump_declaration(struct declaration* decl, int indent, int iterate);

void declaration_1(struct declaration* dcl);
void translation_unit_0(struct declaration* dcl);
void translation_unit_1(struct declaration* dcl);


#endif /*__declaration_h__*/

