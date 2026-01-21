/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fpos_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:54:50 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/21 18:46:39 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_fpos	fpos_new(float x, float y)
{
	t_fpos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

/**
 * TODO: Should be a void function?-> faster
 */
t_fpos	fpos_set(t_fpos *pos, float x, float y)
{
	if (!pos)
		return (fpos_new(-1, -1));
	pos->x = x;
	pos->y = y;
	return (*pos);
}

int	fpos_print(t_fpos pos)
{
	return (printf("(%.4f, %.4f)", pos.x, pos.y));
}

t_fpos	fpos_dup(t_fpos src)
{
	t_fpos	dst;

	dst.x = src.x;
	dst.y = src.y;
	return (dst);
}
