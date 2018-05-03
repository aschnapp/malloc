#include "malloc.h"

void  unmap_heap(t_heap *heap)
{
  if ((t_heap *)(heap->prev))
    ((t_heap *)(heap->prev))->next = heap->next;
  else
  {
    if (g_head.s == heap)
      g_head.s = heap->next;
    else if (g_head.m == heap)
      g_head.m = heap->next;
    else
      g_head.l = heap->next;
  } 
  if ((t_heap *)(heap->next))
    ((t_heap *)(heap->next))->prev = heap->prev;
  munmap((void *)heap, heap->size + sizeof(t_heap));
}

void  remove_right_block(t_block *block)
{
  if (block->next)
    ((t_block *)(block->next))->prev = block->prev;
  if (block->prev)
    ((t_block *)(block->prev))->next = block->next;
  else
    ((t_heap *)(block->heap))->free_head = block->next;
  block->next = NULL;
  block->prev = NULL;
}

t_block   *get_right_block(t_block *block)
{
  t_block *right_block = (t_block *)(((char *)block) + block->size + sizeof(t_block));
  (void)right_block;
  return (t_block *)(((char *)block) + block->size + sizeof(t_block));

}

void  free_block(t_block *block)
{
  t_block *right_block;

  if  (block->next)
    ((t_block *)(block->next))->prev = block->prev;
  if (block->prev)
    ((t_block *)(block->prev))->next = block->next;
  else
    ((t_heap *)(block->heap))->head = block->next;
  if (block->size)
  {
    right_block = get_right_block(block);
    block->size *= -1;
    if (right_block->size < 0)
    {
      block->size += right_block->size - sizeof(t_block);
      remove_right_block(right_block);
    }
  }
  block->next = ((t_heap *)(block->heap))->free_head;
  if (((t_heap *)(block->heap))->free_head)
    ((t_heap *)(block->heap))->free_head->prev = block;
  block->prev = NULL;
  ((t_heap *)(block->heap))->free_head = block;
  if (((t_heap *)(block->heap))->head == NULL)
    unmap_heap((t_heap *)(block->heap));
}

void  free(void *ptr)
{
  t_block *header;

  IFRET(!ptr, );
  header = (t_block *)((char *)ptr - sizeof(t_block));
  if (header->size > (int)g_head.m_size)
    unmap_heap((t_heap *)header - 1);
  else
    free_block(header);
}
