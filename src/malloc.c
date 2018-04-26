#include "malloc.h"

void  *malloc(size_t size)
{
  t_heap *heap;

  IFRET(size > INT_MAX || size < 0, NULL);
  if (!g_head.init)
    init_global();
  heap = FINDSIZE(size, g_head);
  if (!heap)
    IFRET(create_add_heap_to_head(&heap, size), NULL);
  DBG("%d\n", heap->head->size);
  DBG("%zu\n", heap->size);
  return NULL;
}
