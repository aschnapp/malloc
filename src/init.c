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

  size += (sizeof(t_block));
  if (size > g_head.m_size)
    heap_size = (size / g_head.ps * g_head.ps < size 
      ? g_head.ps * (size / g_head.ps + 1) 
      : g_head.ps * size / g_head.ps);
  else if (size > g_head.s_size && size <= g_head.m_size)
    heap_size = g_head.m_size * 100;
  else if (size <= g_head.s_size)
    heap_size = g_head.s_size * 100;
  else 
    return 1;
  tmp = mmap(0, heap_size, PROT_READ | PROT_WRITE,
          MAP_ANON | MAP_PRIVATE, -1, 0);
  IFRET(tmp == MAP_FAILED, 1);
  heap_size -= sizeof(t_heap);
  ((t_heap *)tmp)->size = heap_size;
  ((t_heap *)tmp)->head = NULL;
  ((t_heap *)tmp)->free_head = NULL;
  ((t_heap *)tmp)->next = NULL;
  ((t_heap *)tmp)->prev = NULL;
  *heap = (t_heap *)tmp;
  init_first_block(size - sizeof(t_block), heap);
  return 0;
}

int init_first_block(size_t size, t_heap **heap)
{
  t_block *first_used;
  t_block *first_free;

  first_used = (t_block *)((*heap) + 1);
  first_free = (t_block *)
    ((char *)(*heap) + sizeof(t_heap) + sizeof(t_block) + size);
  first_used->size = (int)size;
  first_used->heap = *heap;
  first_used->next = NULL;
  first_used->prev = NULL;
  (*heap)->head = first_used;
  first_free->size = ((*heap)->size - size - (sizeof(t_block) * 2)) * -1;
  first_free->heap = *heap;
  (*heap)->free_head = first_free;
  return 0;
}

int block_init(size_t size, t_heap **head, t_block **avail)
{
  t_block *free;
  char *heap_end;

  heap_end = ((char *)((*avail)->heap) + 1) + ((t_heap *)((*avail)->heap))->size;
  free = (t_block *)((char *)(*avail + 1) + size);
  IFRET((char *)(*avail + 1) + size > heap_end, 1);
  if ((char *)(free + 2) < heap_end && (*avail)->size * -1 > (int)size + (int)sizeof(t_block) * 2)
  {
    free->size = (*avail)->size + size + sizeof(t_block);
    free->next = (*head)->free_head;
    free->heap = *head;
    if ((*head)->free_head)
      (*head)->free_head->prev = free;
    (*head)->free_head = free;
  }
  (*avail)->heap = *head;
  (*avail)->size = (int)size;
  (*avail)->next = (*head)->head;
  (*avail)->prev = NULL;
  (*head)->head->prev = (void *)(*avail);
  (*head)->head = *avail;
  return 0;
}
