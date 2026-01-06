/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_img_insertion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:04:25 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/06 00:25:38 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	t_img_insert_rows_by_bits(t_img *src, t_img *dst, int dst_x, int dst_y)
{
	int		row;
	int		bpp;
	size_t	row_bytes;
	char	*src_row;
	char	*dst_row;

	if (!dst || !src || !dst->addr || !src->addr || dst_x < 0 || dst_y < 0)
		return (printf("Invalid arguments\n"));
	if (dst_x + src->width > dst->width || dst_y + src->height > dst->height)
		return (printf("Source image exceeds destination bounds\n"));
	if (src->bpp != dst->bpp)
		return (printf("Different bpp not supported\n"));
	bpp = dst->bpp / 8;
	row_bytes = (size_t)(src->width * bpp);
	row = -1;
	while (++row < src->height)
	{
		src_row = src->addr + (row * src->size_line);
		dst_row = dst->addr + ((dst_y + row) * dst->size_line + dst_x * bpp);
		ft_memcpy(dst_row, src_row, row_bytes);
	}
	return (0);
}

/**
 * Insert src image into dst image at (dst_x, dst_y) using ft_memcpy by pixel.
 * int	mlx_xpm_cpy_src_in_dst(t_img *src, t_img *dst, int dst_x, int dst_y)
 */
int	t_img_insert_rows_by_bytes(t_img *src, t_img *dst, int dst_x, int dst_y)
{
	int		row;
	int		bpp;
	size_t	row_bytes;
	char	*src_row;
	char	*dst_row;

	if (!dst || !src || !dst->addr || !src->addr || dst_x < 0 || dst_y < 0)
		return (printf("Invalid arguments\n"));
	if (dst_x + src->width > dst->width || dst_y + src->height > dst->height)
		return (printf("Source image exceeds destination bounds\n"));
	if (src->bpp != dst->bpp)
		return (printf("Different bpp not supported\n"));
	bpp = dst->bpp / 8;
	row_bytes = (size_t)(src->width * bpp);
	row = -1;
	while (++row < src->height)
	{
		src_row = src->addr + (row * src->size_line);
		dst_row = dst->addr + ((dst_y + row) * dst->size_line + dst_x * bpp);
		ft_memcpy_by_bytes(dst_row, src_row, row_bytes);
	}
	return (0);
}

/**
 * Insert src image into dst image at (dst_x, dst_y) using ft_memcpy by words.
 */
int	t_img_insert_rows_by_words(t_img *src, t_img *dst, int dst_x, int dst_y)
{
	int		row;
	int		bpp;
	size_t	row_bytes;
	char	*src_row;
	char	*dst_row;

	if (!dst || !src || !dst->addr || !src->addr || dst_x < 0 || dst_y < 0)
		return (printf("Invalid arguments\n"));
	if (dst_x + src->width > dst->width || dst_y + src->height > dst->height)
		return (printf("Source image exceeds destination bounds\n"));
	if (src->bpp != dst->bpp)
		return (printf("Different bpp not supported\n"));
	bpp = dst->bpp / 8;
	row_bytes = (size_t)(src->width * bpp);
	row = -1;
	while (++row < src->height)
	{
		src_row = src->addr + (row * src->size_line);
		dst_row = dst->addr + ((dst_y + row) * dst->size_line + dst_x * bpp);
		ft_memcpy_by_words(dst_row, src_row, row_bytes);
	}
	return (0);
}

/**
 * Insert src image into dst image at (dst_x, dst_y) using standard memcpy.
 */
int	t_img_insert_rows_with_memcpy(t_img *src, t_img *dst, int dst_x, int dst_y)
{
	int		row;
	int		bpp;
	size_t	row_bytes;
	char	*src_row;
	char	*dst_row;

	if (!dst || !src || !dst->addr || !src->addr || dst_x < 0 || dst_y < 0)
		return (printf("Invalid arguments\n"));
	if (dst_x + src->width > dst->width || dst_y + src->height > dst->height)
		return (printf("Source image exceeds destination bounds\n"));
	if (src->bpp != dst->bpp)
		return (printf("Different bpp not supported\n"));
	bpp = dst->bpp / 8;
	row_bytes = (size_t)(src->width * bpp);
	row = -1;
	while (++row < src->height)
	{
		src_row = src->addr + (row * src->size_line);
		dst_row = dst->addr + ((dst_y + row) * dst->size_line + dst_x * bpp);
		memcpy(dst_row, src_row, row_bytes);
	}
	return (0);
}
