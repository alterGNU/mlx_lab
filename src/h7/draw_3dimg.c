/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dimg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/22 05:58:49 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw3d_obj_vlines(t_img *img, t_hit *hit, int col_width)
{
	int		i;
	int		j;
	t_ipos	y_inter;
	float	line_height;
	float	line_offset;

	y_inter = ipos_new(0, 0);
	i = 0;
	while (hit[i].valid)
	{
		line_height = hit[i].dim.y * img->height / hit[i].dist_corr;
		if (line_height > img->height)
			line_height = img->height;
		line_offset = (img->height - line_height) / 2.0f;
		y_inter = ipos_new(line_offset, line_height + line_offset);
		y_inter.x = ft_imax(y_inter.x, 0);
		y_inter.y = ft_imin(y_inter.y, img->height - 1);
		j = 0;
		while (j < col_width)
		{
			img->draw_vlines(img, i * col_width + j, y_inter, hit[i].type.y);
			j++;
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
void	draw3d_obj_texture(t_img *img, t_hit *hit, int col_width, int *texture)
{
	int		i;
	int		j;
	t_ipos	y_inter;
	float	line_height;
	float	line_offset;
	t_ipos	img_pix;
	t_ipos	text_dim;
	t_fpos	step;
	int		index_text;
	t_fpos	txt_pix;
	float	ty_offset;

	y_inter = ipos_new(0, 0);
	text_dim = ipos_new(32, 32); // TODO: get from texture struct
	i = 0;
	while (hit[i].valid)
	{
		line_height = hit[i].dim.y * img->height / hit[i].dist_corr;
		step = fpos_new((float)text_dim.x / (float)col_width, (float)text_dim.y / line_height);
		ty_offset = 0.f;
		if (line_height > img->height)
		{
			ty_offset = (line_height - (float)img->height) / 2.f;
			line_height = img->height;
		}
		line_offset = (img->height - line_height) / 2.0f;
		y_inter = ipos_new(line_offset, line_height + line_offset);
		y_inter.x = ft_imax(y_inter.x, 0);
		y_inter.y = ft_imin(y_inter.y, img->height - 1);
		txt_pix = fpos_new(0.f, ty_offset * step.y);
		j = 0;
		while (j < col_width)
		{
			img_pix = ipos_new(i * col_width + j, y_inter.x);
			if (hit[i].type.x % 2)
			{
				txt_pix.x = (float)(hit[i].pos.x - (int)hit[i].pos.x) * (float)text_dim.x - j;
				if (hit[i].angle.x > 180.f)
					txt_pix.x = (float)text_dim.x - txt_pix.x - 1.f;
			}
			else
			{
				txt_pix.x = (float)(hit[i].pos.y - (int)hit[i].pos.y) * (float)text_dim.x - j;//NOTE: ?? text_dim.y??
				if (90.f < hit[i].angle.x && hit[i].angle.x < 270.f)
					txt_pix.x = (float)text_dim.x - txt_pix.x - 1.f;
			}
			while (img_pix.y < y_inter.y)
			{
				index_text = (int)(txt_pix.y) * text_dim.x + (int)(txt_pix.x);
				img->put_pix_to_img(img, img_pix.x, img_pix.y, texture[ft_imin(ft_imax(index_text, 0), text_dim.x * text_dim.y - 1)]);
				img_pix.y++;
				txt_pix.y += step.y;
			}
			j++;
		}
		i++;
	}
}

int	draw_buffer_3dimg(t_data *dt)
{
	t_img	img_3d_temp;

	if (dt->maze.mat[(int)dt->player.pos.y * dt->maze.width + \
		(int)dt->player.pos.x] == 0)
	{
		img_3d_temp = dt->img_3d_out_temp;
	}
	else
		img_3d_temp = dt->img_3d_ins_temp;
	if (!dup_t_img_by_words(&img_3d_temp, &dt->img_3d_buffer))
	{
		return (fprintf(stderr, "Error: dup_t_img_by_words() failed\n"), \
				free_data(dt), 1);
	}
	//draw3d_obj_vlines(&dt->img_3d_buffer, dt->hits, dt->column_width);
	draw3d_obj_texture(&dt->img_3d_buffer, dt->hits, dt->column_width, dt->check_board_texture);
	return (0);
}
