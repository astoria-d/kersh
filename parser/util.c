
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "parser.h"


static int alloc_cnt;
static int free_cnt;

static unsigned int pr_indent;
static unsigned int pr_newline;

static unsigned int disable_pr_tkn;


#define INDENT_SPACE "  "

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

void print_indent(int indent) {
    int i;
    for (i = 0; i < indent; i++) {
         printf(INDENT_SPACE);
    }
}

/* print utilities....*/

void indent_inc(void) {
    pr_indent++;
}

void indent_dec(void) {
    pr_indent--;
}

void line_break(void) {
    if (disable_pr_tkn) return;
    printf("\n");
    pr_newline = 1;
}

void print_token(const char* parse_text) {
    if (disable_pr_tkn) return;
    if (pr_newline) {
        int i;
        for (i = 0; i < pr_indent; i++) {
             printf("  ");
        }
    }
    pr_newline = 0;
    printf("%s ", parse_text);
}

void init_utils(void) {
    alloc_cnt = 0;
    free_cnt = 0;
    //printf("init_utils\n");
    pr_indent = 0;
    pr_newline = 0;
    disable_pr_tkn = 1;
}


void exit_utils(void) {
    //printf("exit_utils\n");
    printf("allocation check...\n");
    printf("    allocation cnt: %d, free cnt: %d\n", alloc_cnt, free_cnt);
}

