/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fpos_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/17 18:12:43 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_fpos	init_fpos(float x, float y)
{
	t_fpos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_fpos	set_fpos(t_fpos *pos, float x, float y)
{
	if (!pos)
		return (init_fpos(-1, -1));
	pos->x = x;
	pos->y = y;
	return (*pos);
}

int	print_fpos(t_fpos pos)
{
	return (printf("(%.4f, %.4f)", pos.x, pos.y));
}

/**
 * CHECK-IF: Really useful
 */
t_fpos	dup_fpos(t_fpos src)
{
	t_fpos	dst;

	dst.x = src.x;
	dst.y = src.y;
	return (dst);
}
