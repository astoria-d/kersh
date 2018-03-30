
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utlist.h"
#include "types.h"
#include "util.h"


void copy_type(struct type_definition* src, struct type_definition* dst) {
    int ptr;
    int ar;

    /*pointer and array are not set for each declaration*/
    ptr = dst->ql.is_pointer;
    ar = dst->ql.is_array;
    dst->type_id = src->type_id;
    if (src->type_name) dst->type_name = ker_strdup(src->type_name);
    dst->size = src->size;
    dst->value = src->value;
    dst->ref = src->ref;
    dst->ql = src->ql;
    dst->ql.is_pointer = ptr;
    dst->ql.is_array = ar;

    /* pointer set is not copied.
     * dst->pointer_cnt = src->pointer_cnt;
     * dst->name = ker_strdup(src->name);*/
}

void add_array(struct type_definition* td, unsigned int size) {
    struct dimension *new_arr_dim;
    new_arr_dim = ker_malloc(sizeof(struct dimension));
    new_arr_dim->size = size;
    LL_PREPEND(td->array_size, new_arr_dim);
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

void print_typedef(struct type_definition** head, int indent) {
    struct type_definition *mem;
    int i;

    LL_FOREACH(*head, mem) {
        char arr[100];
        char ptr[100], *p;
        struct dimension* dim;

        for (i = 0; i < indent; i++) printf("  ");

        /*create pointer type*/
        p = ptr;
        memset(ptr, 0, sizeof(ptr));
        for(i = 0; i < mem->pointer_cnt; i++) *p++ = '*';

        /*create array*/
        p = arr;
        LL_FOREACH(mem->array_size, dim) {
            p += sprintf(p, "[%d]", dim->size);
        }

        if (mem->type_id == TP_STRUCT || mem->type_id == TP_UNION) {
            char str_ty[100];

            if (mem->name) {
                sprintf(str_ty, "%s %s", tname_arr[mem->type_id], mem->type_name);
                printf("- %-50s type:%s%s%s, size:%d\n",
                        mem->name, str_ty,
                        mem->ql.is_pointer ? ptr : "",
                        mem->ql.is_array ? arr : "",
                        mem->size);
            }
            else {
                sprintf(str_ty, "%s %s", tname_arr[mem->type_id], mem->type_name);
                printf("- %-50s type:%s def, size:%d\n",
                        mem->type_name, tname_arr[mem->type_id], mem->size);
            }
            if (mem->members) {
                print_typedef(&mem->members, indent + 1);
            }
        }
        else if (mem->type_id == TP_ENUM_DEF) {
            printf("- %-50s type:%s def\n", mem->name, tname_arr[mem->type_id], mem->size);
            if (mem->members) {
                print_typedef(&mem->members, indent + 1);
            }
        }
        else {

            printf("- %-50s type:%s%s%s, size:%d", mem->name,
                    mem->ref ? mem->ref->name : tname_arr[mem->type_id],
                    mem->ql.is_pointer ? ptr : "",
                    mem->ql.is_array ? arr : "",
                            mem->size);
            if (mem->type_id == TP_ENUM) {
                printf(", value:%d", mem->value);
            }
            if (mem->ql.is_typedef) {
                printf(", typedef");
            }
            printf("\n");
        }
    }
}

struct type_definition* alloc_typedef(void) {
    struct type_definition* td;

    td = ker_malloc(sizeof(struct type_definition));
    memset(td, 0, sizeof(struct type_definition));
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
