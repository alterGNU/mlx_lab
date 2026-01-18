/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fpos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 12:46:23 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float	fpos_dist(t_fpos a, t_fpos b)
{
	float	dx;
	float	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (sqrtf(dx * dx + dy * dy));
}

void	fpos_add(t_fpos *a, const t_fpos *b)
{
	a->x += b->x;
	a->y += b->y;
}

void	fpos_dot(t_fpos *a, const t_fpos *b)
{
	a->x *= b->x;
	a->y *= b->y;
}

void	fpos_scal(t_fpos *a, float scalar)
{
	a->x *= scalar;
	a->y *= scalar;
}
