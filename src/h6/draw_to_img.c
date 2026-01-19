/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_to_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:33 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/19 19:38:25 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * TODO-LIST: reorganise, optimize and factorize pixel writing functions.
 * -[] rewrite put_pixel_to_image using t_ipos() instead of x,y.
 * -[] use optimized put_pixel_to_image() fun. in other drawing functions.
 *
 * NOT-OPTI: endianness only need to check it once on start (init img load).
 *    --> Found a way to switch between fun. using little/big endian easily.
 */

/**
 * FIX-ME: To many args, need to use t_ipos struct. and its utils fun.
 * TODO: t and utils fun, calls put_pixel_to_image() fun.
 * NOT-OPTI: bounds checking for each pixel, check-if need to.
 */
void	draw_vline(t_img *img, int x, int start_y, int stop_y, int color)
{
	char	*pixel;
	int		tmp;

	if (x < 0 || x >= img->width)
		return ;
	if (start_y > stop_y)
	{
		tmp = start_y;
		start_y = stop_y;
		stop_y = tmp;
	}
	if (stop_y < 0 || start_y >= img->height)
		return ;
	if (start_y < 0)
		start_y = 0;
	if (stop_y >= img->height)
		stop_y = img->height - 1;
	pixel = img->addr + (start_y * img->size_line + x * (img->bpp / 8));
	while (start_y++ <= stop_y)
	{
		*(int *)pixel = color;
		pixel += img->size_line;
	}
}

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
 * TODO: rewrite using t_fpos utils functions. 
 *  -> ipos_add(center,)
 */
void	draw_circle(t_img *img, t_fpos center, int r, int color)
{
	int		x;
	int		y;
	int		d;
	t_fpos	tp;

	x = 0;
	y = r;
	d = 1 - r;
	tp = fpos_new(-1, -1);
	while (x <= y)
	{
		draw_hline(img, center.x - x, \
			fpos_set(&tp, center.x + x, center.y + y), color);
		draw_hline(img, center.x - x, \
			fpos_set(&tp, center.x + x, center.y - y), color);
		draw_hline(img, center.x - y, \
			fpos_set(&tp, center.x + y, center.y + x), color);
		draw_hline(img, center.x - y, \
			fpos_set(&tp, center.x + y, center.y - x), color);
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

/**
 * TODO: rewrite using t_fpos utils functions. 
 *  ->(fpos_to_ipos_ceil(), fpos_to_ipos_floor(), fpos_to_ipos_round().)
 */
void	draw_dda_line(t_img *img, t_fpos a_pos, t_fpos b_pos, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	sx;
	float	sy;

	dx = b_pos.x - a_pos.x;
	dy = b_pos.y - a_pos.y;
	steps = ft_imax(abs(dx), abs(dy));
	sx = (float)dx / steps;
	sy = (float)dy / steps;
	while (steps-- >= 0)
	{
		img->put_pix_to_img(img, round(a_pos.x), round(a_pos.y), color);
		a_pos.x += sx;
		a_pos.y += sy;
	}
}

/**
 * TODO: rewrite using t_fpos utils functions.
 */
void	draw_vector(t_img *img, t_fpos origin, t_fpos angle_speed, int color)
{
	t_fpos	end;
	t_fpos	left;
	t_fpos	right;
	float	angle_left;
	float	angle_right;

	end = fpos_new(origin.x + cosf(radian(angle_speed.x)) * angle_speed.y, \
		origin.y - sinf(radian(angle_speed.x)) * angle_speed.y);
	angle_left = norm_angle(180.0 + angle_speed.x - 45.0);
	left = fpos_new(end.x + cosf(radian(angle_left)) * angle_speed.y / 2, \
		end.y - sinf(radian(angle_left)) * angle_speed.y / 2);
	angle_right = norm_angle(180.0 + angle_speed.x + 45.0);
	right = fpos_new(end.x + cosf(radian(angle_right)) * angle_speed.y / 2, \
		end.y - sinf(radian(angle_right)) * angle_speed.y / 2);
	draw_dda_line(img, origin, end, color);
	draw_dda_line(img, end, left, color);
	draw_dda_line(img, end, right, color);
}
