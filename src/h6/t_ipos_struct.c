/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ipos_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 16:41:49 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_ipos	ipos_new(int x, int y)
{
	t_ipos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

void	ipos_set(t_ipos *pos, int x, int y)
{
	if (pos)
	{
		pos->x = x;
		pos->y = y;
	}
}

int	ipos_print(t_ipos pos)
{
	return (printf("(%d, %d)", pos.x, pos.y));
}

t_ipos	ipos_dup(t_ipos src)
{
	t_ipos	dst;

	dst.x = src.x;
	dst.y = src.y;
	return (dst);
}
