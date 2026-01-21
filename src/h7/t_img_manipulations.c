/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_img_manipulations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:04:25 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/17 02:45:11 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Insert src image into dst image at (dst_x, dst_y) using ft_memcpy by words.
 */
int	t_img_insert_rows_by_words(t_img *src, t_img *dst, int dst_x, int dst_y)
{
	int		row;
	int		bypp;
	size_t	row_bytes;
	char	*src_row;
	char	*dst_row;

	if (!dst || !src || !dst->addr || !src->addr || dst_x < 0 || dst_y < 0)
		return (printf("Invalid arguments\n"));
	if (dst_x + src->width > dst->width || dst_y + src->height > dst->height)
		return (printf("Source image exceeds destination bounds\n"));
	if (src->bpp != dst->bpp)
		return (printf("Different bpp not supported\n"));
	bypp = dst->bpp / 8;
	row_bytes = (size_t)(src->width * bypp);
	row = -1;
	while (++row < src->height)
	{
		src_row = src->addr + (row * src->size_line);
		dst_row = dst->addr + ((dst_y + row) * dst->size_line + dst_x * bypp);
		ft_memcpy_by_words(dst_row, src_row, row_bytes);
	}
	return (0);
}

static void	copy_t_img_metadata(t_img *src, t_img *dst)
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