
#ifndef __util_h__
#define __util_h__

void *ker_malloc(size_t size);
void ker_free(void *ptr);
char *ker_strdup(const char *s);

void init_utils(void);
void exit_utils(void);

void print_indent(int indent);

void line_break(void);
void indent_inc(void);
void indent_dec(void);
void print_token(const char* parse_text);
void set_pr_token(int disable);

#endif /*__util_h__*/

