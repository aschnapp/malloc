#include "malloc.h"

void  *realloc(void *ptr, size_t size)
{
  (void)size;
  return ptr;
}
