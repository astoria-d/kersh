
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utlist.h"
#include "types.h"

struct typedef_list* alloc_typedef_list(void) {
    struct typedef_list* tdl;

    tdl = malloc(sizeof(struct typedef_list));
    memset(tdl, 0, sizeof(struct typedef_list));
    return tdl;
}

struct type_definition* alloc_typedef(void) {
    struct type_definition* td;

    td = malloc(sizeof(struct type_definition));
    memset(td, 0, sizeof(struct type_definition));
    return td;
}

static void print_typedef(struct typedef_list* tdl, int indent) {
    struct type_definition *mem;
    int i;

    for (i = 0; i < indent; i++) printf("  ");
    printf("[%-50s ]: type:%d, size:%d", tdl->type.name, tdl->type.type_id, tdl->type.size);
    printf("\n");
    LL_FOREACH(&tdl->type, mem) {
        if (&tdl->type == mem) continue;
        for (i = 0; i < indent; i++) printf("  ");
        printf("  [%-48s ]: type:%d, size:%d\n", mem->name, mem->type_id, mem->size);
    }
}

void free_typedef_list(struct typedef_list **head) {
    struct typedef_list *t1;

    printf("\ntypedef clean up...\n");
    LL_FOREACH(*head, t1) {
        struct type_definition *mem;
        print_typedef(t1, 0);
        LL_DELETE(*head, t1);

        LL_FOREACH(&t1->type, mem) {
            free(mem->name);
            free(mem);
        }
        //printf("s1: %08x\n", s1);
    }
}

