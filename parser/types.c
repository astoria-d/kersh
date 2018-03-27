
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utlist.h"
#include "types.h"
#include "util.h"


void copy_type(struct type_definition* src, struct type_definition* dst) {
    dst->type_id = src->type_id;
    if (src->type_name) dst->type_name = ker_strdup(src->type_name);
    dst->size = src->size;
    dst->value = src->value;
    dst->pointer_cnt = src->pointer_cnt;
    dst->array_cnt = src->array_cnt;
    dst->ref = src->ref;
    dst->ql = src->ql;

    /*dst->name = ker_strdup(src->name);*/
}

static char* tname_arr[] = {
                    "invalid"       ,
/*TP_BASE_0   */    "void"          ,
/*TP_BASE_1   */    "char"          ,
/*TP_BASE_2   */    "short"         ,
/*TP_BASE_4   */    "int"           ,
/*TP_BASE_8   */    "long"          ,
/*TP_BASE_16  */    "longlong"      ,
/*TP_ENUM_DEF */    "enum(def)"     ,
/*TP_ENUM     */    "enum"          ,
/*TP_STRUCT   */    "struct"        ,
/*TP_UNION    */    "union"         ,
};

void print_typedef(struct type_definition** head, int indent) {
    struct type_definition *mem;
    int i;

    LL_FOREACH(*head, mem) {
        for (i = 0; i < indent; i++) printf("  ");
        if (mem->type_id == TP_STRUCT || mem->type_id == TP_UNION) {
            printf("- %s:%-50s type:%s, size:%d\n", mem->type_name, mem->name, tname_arr[mem->type_id], mem->size);
            if (mem->members) {
                print_typedef(&mem->members, indent + 1);
            }
        }
        else if (mem->type_id == TP_ENUM_DEF) {
            printf("- %-50s type:%s\n", mem->name, tname_arr[mem->type_id], mem->size);
            if (mem->members) {
                print_typedef(&mem->members, indent + 1);
            }
        }
        else {
            printf("- %-50s type:%s%s, size:%d", mem->name,
                    mem->ref ? mem->ref->name : tname_arr[mem->type_id],
                    mem->ql.is_pointer ? "*" : "",
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

        ker_free(df);
    }
}
