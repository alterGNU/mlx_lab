/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fpos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 11:42:41 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * TODO-LIST: add multipls fpos utils functions:
 *  -[x] float fpos_dist(t_fpos a, t_fpos b);
 *  -[x] t_fpos fpos_dist(t_fpos *a, const t_fpos *b);
 *  -[ ] t_fpos prod_scal_fpos(t_fpos *a, const float scalar);
 *    -> t_fpos{a->x * scalar, a->y * scalar))}
 *    -> use in draw_2dimg.c fun. draw2d_hit_lines()
 *  -[ ] t_fpos dot_fpos(t_fpos *a, const t_fpos *b);
 *    -> t_fpos{a->x * b->x, a->y * b->y))}
 */

float	fpos_dist(t_fpos a, t_fpos b)
{
	float	dx;
	float	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (sqrtf(dx * dx + dy * dy));
}

t_fpos	add_fpos(t_fpos *a, const t_fpos *b)
{
	a->x += b->x;
	a->y += b->y;
	return (*a);
}
