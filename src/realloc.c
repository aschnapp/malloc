#include "malloc.h"

t_block *dup_and_free(t_block *block, size_t size, void *ptr)
{
  char *new;
  size_t i;

  i = 0;
  new = malloc(size);
  IFRET(!new, NULL);
  while((int)i < block->size)
  {
    new[i] = ((char *)ptr)[i];
    i++;
  }
  free(ptr);
  return (t_block *)(new - sizeof(t_block));
}

void  enlarge_block(t_block **block, t_block *free, size_t size)
{
  int diff;
  t_block tmp;
  t_block *new_free;

  diff = (int)size - (*block)->size;
  if (free->size * -1 >= diff)
  {
    tmp = *free;
    tmp.size = free->size + diff;
    new_free = (t_block *)((char *)free + diff);
    *new_free = tmp;
    if (new_free->next)
      ((t_block *)(new_free->next))->prev = new_free;
    if (new_free->prev)
      ((t_block *)(new_free->prev))->next = new_free;
    else
      ((t_heap *)(new_free->heap))->free_head = new_free;
  }
  else
  {
    if (free->next)
      ((t_block *)(free->next))->prev = free->prev;
    if (free->prev)
      ((t_block *)(free->prev))->next = free->next;
    else
      ((t_heap *)(free->heap))->free_head = free->next;
    free = NULL;
  }
  (*block)->size = size;
}

t_block *enlarge_or_alloc(t_block *block, size_t size, void* ptr)
{
  t_block *next_block;

  t_heap **to_heap;
  t_heap **orig_heap;

  to_heap = find_size(size);
  orig_heap = find_size(block ->size);
  next_block = (t_block *)((char *)ptr + block->size);
  if (orig_heap != to_heap)
    return dup_and_free(block, size, ptr);
  if (next_block->size < 0 && block->size - next_block->size >= (int)size)
    enlarge_block(&block, next_block, size);
  else
    return dup_and_free(block, size, ptr);
  return block;
}

void  *realloc(void *ptr, size_t size)
{
  t_block *header;

  header = ((t_block *)ptr) - 1;
  if (header->size < (int)size)
    header = enlarge_or_alloc(header, size, ptr);
  else if (header->size > (int)size)
    return ptr;
  return ptr;
}