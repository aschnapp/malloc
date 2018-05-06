#include "malloc.h"

int traverse_malloced_ptrs(t_heap *heap, void *ptr)
{
  t_block *curr_block;
  t_heap *curr_heap;

  curr_heap = heap;
  while (curr_heap)
  {  
    if (heap->head)
    {
      curr_block = curr_heap->head;
      while(curr_block)
      {
        if ((void *)(curr_block + 1) == ptr)
          return 0;
        curr_block = curr_block->next;
      }
    }
    curr_heap = curr_heap->next;
  }
  return 1;
}

int   check_ptr_ownership(void *ptr)
{
  if (g_head.l)
    IFRET(!traverse_malloced_ptrs(g_head.l ,ptr), 0);
  if (g_head.m)
    IFRET(!traverse_malloced_ptrs(g_head.m, ptr), 0);
  if (g_head.s)
    IFRET(!traverse_malloced_ptrs(g_head.s, ptr), 0);
  return 1;
}

void  free(void *ptr)
{
  t_block *header;

  IFRET(!ptr, );
  IFRET(check_ptr_ownership(ptr), );
  header = (t_block *)((char *)ptr - sizeof(t_block));
  IFRET(header->size != 0 && header->size != header->checksum && header->checksum != 0, );
  IFRET(!header->size, );
  if (header->size > (int)g_head.m_size)
    unmap_heap((t_heap *)header - 1);
  else
    free_block(header);
}
