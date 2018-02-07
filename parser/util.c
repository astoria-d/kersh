
#include <stdio.h>
#include <string.h>


#include "kersh.tab.h"
#include "kersh.h"

int line_num;

#define LBUF_SIZE   1024
static char lex_buf[LBUF_SIZE];
static char* plex_buf;
static char* plex_buf_old;

void yyerror (char const *s) {
    print_lexbuf();
    fprintf (stderr, "%s\n", s);
}


int yywrap (void )
{
    return 1;
}

void init_values(void) {
    yydebug = 0;
    line_num = 1;

    plex_buf_old = plex_buf = lex_buf;
    reset_lex_buf();
}

void put_lex_buf(const char* token) {
    plex_buf_old = plex_buf;
    plex_buf += sprintf(plex_buf, "%s ", token);
}

void reset_lex_buf(void) {
    char oldbuf[LBUF_SIZE];
    strcpy(oldbuf, plex_buf_old);
    memset(lex_buf, 0, LBUF_SIZE);
    plex_buf_old = plex_buf = lex_buf;
    put_lex_buf(oldbuf);
}

void print_lexbuf(void) {
    char ch_old;
    ch_old = *plex_buf_old;
    *plex_buf_old = '\0';
    printf("%s\n", lex_buf);
    *plex_buf_old = ch_old;
}
