/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ipos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/17 02:17:52 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * TODO: remove if not used
 */
void	add_ipos(t_ipos *a, const t_ipos *b)
{
	a->x += b->x;
	a->y += b->y;
}

/**
 * TODO: remove if not used
 */
void	prod_scal_ipos(t_ipos *a, int b)
{
	a->x *= b;
	a->y *= b;
}
