/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ipos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 11:47:15 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * TODO-LIST: add ipos utils functions:
 *  -[x] t_ipos	add_ipos(t_ipos *a, const t_ipos *b)
 *  -[x] t_ipos	prod_scal_ipos(t_ipos *a, int b)
 *  -[] t_ipos fpos_floor(t_ipos *a, const t_fpos *b);
 *  -[] t_ipos fpos_ceil(t_ipos *a, const t_fpos *b);
 *  -[] t_ipos fpos_round(t_ipos *a, const t_fpos *b);
 */

t_ipos	add_ipos(t_ipos *a, const t_ipos *b)
{
	a->x += b->x;
	a->y += b->y;
	return (*a);
}

t_ipos	prod_scal_ipos(t_ipos *a, int b)
{
	a->x *= b;
	a->y *= b;
	return (*a);
}
