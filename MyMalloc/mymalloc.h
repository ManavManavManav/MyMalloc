#ifndef mymalloc_h_
#define mymalloc_h_

#include <stdlib.h>
#include <stdio.h>

#define malloc(manav) mymalloc(manav, __FILE__, __LINE__)
#define free(manav) myfree(manav, __FILE__, __LINE__)

void *mymalloc(size_t size,char *f,int line);
void myfree(void *memory,char *f, int line);

#endif