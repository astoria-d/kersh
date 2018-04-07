
#ifndef __expressions_h__
#define __expressions_h__

struct expression {
    long                    value;
    struct expression*      sub_exp;
};

#endif /*__expressions_h__*/

