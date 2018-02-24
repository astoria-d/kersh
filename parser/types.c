
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utlist.h"
#include "types.h"

struct typedef_list* alloc_typedef_list(void) {
    struct typedef_list* tdl;

    tdl = malloc(sizeof(struct typedef_list));
    memset(tdl, 0, sizeof(struct typedef_list));
    //printf("alloc tdl: %08x\n", tdl);
    return tdl;
}

struct type_definition* alloc_typedef(void) {
    struct type_definition* td;

    td = malloc(sizeof(struct type_definition));
    memset(td, 0, sizeof(struct type_definition));
    //printf("alloc td: %08x\n", td);
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
        printf("  [%-48s ]: type:%d, size:%d", mem->name, mem->type_id, mem->size);
        if (mem->type_id == TP_ENUM) {
            printf(", value:%d", mem->value);
        }
        printf("\n");
    }
}

void free_typedef_list(struct typedef_list **head) {
    struct typedef_list *t1, *t2;

    printf("\ntypedef clean up...\n");
    LL_FOREACH_SAFE(*head, t1, t2) {
        struct type_definition *def_head;
        struct type_definition *mem, *t3;

        //printf("t1: %08x\n", t1);
        print_typedef(t1, 0);
        LL_DELETE(*head, t1);
        def_head = &t1->type;

        /*LL_FOREACH_SAFE macro can't be used because address of 
        def_head and first t1 element is the same!*/
        mem = def_head->members;
        while(mem) {
            //printf("mem: %08x, %s\n", mem, mem->name);
            LL_DELETE(def_head, mem);
            free(mem->name);
            //printf("next: %08x, %08x\n", mem->next, t1->next);
            t3 = mem;
            mem = mem->next;
            free(t3);
        }
        //printf("next: %08x\n", t1->next);
        free(t1);
    }
}

