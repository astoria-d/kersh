
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utlist.h"
#include "types.h"

struct type_definition* alloc_typedef(void) {
    struct type_definition* td;

    td = malloc(sizeof(struct type_definition));
    memset(td, 0, sizeof(struct type_definition));
    //printf("alloc td: %08x\n", td);
    return td;
}

void print_typedef(struct type_definition** head, int indent) {
    struct type_definition *mem;
    int i;

    LL_FOREACH(*head, mem) {
        for (i = 0; i < indent; i++) printf("  ");
        printf("- %-50s type:%d, size:%d", mem->name, mem->type_id, mem->size);
        if (mem->type_id == TP_ENUM) printf(", value:%d", mem->value);
        printf("\n");
        if (mem->type_id == TP_STRUCT || mem->type_id == TP_UNION || mem->type_id == TP_ENUM) {
            print_typedef(&mem->members, indent + 1);
        }
    }
}

void free_typedef(struct type_definition** head) {
    struct type_definition *df, *tmp;

    LL_FOREACH_SAFE(*head, df, tmp) {
        LL_DELETE(*head, df);

        if (df->type_id == TP_STRUCT || df->type_id == TP_UNION || df->type_id == TP_ENUM) {
            free_typedef(&df->members);
        }

        if (df->name) free (df->name);
        if (df->type_name) free (df->type_name);
        free(df);
    }
}
