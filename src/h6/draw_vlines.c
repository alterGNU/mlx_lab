/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vlines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:33 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/20 00:35:12 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Generic version working for any endianness and bpp. not optimized at all.
 */
void	draw_vlines_generic(t_img *img, int x, t_ipos y_inter, int color)
{
	int		tmp;

	if (x < 0 || x >= img->width)
		return ;
	if (y_inter.x > y_inter.y)
	{
		tmp = y_inter.x;
		y_inter.x = y_inter.y;
		y_inter.y = tmp;
	}
	y_inter.x = ft_imax(y_inter.x, 0);
	y_inter.y = ft_imin(y_inter.y, img->height - 1);
	while (y_inter.x <= y_inter.y)
	{
		img->put_pix_to_img(img, x, y_inter.x, color);
		y_inter.x++;
	}
}

/**
 * NOTE: *(int *)pixel = color faster than the 4 setting line
 * OPTI: Specialized version for little-endian images with bpp=32 only.
 */
void	draw_vlines_little_end_32(t_img *img, int x, t_ipos y_inter, int color)
{
	char	*pixel;
	int		tmp;

	if (x < 0 || x >= img->width)
		return ;
	if (y_inter.x > y_inter.y)
	{
		tmp = y_inter.x;
		y_inter.x = y_inter.y;
		y_inter.y = tmp;
	}
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
	int		tmp;

	if (x < 0 || x >= img->width)
		return ;
	if (y_inter.x > y_inter.y)
	{
		tmp = y_inter.x;
		y_inter.x = y_inter.y;
		y_inter.y = tmp;
	}
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
