/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hit_fun_drawtxtlines.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:33 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/26 06:48:52 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// NOTE: txt_ty.y == offset == i.x * col_width
void	draw_txt_vlines_gen(t_ima *img, t_ima *txt, t_hit *hit, int col_width)
{
	t_ipos	y_inter;
	t_fpos	txt_pix;
	int		c;
	int		j;
	int		dst_x;

	txt_pix = hit->txt_pix;
	y_inter = hit->y_inter;
	dst_x = hit->txt_ty.y;
	while (y_inter.x < y_inter.y)
	{
		c = *(int *)(txt->addr + (int)(txt_pix.y) * txt->size_line + \
			(int)(txt_pix.x) * (txt->bpp / 8));
		j = -1;
		while (++j < col_width)
			*(int *)(img->addr + y_inter.x * img->size_line + (dst_x + j) \
				* (img->bpp / 8)) = c;
		txt_pix.y += hit->txt_ty.x;
		y_inter.x++;
	}
}

/**
 * OPTI: for 32bpp images (dst and src both 32bpp)
 */
void	draw_txt_vlines_32(t_ima *img, t_ima *txt, t_hit *hit, int col_width)
{
	t_ipos	y_inter;
	t_fpos	txt_pix;
	int		c;
	int		j;
	int		dst_x;

	txt_pix = hit->txt_pix;
	y_inter = hit->y_inter;
	dst_x = hit->txt_ty.y;
	while (y_inter.x < y_inter.y)
	{
		c = ((int *)(txt->addr + (int)(txt_pix.y) * txt->size_line))\
				[(int)(txt_pix.x)];
		j = -1;
		while (++j < col_width)
			((int *)(img->addr + y_inter.x * img->size_line))[dst_x + j] = c;
		txt_pix.y += hit->txt_ty.x;
		y_inter.x++;
	}
}
