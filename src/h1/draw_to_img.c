/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_to_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:33 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/04 12:49:31 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
	i = img->bpp - 8;
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	draw_line(t_img *img, int x1, int x2, int y, int color)
{
	while (x1 <= x2)
	{
		if (x1 >= 0 && x1 < img->width && y >= 0 && y < img->height)
			put_pixel_to_image(img, x1, y, color);
		x1++;
	}
}

void	draw_circle(t_img *img, int cx, int cy, int r, int color)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = r;
	d = 1 - r;

	while (x <= y)
	{
		draw_line(img, cx - x, cx + x, cy + y, color);
		draw_line(img, cx - x, cx + x, cy - y, color);
		draw_line(img, cx - y, cx + y, cy + x, color);
		draw_line(img, cx - y, cx + y, cy - x, color);

		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}
