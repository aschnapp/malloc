#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/resource.h>
# include <limits.h>
# ifdef DEBUG_MODE
#  include <stdio.h>
#  define DBG(f, ...) printf("%s::%s> " f, __FILE__, __func__, ##__VA_ARGS__)
# else
#  define DBG(f, ...)
# endif
# define IFRET(x, y) if (x) return y
# define ISFREE (size) size < 0;
# define FINDSIZE(size, h) size <= h.s_size ? h.s : size <= h.m_size ? h.m : h.l 

/*
**size < 0 free
**size > 0 allocated
*/
typedef struct  s_block
{
  int     size;
  void   *next;
  void   *prev;
}               t_block;

typedef struct  s_heap
{
  size_t  size;
  void    *next;
  void    *prev;
  t_block *head;
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

int     create_add_block_to_head(t_block **head);
int     create_add_heap_to_head(t_heap **head, size_t size);
void    init_global(void);
int     init_first_block(size_t size, t_heap **heap);
int     heap_init(size_t size, t_heap **heap);
void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem();

#endif
