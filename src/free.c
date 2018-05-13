/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschnapp <aschnapp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:09:52 by aschnapp          #+#    #+#             */
/*   Updated: 2018/05/13 15:15:05 by aschnapp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		traverse_malloced_ptrs(t_heap *heap, void *ptr)
{
	t_block	*curr_block;
	t_heap	*curr_heap;

	curr_heap = heap;
	while (curr_heap)
	{
		if (curr_heap->head)
		{
			curr_block = curr_heap->head;
			while (curr_block)
			{
				if (curr_block->checksum != curr_block->size)
					break ;
				if ((void *)(curr_block + 1) == ptr)
					return (0);
				curr_block = curr_block->next;
			}
		}
		curr_heap = curr_heap->next;
	}
	return (1);
}

int		check_ptr_ownership(void *ptr)
{
	t_block *header;

	header = (t_block *)ptr - 1;
	if (g_head.l)
		IFRET(!traverse_malloced_ptrs(g_head.l, ptr), 0);
	if (g_head.m)
		IFRET(!traverse_malloced_ptrs(g_head.m, ptr), 0);
	if (g_head.s)
		IFRET(!traverse_malloced_ptrs(g_head.s, ptr), 0);
	return (1);
}

void	free(void *ptr)
{
	t_block *header;

	if (!ptr)
		return ;
	header = (t_block *)ptr - 1;
	if (check_ptr_ownership(ptr))
		return ;
	if ((header->size == 0) || (header->size
		!= header->checksum) || (header->checksum == 0))
		return ;
	if (header->size > (int)g_head.m_size)
		unmap_heap((t_heap *)header - 1);
	else
		free_block(header);
}
