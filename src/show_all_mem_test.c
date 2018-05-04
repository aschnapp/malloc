#include "malloc.h"

void traverse_block_and_print(t_block *head)
{
  while (head)
  {
    DBG("%p %d\n", head, head->size);
    head = head->next;
  }
}

void traverse_heap_and_print(t_heap *head)
{
  while(head)
  {
    DBG("heap size: %zu\n", head->size);
    DBG("Used\n");
    traverse_block_and_print(head->head);
    DBG("Free\n");
    traverse_block_and_print(head->free_head);
    head = head->next;
  }
}

void  show_all_mem_test()
{
  DBG("l\n");
  traverse_heap_and_print(g_head.l);
  DBG("m\n");
  traverse_heap_and_print(g_head.m);
  DBG("s\n");
  traverse_heap_and_print(g_head.s);
}
