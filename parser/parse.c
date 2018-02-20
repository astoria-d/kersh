
#include <stdio.h>
#include "kersh.tab.h"
#include "kersh.h"
#include "symbols.h"

static unsigned int ps_stage;
static unsigned int ps_stage_level;
static unsigned int old_token;

static unsigned int enum_index;

void init_parser(void) {
    extern int yydebug;
    extern int line_num;
    yydebug = 0;
    line_num = 1;
    ps_stage = 0;
    old_token = 0;
    ps_stage_level = 0;
}

int return_token(const char* parse_text, int token_num) {
    printf( "%s ", parse_text);
    old_token = token_num;
    if (token_num == IDEN) {
        set_last_symbol(parse_text);
    }
    else if (token_num == ENUM_CONSTANT) {
        add_enum_symbol(parse_text, enum_index++);
    }
    return token_num;
}

int check_symbol_type(void) {
    /*printf("ps_stage: %d\n", ps_stage);*/
    if (ps_stage == ENUM) {
        return ENUM_CONSTANT;
    }
    else {
        return IDEN;
    }
}

void enter_parse_stage(int stage) {
    if ((stage == STRUCT || stage == UNION) && (ps_stage == STRUCT || ps_stage == UNION)) {
        ps_stage_level++;
        return;
    }
    if (stage == ENUM) {
        enum_index = 0;
    }
    printf("stage %d entered\n", stage);
    ps_stage = stage;
}

void exit_parse_stage(void) {
    if ((ps_stage == STRUCT || ps_stage == UNION) && (ps_stage_level > 0)) {
        ps_stage_level--;
        return;
    }
    if (ps_stage != 0) printf("stage %d exited ", ps_stage);
    ps_stage = 0;
}

void line_break(void) {
    printf("\n");
    if (ps_stage == STRUCT || ps_stage == UNION) {
        int i;
        for (i = 0; i < ps_stage_level + 1; i++) {
             printf("  ");
        }
    }
}

