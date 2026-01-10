/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pos_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:04:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/10 17:22:12 by lagrondi         ###   ########.fr       */
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
	return (printf("pos(%.2f, %.2f)", pos.x, pos.y));
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
	return (sqrtf(powf(b.x - a.x, 2) + powf(b.y - a.y, 2)));
}
