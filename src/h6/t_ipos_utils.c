/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ipos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 16:40:51 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * NOTE: args could be non-pointer since small structs, but for consistency...
 */
t_ipos	ipos_add_new(const t_ipos *a, const t_ipos *b)
{
	return (ipos_new(a->x + b->x, a->y + b->y));
}

t_ipos	ipos_dot_new(const t_ipos *a, const t_ipos *b)
{
	return (ipos_new(a->x * b->x, a->y * b->y));
}

t_ipos	ipos_scal_new(const t_ipos *a, int b)
{
	return (ipos_new(a->x * b, a->y * b));
}
