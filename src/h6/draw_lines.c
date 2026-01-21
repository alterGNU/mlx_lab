/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:33 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/22 00:50:21 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Draw a horizontal line from (x, pos.y) to (pos.x, pos.y) in img with color.
 */
void	draw_hline(t_img *img, int x, t_fpos pos, int color)
{
	while (x <= pos.x)
	{
		if (x >= 0 && x < img->width && pos.y >= 0 && pos.y < img->height)
			img->put_pix_to_img(img, x, pos.y, color);
		x++;
	}
}


/**
 * Draw a vertical line at column x from y.x to y.y in img with color.
 * Generic version working for any endianness and bpp. not optimized at all.
 * NOTE: y.x == y_start, y.y == y_end
 */
void	draw_vlines_generic(t_img *img, int x, t_ipos y, int color)
{
	if (x < 0 || x >= img->width)
		return ;
	y.x = ft_imax(y.x, 0);
	y.y = ft_imin(y.y, img->height - 1);
	while (y.x <= y.y)
	{
		img->put_pix_to_img(img, x, y.x, color);
		y.x++;
	}
}

/**
 * NOTE: *(int *)pixel = color faster than the 4 setting line
 * OPTI: Specialized version for little-endian images with bpp=32 only.
 */
void	draw_vlines_little_end_32(t_img *img, int x, t_ipos y_inter, int color)
{
	char	*pixel;

	if (x < 0 || x >= img->width)
		return ;
	y_inter.x = ft_imax(y_inter.x, 0);
	y_inter.y = ft_imin(y_inter.y, img->height - 1);
	pixel = img->addr + (y_inter.x * img->size_line + x * 4);
	while (y_inter.x <= y_inter.y)
	{
		*(int *)pixel = color;
		pixel += img->size_line;
		y_inter.x++;
	}
}

/**
 * OPTI: Specialized version for big-endian images with bpp=32 only.
 */
void	draw_vlines_big_end_32(t_img *img, int x, t_ipos y_inter, int color)
{
	char	*pixel;

	if (x < 0 || x >= img->width)
		return ;
	y_inter.x = ft_imax(y_inter.x, 0);
	y_inter.y = ft_imin(y_inter.y, img->height - 1);
	pixel = img->addr + (y_inter.x * img->size_line + x * 4);
	while (y_inter.x <= y_inter.y)
	{
		pixel[0] = (color >> 24) & 0xFF;
		pixel[1] = (color >> 16) & 0xFF;
		pixel[2] = (color >> 8) & 0xFF;
		pixel[3] = (color >> 0) & 0xFF;
		pixel += img->size_line;
		y_inter.x++;
	}
}
