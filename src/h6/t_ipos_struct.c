/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ipos_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 11:31:41 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_ipos	init_ipos(int x, int y)
{
	t_ipos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_ipos	set_ipos(t_ipos *pos, int x, int y)
{
	if (!pos)
		return (init_ipos(-1, -1));
	pos->x = x;
	pos->y = y;
	return (*pos);
}

int	print_ipos(t_ipos pos)
{
	return (printf("(%d, %d)", pos.x, pos.y));
}

/**
 * CHECK-IF: really useful...t_ipos toto = t_ipos tutu do the same?
 */
t_ipos	dup_ipos(t_ipos src)
{
	t_ipos	dst;

	dst.x = src.x;
	dst.y = src.y;
	return (dst);
}
