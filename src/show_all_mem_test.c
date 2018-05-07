/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_all_mem_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschnapp <aschnapp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:04:58 by aschnapp          #+#    #+#             */
/*   Updated: 2018/05/06 19:05:28 by aschnapp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	traverse_block_and_print(t_block *head)
{
	while (head)
	{
		DBG("%p %d\n", head, head->size);
		head = head->next;
	}
}

void	traverse_heap_and_print(t_heap *head)
{
	while (head)
	{
		DBG("heap size: %zu\n", head->size);
		DBG("Used\n");
		traverse_block_and_print(head->head);
		DBG("Free\n");
		traverse_block_and_print(head->free_head);
		head = head->next;
	}
}

void	show_all_mem_test(void)
{
	DBG("l\n");
	traverse_heap_and_print(g_head.l);
	DBG("m\n");
	traverse_heap_and_print(g_head.m);
	DBG("s\n");
	traverse_heap_and_print(g_head.s);
}
