
#ifndef __types_h__
#define __types_h__


enum TP {
    TP_INVALID = 0  , /*invalid type...*/
    TP_BASE_0       , /*void*/
    TP_BASE_1       , /*char*/
    TP_BASE_2       , /*short*/
    TP_BASE_4       , /*int*/
    TP_BASE_8       , /*long*/
    TP_BASE_16      , /*long long*/
    TP_ENUM_DEF     , /*enum block definition*/
    TP_ENUM         , /*enum entry definition*/
    TP_STRUCT       , /*struct field definition*/
    TP_UNION        , /*union field definition*/
};

struct type_definition {
    enum TP                     type_id;
    char*                       type_name;
    char*                       name;
    unsigned int                size;
    int                         value;

    struct qualifier {
        unsigned char       is_unsigned     : 1;
        unsigned char       is_pointer      : 1;
        unsigned char       is_array        : 1;
        unsigned char       is_const        : 1;
        unsigned char       is_volatile     : 1;
        unsigned char       internal_def    : 1;
        unsigned char       is_typedef      : 1;
    } ql;
    int                         pointer_cnt;
    int                         array_cnt;

    struct type_definition*    members;
    struct type_definition*    next;
    struct type_definition*    ref;
};

struct type_definition* alloc_typedef(void);
void free_typedef(struct type_definition** head);
void print_typedef(struct type_definition** head, int indent);
void copy_type(struct type_definition* src, struct type_definition* dst);

#endif /*__types_h__*/

