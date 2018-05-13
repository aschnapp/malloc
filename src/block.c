/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschnapp <aschnapp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:06:29 by aschnapp          #+#    #+#             */
/*   Updated: 2018/05/12 23:33:12 by aschnapp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	init_block_values(t_block **block, t_heap **head, size_t size)
{
	(*block)->heap = *head;
	(*block)->size = (int)size;
	(*block)->checksum = (int)size;
	(*block)->next = (*head)->head;
	(*block)->prev = NULL;
	if ((*head)->head)
		(*head)->head->prev = (void *)(*block);
	(*head)->head = (*block);
}

int		init_first_block(size_t size, t_heap **heap)
{
	t_block *first_used;
	t_block *first_free;

	first_used = (t_block *)((*heap) + 1);
	first_used->size = (int)size;
	first_used->checksum = (int)size;
	first_used->heap = *heap;
	first_used->next = NULL;
	first_used->prev = NULL;
	(*heap)->head = first_used;
	if ((*heap)->size > first_used->size + sizeof(t_block) * 2)
	{
		first_free = (t_block *)
			((char *)(*heap) + sizeof(t_heap) + sizeof(t_block) + size);
		first_free->size = ((*heap)->size - size - (sizeof(t_block) * 2)) * -1;
		first_free->heap = *heap;
		(*heap)->free_head = first_free;
	}
	return (0);
}

int		block_init(size_t size, t_heap **head, t_block **avail)
{
	t_block	*free;
	char	*heap_end;

	heap_end = ((char *)((*avail)->heap) + 1)
		+ ((t_heap *)((*avail)->heap))->size;
	free = (t_block *)((char *)(*avail + 1) + size);
	IFRET((char *)(*avail + 1) + size > heap_end, 1);
	if ((char *)(free + 2) < heap_end && (*avail)->size * -1
		> (int)size + (int)sizeof(t_block) * 2)
	{
		free->size = (*avail)->size + size + sizeof(t_block);
		free->checksum = (*avail)->size + size + sizeof(t_block);
		free->next = (*head)->free_head;
		free->prev = NULL;
		free->heap = *head;
		if ((*head)->free_head)
			(*head)->free_head->prev = free;
		(*head)->free_head = free;
	}
	init_block_values(avail, head, size);
	return (0);
}

void	remove_right_block(t_block *block)
{
	remove_block_from_list(block, 0);
	block->next = NULL;
	block->prev = NULL;
}

void	free_block(t_block *block)
{
	t_block *right_block;

	remove_block_from_list(block, 1);
	if (block->size)
	{
		right_block = (t_block *)(((char *)(block + 1)) + block->size);
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
	if (((t_heap *)(block->heap))->head == NULL
	&& ((t_heap *)(block->heap))->next
	&& ((t_heap *)(block->heap)) != g_head.l)
		unmap_heap((t_heap *)(block->heap));
}
