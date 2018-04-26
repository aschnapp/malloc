#include "malloc.h"

int create_add_heap_to_head(t_heap **head, size_t size)
{
  t_heap *heap;
  IFRET(heap_init(size, &heap), 1);
  heap->next = *head;
  if (*head)
    (*head)->prev = heap;
  *head = heap;
  return 0;
}

int create_add_block_to_head(t_block **head)
{
  (void)head;
  return 0;
}
