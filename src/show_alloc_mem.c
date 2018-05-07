/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschnapp <aschnapp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 18:52:41 by aschnapp          #+#    #+#             */
/*   Updated: 2018/05/06 19:54:46 by aschnapp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*find_next_block(t_heap *heap, t_block *prev)
{
	t_block	*ptr;
	t_block	*lowest;

	lowest = (t_block *)(~((uintptr_t)NULL));
	ptr = heap->head;
	while (ptr)
	{
		if (lowest > ptr && ptr > prev)
			lowest = ptr;
		ptr = ptr->next;
	}
	IFRET((uintptr_t)lowest == ~((uintptr_t)NULL), NULL);
	return (lowest);
}

t_heap	*traverse_heaps_at_size(t_heap *heap, t_heap *prev)
{
	t_heap	*ptr;
	t_heap	*lowest;

	lowest = (t_heap *)(~((uintptr_t)NULL));
	ptr = heap;
	while (ptr)
	{
		if (lowest > ptr && ptr > prev)
			lowest = ptr;
		ptr = ptr->next;
	}
	IFRET((uintptr_t)lowest == ~((uintptr_t)NULL), NULL);
	return (lowest);
}

t_heap	*find_next_heap(t_heap *prev)
{
	uintptr_t	heads[3];
	int			i;
	uintptr_t	ptr;

	ptr = ~((uintptr_t)NULL);
	heads[0] = (uintptr_t)(traverse_heaps_at_size(g_head.s, prev));
	heads[1] = (uintptr_t)traverse_heaps_at_size(g_head.m, prev);
	heads[2] = (uintptr_t)traverse_heaps_at_size(g_head.l, prev);
	i = 0;
	while (i < 3)
	{
		if (!heads[i])
		{
			i++;
			continue;
		}
		if (ptr == ~((uintptr_t)NULL))
			ptr = heads[i];
		if (heads[i] < ptr)
			ptr = heads[i];
		i++;
	}
	IFRET(ptr == ~((uintptr_t)NULL), NULL);
	return ((t_heap *)ptr);
}

void	find_size_print_heap(t_heap *heap, t_block *block)
{
	int size;

	size = block->size < 0 ? block->size * -1 : block->size;
	if (size < (int)g_head.s_size)
		write(1, "Small : ", 8);
	else if (size < (int)g_head.m_size)
		write(1, "Medium : ", 9);
	else
		write(1, "Large : ", 8);
	ft_putnbr_hex((uintptr_t)heap);
	write(1, "\n", 1);
}

void	show_alloc_mem(void)
{
	t_heap	*to_print;
	t_block	*block_to_print;

	to_print = NULL;
	block_to_print = NULL;
	to_print = find_next_heap(to_print);
	while ((uintptr_t)to_print)
	{
		block_to_print = find_next_block(to_print, block_to_print);
		if (!block_to_print)
			break ;
		find_size_print_heap(to_print, block_to_print);
		while (block_to_print)
		{
			ft_putnbr_hex((uintptr_t)(block_to_print + 1));
			write(1, " - ", 3);
			ft_putnbr_hex((uintptr_t)(block_to_print + 1)
				+ block_to_print->size);
			write(1, " : ", 3);
			ft_putnbr(block_to_print->size);
			write(1, "\n", 1);
			block_to_print = find_next_block(to_print, block_to_print);
		}
		to_print = find_next_heap(to_print);
	}
}
