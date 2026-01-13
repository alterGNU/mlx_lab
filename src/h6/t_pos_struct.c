/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pos_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:04:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/13 16:22:09 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_pos	init_pos(float x, float y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_pos	set_pos(t_pos *pos, float x, float y)
{
	if (!pos)
		return (init_pos(-1, -1));
	pos->x = x;
	pos->y = y;
	return (*pos);
}

int	print_pos(t_pos pos)
{
	return (printf("(%.2f, %.2f)", pos.x, pos.y));
}

t_pos	dup_pos(t_pos src)
{
	t_pos	dst;

	dst.x = src.x;
	dst.y = src.y;
	return (dst);
}

float	tpos_dist(t_pos a, t_pos b)
{
	float	dx;
	float	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (sqrtf(dx * dx + dy * dy));
}

void	add_pos(t_pos *a, const t_pos *b)
{
	a->x += b->x;
	a->y += b->y;
}
