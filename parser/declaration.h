
#ifndef __declaration_h__
#define __declaration_h__

#include "types.h"

struct declaration {
    char*                       name;
    unsigned char               is_pointer;
    struct type_definition*     type;
    unsigned long               value;
    struct declaration *        next;
};


#endif /*__declaration_h__*/

