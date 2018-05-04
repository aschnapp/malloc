#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/resource.h>
# include <limits.h>
#  include <stdio.h>
# ifdef DEBUG_MODE
#  include <stdio.h>
#  define DBG(f, ...) printf("%s::%s> " f, __FILE__, __func__, ##__VA_ARGS__)
# else
#  define DBG(f, ...)
# endif
# define IFRET(x, y) if (x) return y
# define ISFREE (size) size < 0;

/*
**size < 0 free
**size > 0 allocated
*/
typedef struct  s_block
{
  int     size;
  void    *next;
  void    *prev;
  void    *heap;
}               t_block;

typedef struct  s_heap
{
  size_t  size;
  void    *next;
  void    *prev;
  t_block *head;
  t_block *free_head;
}               t_heap;

typedef struct  s_head
{
  int     ps;
  int     init;
  size_t  s_size;
  size_t  m_size;
  t_heap  *s;
  t_heap  *m;
  t_heap  *l;
}               t_head;

t_head  g_head;

t_heap  *traverse_heap(size_t size, t_heap **head);
t_heap  **find_size(size_t size);
int     block_init(size_t size, t_heap **head, t_block **avail);
void    free_block(t_block *block);
void    unmap_heap(t_heap *heap);
void    remove_block_from_list(t_block *block, int type);
int     create_add_block_to_head(t_block **head);
int     create_add_heap_to_head(size_t size, t_heap **head);
void    init_global(void);
int     init_first_block(size_t size, t_heap **heap);
int     heap_init(size_t size, t_heap **heap);
void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem(void);
void    show_all_mem_test(void);
void    remove_heap_head(t_heap **global, t_heap *heap);
void    ft_putnbr(int n);
void    ft_putnbr_hex(uintptr_t nb);

#endif
