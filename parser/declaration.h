
#ifndef __declaration_h__
#define __declaration_h__

#include "parser.h"
#include "function.h"
#include "expression.h"

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
    TS_TDEFNAME     ,
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

    /*declaration or function or enumerator .*/
    unsigned char           is_func;
    unsigned char           is_enum;

    union {
        /*case declaration. declaration has type and identifier*/
        struct {
            struct type_specifier*      type_spec;
            struct ctoken*              identifer;
        };
        /*case function definition.*/
        struct function*                func;
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

    /*enum elm init values.*/
    struct expression*      init_exp;

    /*function parameters.*/
    struct declaration*     param;

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
struct declaration* add_param(struct declaration* func_name, struct declaration* param);


struct type_specifier* alloc_enum_spec(struct ctoken* tk, struct declaration* enumerators);
struct declaration* alloc_enumerator(struct ctoken* tk, struct expression* exp);

struct type_specifier* alloc_struct_spec(struct ctoken* tk, struct ctoken* iden, struct declaration* str_decl);

void dump_typespec(struct type_specifier* ts, int indent);
void dump_declaration(struct declaration* decl, int indent, int iterate);

void declaration_1(struct declaration* dcl);
void translation_unit_0(struct declaration* dcl);
void translation_unit_1(struct declaration* dcl);


#endif /*__declaration_h__*/

