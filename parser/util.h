
#ifndef __util_h__
#define __util_h__

void *ker_malloc(size_t size);
void ker_free(void *ptr);
char *ker_strdup(const char *s);

void init_utils(void);
void exit_utils(void);

#endif /*__util_h__*/

