
#ifndef __types_h__
#define __types_h__

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

