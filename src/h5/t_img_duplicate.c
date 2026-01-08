/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_img_duplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:43:39 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/06 02:14:25 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	copy_t_img_metadata(t_img *src, t_img *dst)
{
	dst->endian = src->endian;
	dst->size_line = src->size_line;
	dst->bpp = src->bpp;
	dst->height = src->height;
	dst->width = src->width;
}

int	dup_t_img_by_words(t_img *src, t_img *dst)
{
	size_t	length;

	if (!is_img_valid(src) || !is_img_valid(dst))
		return (0);
	copy_t_img_metadata(src, dst);
	length = (size_t)(src->size_line * src->height);
	ft_memcpy_by_words(dst->addr, src->addr, length);
	return (1);
}
