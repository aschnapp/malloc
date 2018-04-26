#include "malloc.h"

void  free(void *ptr)
{
  munmap(ptr, 5);
}
