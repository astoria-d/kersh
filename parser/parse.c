
#include <stdio.h>
#include "kersh.tab.h"

static unsigned int ps_stage;
static unsigned int old_token;

void init_parser(void) {
    extern int yydebug;
    extern int line_num;
    yydebug = 0;
    line_num = 1;
    ps_stage = 0;
    old_token = 0;
}

int return_token(const char* parse_text, int token_num) {
    printf( "%s ", parse_text);
    old_token = token_num;
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
    printf("stage %d entered\n", stage);
    ps_stage = stage;
}

void exit_parse_stage(void) {
    if (ps_stage != 0) printf("\nstage %d exited", ps_stage);
    ps_stage = 0;
}
