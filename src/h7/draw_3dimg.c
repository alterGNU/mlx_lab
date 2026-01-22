/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dimg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/22 04:25:20 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Draws vertical lines representing 3D objects based on raycasting hits.
 * - Do not draw floor vertical lines [0 to y_start[
 * + Draw (only) the vertical lines of the objects [y_start to y_stop]
 * - Do not draw ceiling vertical lines [y_stop to img_3d_buffer.height[
 * TODO-LIST:
 *  -[] move texture in hit struct as a pointer to dt->textures
 *  -[] should be able to draw object smaller that the column width
 *  -[] use object dim.x too...j should start at (col_width - obj_width)/2
 */
void	draw3d_obj_vlines(t_img *img, t_hit *hit, int col_width, int *texture)
{
	int		i;
	int		j;
	t_ipos	y_inter;
	float	line_height;
	float	line_offset;
	t_ipos	img_pix;
	//t_fpos	txt_pix;

	(void)texture;
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
			//img->draw_vlines(img, i * col_width + j, y_inter, hit[i].type.y);
			img_pix = ipos_new(i * col_width + j, y_inter.x);
			while (img_pix.y <= y_inter.y)
			{
				img->put_pix_to_img(img, img_pix.x, img_pix.y, hit[i].type.y);
				img_pix.y++;
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
	draw3d_obj_vlines(&dt->img_3d_buffer, dt->hits, dt->column_width, dt->check_board_texture);
	return (0);
}
