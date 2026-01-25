/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dfun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/25 05:38:02 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// OPTI: better than draw3d_obj_vlines_le32()...
void	draw3d_obj_vlines(t_ima *img, t_hit *hit, int col_width)
{
	int		i;
	int		j;

	i = 0;
	while (hit[i].valid)
	{
		j = 0;
		while (j < col_width)
			img->draw_vlines(img, i * col_width + j++, hit[i].y_inter, hit[i].type.y);
		i++;
	}
}

// NOTE: surprisingly slower than draw3d_obj_vlines()...lost ~3FPS
void	draw3d_obj_vlines_le32(t_ima *img, t_hit *hit, int col_width)
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	*pixel;

	i = 0;
	while (hit[i].valid)
	{
		j = -1;
		while (++j < col_width)
		{
			x = i * col_width + j;
			if (x < 0 || x >= img->dim.x)
				continue ;
			pixel = img->addr + (hit[i].y_inter.x * img->size_line + x * 4);
			y = hit[i].y_inter.x;
			while (y <= hit[i].y_inter.y)
			{
				*(int *)pixel = hit[i].type.y;
				pixel += img->size_line;
				y++;
			}
		}
		i++;
	}
}

void	draw3d_obj_texture(t_ima *img, t_hit *hit, int col_width)
{
	t_ipos	i;
	t_text	*txt;
	t_ipos	y_inter;
	t_fpos	txt_pix;
	int		c;

	i = ipos_new(0, 0);
	while (hit[i.x].valid)
	{
		txt = hit[i.x].texture;
		txt_pix = hit[i.x].txt_pix;
		y_inter = hit[i.x].y_inter;
		while (y_inter.x < y_inter.y)
		{
			c = txt->img[ft_imax(0, ft_imin((int)(txt_pix.y) * txt->dim.x + \
				(int)(txt_pix.x), txt->size - 1))];
			i.y = -1;
			while (++i.y < col_width)
				img->put_pix_to_img(img, i.x * col_width + i.y, y_inter.x, c);
			txt_pix.y += hit[i.x].txt_ty.x;
			y_inter.x++;
		}
		i.x++;
	}
}

void	draw3d_obj_texture_le32(t_ima *img, t_hit *hit, int col_width)
{
	t_ipos	i;
	t_text	*txt;
	t_ipos	y_inter;
	t_fpos	txt_pix;
	int		c;

	i = ipos_new(0, 0);
	while (hit[i.x].valid)
	{
		txt = hit[i.x].texture;
		txt_pix = hit[i.x].txt_pix;
		y_inter = hit[i.x].y_inter;
		while (y_inter.x < y_inter.y)
		{
			c = txt->img[ft_imax(0, ft_imin((int)(txt_pix.y) * txt->dim.x + \
				(int)(txt_pix.x), txt->size - 1))];
			i.y = -1;
			while (++i.y < col_width)
				((int *)(img->addr + y_inter.x * img->size_line))\
					[i.x * col_width + i.y] = c;
			txt_pix.y += hit[i.x].txt_ty.x;
			y_inter.x++;
		}
		i.x++;
	}
}

//void	draw3d_obj_ima_xpm(t_ima *img, t_hit *hit, int col_width)
//{
//	int		i;
//	int		j;
//	int		y;
//	t_ima	*xpm;
//	int		color;
//	int		src_x;
//	int		src_y;
//
//	i = 0;
//	while (hit[i].valid)
//	{
//		xpm = hit[i].ima_xpm;
//		y = hit[i].y_inter.x;
//		while (y < hit[i].y_inter.y)
//		{
//			src_y = ft_imax(0, ft_imin((int)hit[i].txt_pix.y, xpm->dim.y - 1));
//			src_x = ft_imax(0, ft_imin((int)hit[i].txt_pix.x, xpm->dim.x - 1));
//			color = *(int *)(xpm->addr + (src_y * xpm->size_line + src_x * 4));
//			j = 0;
//			while (j < col_width)
//				img->put_pix_to_img(img, i * col_width + j++, y, color);
//			hit[i].txt_pix.y += hit[i].txt_ty.x;
//			y++;
//		}
//		i++;
//	}
//}
void	draw3d_obj_ima_xpm(t_ima *img, t_hit *hit, int col_width)
{
	int		i;
	int		y;
	int		src_x;
	int		src_y;
	int		color;
	int		j;
	t_ima	*xpm;

	i = 0;
	while (hit[i].valid)
	{
		xpm = hit[i].ima_xpm;
		y = hit[i].y_inter.x;
		while (y < hit[i].y_inter.y)
		{
			src_y = (int)(hit[i].txt_pix.y + (float)(y - hit[i].y_inter.x) * hit[i].txt_ty.x);
			src_x = (int)(hit[i].txt_pix.x);
			src_y = ft_imax(0, ft_imin(src_y, xpm->dim.y - 1));
			src_x = ft_imax(0, ft_imin(src_x, xpm->dim.x - 1));
			color = *(int *)(xpm->addr + (src_y * xpm->size_line + src_x * 4));
			j = 0;
			while (j < col_width)
				((int *)(img->addr + y * img->size_line))[i * col_width + j++] = color;
			y++;
		}
		i++;
	}
}