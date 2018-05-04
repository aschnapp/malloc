#include "malloc.h"

void  free(void *ptr)
{
  t_block *header;

  IFRET(!ptr, );
  header = (t_block *)((char *)ptr - sizeof(t_block));
  IFRET(!header->size, );
  if (header->size > (int)g_head.m_size)
    unmap_heap((t_heap *)header - 1);
  else
    free_block(header);
}
