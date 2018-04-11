
#ifndef __declaration_h__
#define __declaration_h__

#include "parser.h"

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
    struct token_list*      identifer;
    unsigned char           is_unsigned;
    struct declaration*     members;
};

struct declaration {

    /*declaration type and identifier*/
    struct type_specifier*      type_spec;
    struct token_list*          identifer;

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

struct type_specifier* alloc_type_spec(struct token_list* tk);

struct declaration* declare(struct declaration* dclspec, struct declaration* declarator);

struct declaration* alloc_decl_spec(struct token_list* tk);
struct declaration* alloc_decl_spec_from_ts(struct type_specifier* ts);
struct declaration* add_type_spec(struct declaration* dc, struct type_specifier* ts);
struct declaration* add_decl_spec(struct declaration* dc, struct token_list* tk);

struct declaration* alloc_declarator(struct token_list* tk);
struct declaration* append_declarator(struct declaration* d1, struct declaration* d2);

void dump_declaration(struct declaration* decl);

#endif /*__declaration_h__*/

