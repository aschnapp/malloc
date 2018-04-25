/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 15:38:58 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/29 15:24:23 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_block(t_block *b)
{
	if (b == NULL || b->is_free)
		return ;
	ft_put_addr(BDATA(b));
	ft_putstr(" - ");
	ft_put_addr(BDATA(b) + b->size);
	ft_putstr(" : ");
	ft_putnbr(b->size);
	ft_putstr(" octets\n");
}

void	show_page(t_page *page)
{
	t_block	*iter;

	ft_putstr("Page ");
	ft_put_addr(page);
	ft_putstr(", type ");
	if (page->type == TINY)
		ft_putstr("TINY");
	if (page->type == SMALL)
		ft_putstr("SMALL");
	if (page->type == LARGE)
		ft_putstr("LARGE");
	ft_putstr("\n");
	iter = page->first;
	while (iter != NULL)
	{
		print_block(iter);
		iter = iter->next;
	}
}

void	show_alloc_mem(void)
{
	t_page	*iter;

	iter = first_page();
	if (iter == NULL)
		ft_putstr("No allocation\n");
	while (iter != NULL)
	{
		show_page(iter);
		iter = iter->next;
	}
}
