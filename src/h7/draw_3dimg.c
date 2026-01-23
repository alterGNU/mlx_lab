/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dimg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/23 02:34:20 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// TODO: adpat too
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
		line_height = hit[i].dim.y * img->height / hit[i].dist.y;
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
void	draw3d_obj_texture(t_img *img, t_hit *hit, int col_width)
{
	int		i;
	t_ipos	y_inter;
	float	line_height;
	float	line_offset;
	t_ipos	img_pix;
	float	ty_step;
	float	ty_offset;
	int		index_text;
	t_fpos	txt_pix;
	t_text	*txt;

	i = 0;
	while (hit[i].valid)
	{
		// TODO: all this part can be pre-computed in update_hit_tpos()
		// -> float line_height : use to define t_fpos y_inter
		// -> float ty_step : ty step on texture pixel column-->used to define txt_pix.y = ty_offset * ty_step
		// -> float ty_offset : ty offset on texture pixel column-->used to define txt_pix.y = ty_offset * ty_step
		// -> t_ipos y_inter : y start and y end on img where to draw the vertical line
		// -> t_fpos txt_pix : x and y pixel position on texture to sample color from
		txt = hit[i].texture;
		line_height = hit[i].dim.y * img->height / hit[i].dist.y;
		ty_step = (float)txt->dim.y / line_height;
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
		txt_pix.y = ty_offset * ty_step;
		if (hit[i].type.x % 2)
		{
			txt_pix.x = (float)(hit[i].pos.x - (int)hit[i].pos.x) * (float)txt->dim.x;
			if (hit[i].angle.x > 180.f)
				txt_pix.x = (float)txt->dim.x - txt_pix.x;
		}
		else
		{
			txt_pix.x = (float)(hit[i].pos.y - (int)hit[i].pos.y) * (float)txt->dim.x;
			if (90 < hit[i].angle.x && hit[i].angle.x < 270.f)
				txt_pix.x = (float)txt->dim.x - txt_pix.x;
		}
		// ------------------------------------------------------------------------------------------
		img_pix = ipos_new(i * col_width, y_inter.x);
		while (y_inter.x < y_inter.y)
		{
			index_text = (int)(txt_pix.y) * txt->dim.x + (int)(txt_pix.x);
			//*(int *)(img->addr + (y_inter.x * img->size_line + img_pix.x * 4)) = txt->img[ft_imax(0, ft_imin(index_text, txt->size - 1))];
			int color = txt->img[ft_imax(0, ft_imin(index_text, txt->size - 1))];
			//int *dest = (int *)(img->addr + (y_inter.x * img->size_line + img_pix.x * 4));
			int j = 0;
			while (j < col_width)
			{
				img->put_pix_to_img(img, img_pix.x + j++, y_inter.x, color);
				// put_pix with little endian 32bits --256xrays-->from FPS:7.50 to FPS:15.00 --> X2
				// --1024xrays-->from FPS:5 to FPS:7 --> +2
				// --256xrays-->from FPS:7.50 to FPS:15.00 --> X2
				//dest[j++] = color;
			}
			txt_pix.y += ty_step;
			y_inter.x++;
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
	//draw3d_obj_texture(&dt->img_3d_buffer, dt->hits, dt->column_width, dt->check_board_texture);
	draw3d_obj_texture(&dt->img_3d_buffer, dt->hits, dt->column_width);
	return (0);
}
