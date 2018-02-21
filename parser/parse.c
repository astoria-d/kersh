
#include <stdio.h>
#include "kersh.tab.h"
#include "kersh.h"
#include "parser.h"
#include "symbols.h"

int line_num;

static unsigned int ps_stage;
static unsigned int pr_indent;
static unsigned int pr_newline;

static unsigned int enum_index;
static unsigned int const_int_val;


/*bison required functions...*/
void yyerror (char const *s) {
    fprintf (stderr, "line: %d,\n   %s\n", line_num, s);
}

int yywrap (void )
{
    return 1;
}

/*kersh implementations...*/

void init_parser(void) {
    extern int yydebug;
    yydebug = 0;
    line_num = 1;
    ps_stage = 0;
    pr_indent = 0;
    pr_newline = 0;
}

int return_token(const char* parse_text, int token_num) {
    print_token(parse_text);
    if (token_num == IDEN) {
        /*set_last_symbol(parse_text);*/
    }
    else if (token_num == ENUM_CONSTANT) {
        add_enum_symbol(parse_text, enum_index++);
    }
    else if (token_num == DECIMAL_CONSTANT) {
        sscanf(parse_text, "%d", &const_int_val);
    }
    else if (token_num == OCTAL_CONSTANT) {
        sscanf(parse_text, "%o", &const_int_val);
    }
    else if (token_num == HEX_CONSTANT) {
        sscanf(parse_text, "%x", &const_int_val);
    }
    
    return token_num;
}

int get_const_val(void) {
    return const_int_val;
}

void set_enum_index(int next_index) {
    enum_index = next_index;
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
    if (stage == ENUM) {
        enum_index = 0;
    }
    /*printf("stage %d entered\n", stage);*/
    ps_stage = stage;
}

void exit_parse_stage(void) {
    /*if (ps_stage != 0) printf("stage %d exited ", ps_stage);*/
    ps_stage = 0;
}

void line_break(void) {
    printf("\n");
    pr_newline = 1;
}

void print_token(const char* parse_text) {
    if (pr_newline) {
        int i;
        for (i = 0; i < pr_indent; i++) {
             printf("  ");
        }
    }
    pr_newline = 0;
    printf("%s ", parse_text);
}

void indent_inc(void) {
    pr_indent++;
}

void indent_dec(void) {
    pr_indent--;
}
