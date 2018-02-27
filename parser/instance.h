
#ifndef __instance_h__
#define __instance_h__

#include "types.h"

struct instance {
    char*                       name;
    unsigned char               is_pointer;
    struct type_definition*     type;
    unsigned long               value;
};

struct instance_list {
    struct instance         inst;
    struct instance_list    *next;
};


#endif /*__instance_h__*/

