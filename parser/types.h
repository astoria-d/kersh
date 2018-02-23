
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
    struct type_definition*     members;
    struct type_definition*     subtype;
};

struct type_def_list {
    struct type_definition  type;
    struct type_def_list*   next;
    struct type_def_list*   prev;
};

#endif /*__types_h__*/

