/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_to_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:33 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/04 18:25:15 by lagrondi         ###   ########.fr       */
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

static void	draw_hline(t_img *img, int x, t_pos pos, int color)
{
	while (x <= pos.x)
	{
		if (x >= 0 && x < img->width && pos.y >= 0 && pos.y < img->height)
			put_pixel_to_image(img, x, pos.y, color);
		x++;
	}
}

void	draw_circle(t_img *img, t_pos c_pos, int r, int c)
{
	int		x;
	int		y;
	int		d;
	t_pos	tp;

	x = 0;
	y = r;
	d = 1 - r;
	tp = init_pos(-1, -1);
	while (x <= y)
	{
		draw_hline(img, c_pos.x - x, set_pos(&tp, c_pos.x + x, c_pos.y + y), c);
		draw_hline(img, c_pos.x - x, set_pos(&tp, c_pos.x + x, c_pos.y - y), c);
		draw_hline(img, c_pos.x - y, set_pos(&tp, c_pos.x + y, c_pos.y + x), c);
		draw_hline(img, c_pos.x - y, set_pos(&tp, c_pos.x + y, c_pos.y - x), c);
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
