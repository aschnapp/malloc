#include "malloc.h"

void  init_global(void)
{
  g_head.ps = getpagesize();
  g_head.init = 1;
  g_head.m_size = getpagesize() * 32;
  g_head.s_size = getpagesize();
  g_head.s = NULL;
  g_head.m = NULL;
  g_head.l = NULL;
}

int  heap_init(size_t size, t_heap **heap)
{
  size_t  heap_size;
  void    *tmp;

  size += sizeof(t_heap) + sizeof(t_block);
  if (size > g_head.m_size)
    heap_size = (size / g_head.ps * g_head.ps < size 
      ? g_head.ps * (size / g_head.ps + 1) 
      : g_head.ps * size / g_head.ps);
  else if (size > g_head.s_size && size >= g_head.m_size)
    heap_size = g_head.m_size * 100;
  else if (size <= g_head.s_size)
    heap_size = g_head.s_size * 100;
  else 
    return 1;
  tmp = mmap(0, heap_size, PROT_READ | PROT_WRITE,
          MAP_ANON | MAP_PRIVATE, -1, 0);
  IFRET(tmp == MAP_FAILED, 1);
  heap_size -= (sizeof(t_heap) + sizeof(t_block));
  ((t_heap *)tmp)->size = heap_size;
  ((t_heap *)tmp)->head = NULL;
  *heap = (t_heap *)tmp;
  init_first_block(size - (sizeof(t_heap) + sizeof(t_block)), heap);
  return 0;
}

int init_first_block(size_t size, t_heap **heap)
{
  ((t_block *)((*heap) + 1))->size = (int)size;
  ((t_block *)((*heap) + 1))->next = NULL;
  ((t_block *)((*heap) + 1))->prev = NULL;
  (*heap)->head = ((t_block *)((*heap) + 1));
  return 0;
}
