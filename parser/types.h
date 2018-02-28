
#ifndef __types_h__
#define __types_h__


enum {
    TP_BASE_0 = 1   , /*void*/
    TP_BASE_1       , /*char*/
    TP_BASE_2       , /*short*/
    TP_BASE_4       , /*int*/
    TP_BASE_8       , /*long*/
    TP_BASE_16      , /*long long*/
    TP_ENUM         ,
    TP_TYPEDEF      ,
    TP_STRUCT       ,
    TP_UNION        ,
};

struct typedef_list;

struct type_definition {
    unsigned char               type_id;
    char*                       name;
    unsigned int                size;
    int                         value;

    struct qualifier {
        unsigned char       is_unsigned     : 1;
        unsigned char       is_pointer      : 1;
        unsigned char       is_array        : 1;
        unsigned char       is_const        : 1;
        unsigned char       is_volatile     : 1;
    } ql;
    int                         pointer_cnt;
    int                         array_cnt;

    struct typedef_list*        subtypes;
    union {
        struct type_definition*     members;
        struct type_definition*     next;
    };
};

struct typedef_list {
    struct type_definition  type;
    struct typedef_list*    next;
};

struct typedef_list* alloc_typedef_list(void);
void free_typedef_list(struct typedef_list** head);

struct type_definition* alloc_typedef(void);

#endif /*__types_h__*/

