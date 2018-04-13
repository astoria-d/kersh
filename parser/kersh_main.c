
#include <stdio.h>
#include "util.h"
#include "parser.h"
#include "code.h"
#include "utlist.h"
#include "symbol.h"

/*main func...*/
 
int main(int argc, char* argv[]) {
    int ret;
    int need_close;
    extern FILE* yyin;

    if (argc < 2) {
        yyin = stdin;
        need_close = 0;
    }
    else {
        yyin = fopen (argv[1], "r");
        need_close = 1;
    }

    if (yyin == NULL) {
        printf("failed to open input file [%s].\n", argv[1]);
        return 100;
    }

    init_utils();
    init_code();
    init_symbols();

    printf("%s start parser...\n", argv[0]);
    init_parser();
    ret = yyparse();
    printf("\nparser exit.\n");
    exit_parser();

    dump_ir();
    exit_code();
    exit_utils();

    if (need_close) {
        fclose(yyin);
    }
    return ret;
}
    
