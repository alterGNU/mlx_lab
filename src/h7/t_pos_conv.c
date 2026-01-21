/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pos_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 12:44:17 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fpos_floor(t_ipos *a, const t_fpos *b)
{
	a->x = floorf(b->x);
	a->y = floorf(b->y);
}

void	fpos_ceil(t_ipos *a, const t_fpos *b)
{
	a->x = ceilf(b->x);
	a->y = ceilf(b->y);
}

void	fpos_round(t_ipos *a, const t_fpos *b)
{
	a->x = roundf(b->x);
	a->y = roundf(b->y);
}
