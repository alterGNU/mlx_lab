/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dfun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 04:34:31 by lagrondi         ###   ########.fr       */
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
			if (x < 0 || x >= img->width)
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

/**
 * Draws vertical lines representing 3D objects based on raycasting hits.
 * - Do not draw floor vertical lines [0 to y_start[
 * + Draw (only) the vertical lines of the objects [y_start to y_stop]
 * - Do not draw ceiling vertical lines [y_stop to img_3d_buffer.height[
 * TODO-LIST:
 *  -[] create all 3 fun. draw3d_obj_{vlines,texture,image}()
 *  -[] move texture in hit struct as a pointer to dt->textures
 *  -[] should be able to draw object smaller that the column width
 *  -[] use object dim.x too...j should start at (col_width - obj_width)/2
 * NOTE: texture need to be store in hit struct to avoid passing it as parameter
 */
void	draw3d_obj_texture(t_ima *img, t_hit *hit, int col_width)
{
	int		i;
	int		y;
	int		index_text;
	int		color;
	int		j;

	i = 0;
	while (hit[i].valid)
	{
		hit[i].img_pix = ipos_new(i * col_width, hit[i].y_inter.x);
		y = hit[i].y_inter.x;
		while (y < hit[i].y_inter.y)
		{
			index_text = (int)(hit[i].txt_pix.y + \
				(float)(y - hit[i].y_inter.x) * hit[i].txt_ty.x) * \
				hit[i].texture->dim.x + (int)(hit[i].txt_pix.x);
			color = hit[i].texture->img[ft_imax(0, ft_imin(index_text, \
				hit[i].texture->size - 1))];
			j = 0;
			while (j < col_width)
				img->put_pix_to_img(img, i * col_width + j++, y, color);
			y++;
		}
		i++;
	}
}

void	draw3d_obj_texture_le32(t_ima *img, t_hit *hit, int col_width)
{
	int		i;
	int		y;
	int		index_txt;
	int		color;
	int		j;

	i = 0;
	while (hit[i].valid)
	{
		hit[i].img_pix = ipos_new(i * col_width, hit[i].y_inter.x);
		y = hit[i].y_inter.x;
		while (y < hit[i].y_inter.y)
		{
			index_txt = (int)(hit[i].txt_pix.y + (float)(y - hit[i].y_inter.x) * hit[i].txt_ty.x) * hit[i].texture->dim.x + (int)(hit[i].txt_pix.x);
			color = hit[i].texture->img[ft_imax(0, ft_imin(index_txt, hit[i].texture->size - 1))];
			j = 0;
			while (j < col_width)
				((int *)(img->addr + y * img->size_line))[i * col_width + j++] = color;
			y++;
		}
		i++;
	}
}
