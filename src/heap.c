/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschnapp <aschnapp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:18:37 by aschnapp          #+#    #+#             */
/*   Updated: 2018/05/06 19:58:28 by aschnapp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	unmap_heap(t_heap *heap)
{
	if ((t_heap *)(heap->next))
		((t_heap *)(heap->next))->prev = heap->prev;
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
	munmap((void *)heap, heap->size + sizeof(t_heap));
}

int		heap_init(size_t size, t_heap **heap)
{
	size_t	heap_size;
	void	*tmp;

	size += (sizeof(t_block));
	if (size > g_head.m_size)
		heap_size = (size / g_head.ps * g_head.ps < size
		? g_head.ps * (size / g_head.ps + 1) : g_head.ps * size / g_head.ps);
	else if (size > g_head.s_size && size <= g_head.m_size)
		heap_size = g_head.m_size * 100;
	else if (size <= g_head.s_size)
		heap_size = g_head.s_size * 100;
	else
		return (1);
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
	return (0);
}
