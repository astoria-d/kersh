
#ifndef __declaration_h__
#define __declaration_h__

#include "parser.h"

enum DC_TYPE {
    DC_INVALID = 0  , /*invalid type...*/
    DC_BASE_0       , /*void*/
    DC_BASE_1       , /*char*/
    DC_BASE_2       , /*short*/
    DC_BASE_4       , /*int*/
    DC_BASE_8       , /*long*/
    DC_BASE_16      , /*long long*/
    DC_T_DEFINED    , /*typedef-ed type*/
    DC_STRUCT_SPEC  ,
    DC_UNION_SPEC   ,
    DC_ENUM_SPEC    ,
    DC_STRUCT       ,
    DC_UNION        ,
    DC_ENUM         ,
};


struct declaration {
    enum DC_TYPE                type;

    union {
        struct declaration *        decl_spec;  /* enum/struct/union specifier */
        struct declaration*         ref;        /* pointer to typedef org */
    };

    struct token_list*          name;

    unsigned int                size;
    long                        value;          /*enum value*/

    struct qualifier {
        unsigned char       is_unsigned     : 1;
        unsigned char       is_pointer      : 1;
        unsigned char       is_array        : 1;
        unsigned char       is_const        : 1;
        unsigned char       is_volatile     : 1;
        unsigned char       internal_def    : 1;
        unsigned char       is_typedef      : 1;
        unsigned char       has_init_val    : 1;
    } ql;
    int                         pointer_cnt;

    struct declaration*         members;
    struct declaration*         next;
};

struct declaration* alloc_declarator(struct token_list* tk);

void dump_declaration(struct declaration* decl);

#endif /*__declaration_h__*/

