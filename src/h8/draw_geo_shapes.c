/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_geo_shapes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:33 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 04:34:31 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * NOTE: NON-OPTI-VERSION this version is cleaner but not optimized for speed.
 */
void	draw_dda_line(t_ima *img, t_fpos a_pos, t_fpos b_pos, int color)
{
	t_ipos	delta;
	int		nb_step;
	t_fpos	step;

	delta = ipos_new(b_pos.x - a_pos.x, b_pos.y - a_pos.y);
	nb_step = ft_imax(abs(delta.x), abs(delta.y));
	step = fpos_new((float)delta.x / nb_step, (float)delta.y / nb_step);
	while (nb_step-- >= 0)
	{
		img->put_pix_to_img(img, round(a_pos.x), round(a_pos.y), color);
		fpos_add(&a_pos, &step);
	}
}

/**
 * OPTI: this version is optimized for speed but less readable.
 */
void	draw_dda_line_opti(t_ima *img, t_fpos a_pos, t_fpos b_pos, int color)
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
 * NOTE: ce->center, co->color, r->radius, ip->int_pos, fp->float_pos
 */
void	draw_circle(t_ima *img, t_fpos ce, int r, int co)
{
	t_ipos	ip;
	int		d;
	t_fpos	fp;
	int		x;

	ip = ipos_new(0, r);
	d = 1 - r;
	fp = fpos_new(-1, -1);
	while (ip.x <= ip.y)
	{
		x = ce.x - ip.x;
		draw_hline(img, x, fpos_set(&fp, ce.x + ip.x, ce.y + ip.y), co);
		draw_hline(img, x, fpos_set(&fp, ce.x + ip.x, ce.y - ip.y), co);
		x = ce.x - ip.y;
		draw_hline(img, x, fpos_set(&fp, ce.x + ip.y, ce.y + ip.x), co);
		draw_hline(img, x, fpos_set(&fp, ce.x + ip.y, ce.y - ip.x), co);
		if (d < 0)
			d += 2 * ip.x + 3;
		else
		{
			d += 2 * (ip.x - ip.y) + 5;
			ip.y--;
		}
		ip.x++;
	}
}

/**
 * NOTE: NON-OPTI-VERSION using t_fpos cleaner but less optimized for speed
 */
void	draw_vector(t_ima *img, t_fpos origin, t_fpos angle_speed, int color)
{
	t_fpos	end;
	t_fpos	left;
	t_fpos	right;
	t_fpos	angle;

	end = fpos_new(origin.x + cosf(radian(angle_speed.x)) * angle_speed.y, \
		origin.y - sinf(radian(angle_speed.x)) * angle_speed.y);
	angle = fpos_new(norm_angle(180.0 + angle_speed.x - 45.0), \
		norm_angle(180.0 + angle_speed.x + 45.0));
	left = fpos_new(end.x + cosf(radian(angle.x)) * angle_speed.y / 2, \
		end.y - sinf(radian(angle.x)) * angle_speed.y / 2);
	right = fpos_new(end.x + cosf(radian(angle.y)) * angle_speed.y / 2, \
		end.y - sinf(radian(angle.y)) * angle_speed.y / 2);
	draw_dda_line(img, origin, end, color);
	draw_dda_line(img, end, left, color);
	draw_dda_line(img, end, right, color);
}

/**
 * OPTI:  without using t_fpos utils functions. --> more optimized.
 */
void	draw_vector_opti(t_ima *img, t_fpos c, t_fpos ang, int color)
{
	t_fpos	end;
	t_fpos	left;
	t_fpos	right;
	float	angle_left;
	float	angle_right;

	end = fpos_new(c.x + cosf(radian(ang.x)) * ang.y, \
		c.y - sinf(radian(ang.x)) * ang.y);
	angle_left = norm_angle(180.0 + ang.x - 45.0);
	left = fpos_new(end.x + cosf(radian(angle_left)) * ang.y / 2, \
		end.y - sinf(radian(angle_left)) * ang.y / 2);
	angle_right = norm_angle(180.0 + ang.x + 45.0);
	right = fpos_new(end.x + cosf(radian(angle_right)) * ang.y / 2, \
		end.y - sinf(radian(angle_right)) * ang.y / 2);
	draw_dda_line_opti(img, c, end, color);
	draw_dda_line_opti(img, end, left, color);
	draw_dda_line_opti(img, end, right, color);
}
