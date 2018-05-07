/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschnapp <aschnapp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:20:02 by aschnapp          #+#    #+#             */
/*   Updated: 2018/05/06 19:22:01 by aschnapp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		create_add_heap_to_head(size_t size, t_heap **head)
{
	t_heap *heap;

	IFRET(heap_init(size, &heap), 1);
	heap->next = *head;
	if (*head)
		(*head)->prev = heap;
	*head = heap;
	return (0);
}

void	remove_block_from_list(t_block *block, int type)
{
	if (block->next)
		((t_block *)(block->next))->prev = block->prev;
	if (block->prev)
		((t_block *)(block->prev))->next = block->next;
	else
	{
		if (type)
			((t_heap *)(block->heap))->head = block->next;
		else
			((t_heap *)(block->heap))->free_head = block->next;
	}
}

t_block	*find_avail_block(size_t size, t_heap *heap)
{
	t_block	*head;
	char	*heap_end;

	IFRET(!heap, NULL);
	head = heap->free_head;
	heap_end = (char *)(heap + 1) + heap->size;
	while (head != NULL)
	{
		if ((head->size * -1) >= (int)size - (int)sizeof(t_block))
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_heap	*traverse_heap(size_t size, t_heap **head)
{
	t_block	*avail_block;
	t_heap	*ptr;

	ptr = *head;
	while (!((avail_block =
	find_avail_block(size + sizeof(t_block), ptr)) && *head) && ptr)
		ptr = ptr->next;
	if (avail_block == NULL)
	{
		create_add_heap_to_head(size, head);
		return (*head);
	}
	if (((t_block *)(avail_block->prev)))
		((t_block *)(avail_block->prev))->next = avail_block->next;
	else
		(*head)->free_head = avail_block->next;
	if (((t_block *)(avail_block->next)))
		((t_block *)(avail_block->next))->prev = avail_block->prev;
	avail_block->next = NULL;
	avail_block->prev = NULL;
	block_init(size, head, &avail_block);
	return (ptr);
}
