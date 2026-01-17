/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fpos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/16 17:13:40 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * TODO:
 *  - t_fpos mult_scal_fpos(t_fpos *a, const float scalar);
 *    -> t_fpos{a->x * scalar, a->y * scalar))}
 *  - t_fpos dot_fpos(t_fpos *a, const t_fpos *b);
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

void	add_fpos(t_fpos *a, const t_fpos *b)
{
	a->x += b->x;
	a->y += b->y;
}
