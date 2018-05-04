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

t_heap **find_size(size_t size)
{
  IFRET(size <= g_head.s_size, &(g_head.s));
  IFRET(size <= g_head.m_size, &(g_head.m));
  return &(g_head.l);
}

void  *malloc(size_t size)
{
  t_heap **heap;
  t_heap *tmp;

  IFRET(size > INT_MAX || size < 0, NULL);
  if (!g_head.init)
    init_global();
  heap = find_size(size + sizeof(t_block));
  if ((*heap) == NULL || size > g_head.m_size) 
  {
    IFRET(create_add_heap_to_head(size, heap), NULL);
    return (void *)(((char *)(*heap)) + sizeof(t_heap) + sizeof(t_block));
  }
  IFRET(!(tmp = traverse_heap(size, heap)), NULL);
  return (void *)(tmp->head + 1);
}
