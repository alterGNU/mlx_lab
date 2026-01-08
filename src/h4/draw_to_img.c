/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_to_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:33 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/08 02:59:46 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
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

void	draw_dda_line(t_img *img, t_pos a_pos, t_pos b_pos, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	sx;
	float	sy;

	dx = b_pos.x - a_pos.x;
	dy = b_pos.y - a_pos.y;
	steps = ft_max(abs(dx), abs(dy));
	sx = (float)dx / steps;
	sy = (float)dy / steps;
	while (steps-- >= 0)
	{
		put_pixel_to_image(img, round(a_pos.x), round(a_pos.y), color);
		a_pos.x += sx;
		a_pos.y += sy;
	}
}

void	draw_vector(t_img *img, t_pos origin, t_pos angle_speed, int color)
{
	t_pos	end;
	t_pos	left;
	t_pos	right;
	int		angle_left;
	int		angle_right;

	end = init_pos(origin.x + cosf(radian(angle_speed.x)) * angle_speed.y, \
		origin.y - sinf(radian(angle_speed.x)) * angle_speed.y);
	angle_left = norm_angle(180 + angle_speed.x - 45);
	left = init_pos(end.x + cosf(radian(angle_left)) * angle_speed.y / 2, \
		end.y - sinf(radian(angle_left)) * angle_speed.y / 2);
	angle_right = norm_angle(180 + angle_speed.x + 45);
	right = init_pos(end.x + cosf(radian(angle_right)) * angle_speed.y / 2, \
		end.y - sinf(radian(angle_right)) * angle_speed.y / 2);
	draw_dda_line(img, origin, end, color);
	draw_dda_line(img, end, left, color);
	draw_dda_line(img, end, right, color);
}
