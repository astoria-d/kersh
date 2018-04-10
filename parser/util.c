
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


static int alloc_cnt;
static int free_cnt;

void init_utils(void) {
    alloc_cnt = 0;
    free_cnt = 0;
    //printf("init_utils\n");
}


void exit_utils(void) {
    //printf("exit_utils\n");
    printf("allocation check...\n");
    printf("    allocation cnt: %d, free cnt: %d\n", alloc_cnt, free_cnt);
}

void *ker_malloc(size_t size) {
    void *ret;
    alloc_cnt++;
    ret = malloc(size);
    memset(ret, 0, size);
    //printf("ker_malloc %x\n", ret);
    return ret;
}

void ker_free(void *ptr) {
    free_cnt++;
    free(ptr);
}

char *ker_strdup(const char *s) {
    alloc_cnt++;
    return strdup(s);
}

