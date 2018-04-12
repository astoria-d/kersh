
#include <stdio.h>
#include "parser.h"
#include "code.h"

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

    printf("%s start parser...\n", argv[0]);
    init_parser();
    ret = yyparse();
    printf("\nparse finished.\n==========================\n");
    dump_ir();
    exit_parser();
    printf("parser exit.\n");

    if (need_close) {
        fclose(yyin);
    }
    return ret;
}
    
