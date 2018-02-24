
#ifndef __types_h__
#define __types_h__


#define     TP_BASE_1       0
#define     TP_BASE_2       1
#define     TP_BASE_4       2
#define     TP_BASE_8       3
#define     TP_BASE_16      4
#define     TP_ENUM         5
#define     TP_TYPEDEF      6
#define     TP_STRUCT       7
#define     TP_UNION        8

struct type_definition {
    unsigned char               type_id;
    char*                       name;
    unsigned int                size;
    int                         value;
    unsigned char               is_unsigned;
    unsigned char               is_pointer;
    struct type_definition*     subtype;
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

