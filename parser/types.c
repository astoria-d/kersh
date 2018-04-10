
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utlist.h"
#include "types.h"
#include "util.h"


void copy_type(struct type_definition* src, struct type_definition* dst) {
    int ptr;
    int ar;
    int init_val;

    /*pointer and array are not set for each declaration*/
    ptr = dst->ql.is_pointer;
    ar = dst->ql.is_array;
    init_val = dst->ql.has_init_val;
    dst->type_id = src->type_id;
    if (src->type_name) dst->type_name = ker_strdup(src->type_name);
    dst->size = src->size;
    dst->value = src->value;
    dst->ref = src->ref;
    dst->ql = src->ql;

    dst->ql.is_pointer = ptr;
    dst->ql.is_array = ar;
    dst->ql.has_init_val = init_val;

    /* pointer set is not copied.
     * dst->pointer_cnt = src->pointer_cnt;
     * dst->name = ker_strdup(src->name);*/
}

void add_array(struct type_definition* td, unsigned int size) {
    struct dimension *new_arr_dim;
    new_arr_dim = ker_malloc(sizeof(struct dimension));
    new_arr_dim->size = size;
    LL_APPEND(td->array_size, new_arr_dim);
}

unsigned int get_size(struct type_definition* td) {
    if (td->ql.is_array) {
        unsigned int sz;
        struct dimension* dim;

        sz = 0;
        LL_FOREACH(td->array_size, dim) {
            sz += dim->size * td->size;
        }
        return sz;
    }
    else {
        return td->size;
    }
}

static char* tname_arr[] = {
                    "invalid"       ,
/*TP_BASE_0   */    "void"          ,
/*TP_BASE_1   */    "char"          ,
/*TP_BASE_2   */    "short"         ,
/*TP_BASE_4   */    "int"           ,
/*TP_BASE_8   */    "long"          ,
/*TP_BASE_16  */    "longlong"      ,
/*TP_ENUM_DEF */    "enum"          ,
/*TP_ENUM     */    "enum"          ,
/*TP_STRUCT   */    "struct"        ,
/*TP_UNION    */    "union"         ,
};

void print_typedef(struct type_definition** head, int level) {
    struct type_definition *tp;
    int i;

    LL_FOREACH(*head, tp) {
        char arr[100];
        char ptr[100], *p;
        struct dimension* dim;

        for (i = 0; i < level; i++) printf("  ");

        /*create pointer type*/
        p = ptr;
        memset(ptr, 0, sizeof(ptr));
        for(i = 0; i < tp->pointer_cnt; i++) *p++ = '*';

        /*create array*/
        p = arr;
        LL_FOREACH(tp->array_size, dim) {
            p += sprintf(p, "[%d]", dim->size);
        }

        if (tp->type_id == TP_STRUCT || tp->type_id == TP_UNION) {
            char str_ty[100];

            if (tp->name || level > 0) {
                sprintf(str_ty, "%s %s", tname_arr[tp->type_id], tp->type_name);
                printf("- %-50s type:%s%s%s, size:%d\n",
                        tp->name, str_ty,
                        tp->ql.is_pointer ? ptr : "",
                        tp->ql.is_array ? arr : "",
                        tp->size);
            }
            else {
                sprintf(str_ty, "%s %s", tname_arr[tp->type_id], tp->type_name);
                printf("- %-50s type:%s def, size:%d\n",
                        tp->type_name, tname_arr[tp->type_id], tp->size);
            }
            if (tp->members) {
                print_typedef(&tp->members, level + 1);
            }
        }
        else if (tp->type_id == TP_ENUM_DEF) {
            printf("- %-50s type:%s def\n", tp->name, tname_arr[tp->type_id], tp->size);
            if (tp->members) {
                print_typedef(&tp->members, level + 1);
            }
        }
        else {

            printf("- %-50s type:%s%s%s, size:%d", tp->name,
                    tp->ref ? tp->ref->name : tname_arr[tp->type_id],
                    tp->ql.is_pointer ? ptr : "",
                    tp->ql.is_array ? arr : "",
                            tp->size);
            if (tp->type_id == TP_ENUM) {
                printf(", value:%d", tp->value);
            }
            if (tp->ql.is_typedef) {
                printf(", typedef");
            }
            printf("\n");
        }
    }
}

struct type_definition* alloc_typedef(void) {
    struct type_definition* td;

    td = ker_malloc(sizeof(struct type_definition));
    //printf("alloc td: %08x\n", td);
    return td;
}

void free_typedef(struct type_definition** head) {
    struct type_definition *df, *tmp;

    LL_FOREACH_SAFE(*head, df, tmp) {
        LL_DELETE(*head, df);

        if (df->type_id == TP_ENUM_DEF) {
            free_typedef(&df->members);
        }
        else if (df->type_id == TP_STRUCT || df->type_id == TP_UNION) {
            free_typedef(&df->members);
        }

        if (df->name) ker_free (df->name);
        if (df->type_name) ker_free (df->type_name);
        if (df->array_size) {
            struct dimension *dim, *dtmp;
            LL_FOREACH_SAFE(df->array_size, dim, dtmp) {
                LL_DELETE(df->array_size, dim);
                ker_free(dim);
            }
        }

        ker_free(df);
    }
}
