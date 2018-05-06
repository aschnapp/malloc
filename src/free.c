#include "malloc.h"

int traverse_malloced_ptrs(t_heap *heap, void *ptr)
{
  t_block *curr;

  if (heap->head)
  {
    curr = heap->head;
    while(curr)
    {
      if ((void *)(curr + 1) == ptr)
        return 0;
      curr = curr->next;
    }
  }
  return 1;
}

int   check_ptr_ownership(void *ptr)
{
  IFRET(g_head.l, traverse_malloced_ptrs(g_head.l ,ptr));
  IFRET(g_head.m, traverse_malloced_ptrs(g_head.m, ptr));
  IFRET(g_head.s, traverse_malloced_ptrs(g_head.s, ptr));
  return 1;
}

void  free(void *ptr)
{
  t_block *header;

  IFRET(!ptr, );
  IFRET(check_ptr_ownership(ptr), );
  header = (t_block *)((char *)ptr - sizeof(t_block));
  IFRET(header->size != 0 && header->size != header->checksum && header->checksum != 0, );
  IFRET((!g_head.l && !g_head.l->head) || (!g_head.m && !g_head.m->head) || (!g_head.s && !g_head.s->head), );
  IFRET(!header->size, );
  if (header->size > (int)g_head.m_size)
    unmap_heap((t_heap *)header - 1);
  else
    free_block(header);
}
