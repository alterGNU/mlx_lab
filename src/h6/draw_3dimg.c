/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dimg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/20 04:45:11 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Draws vertical lines representing 3D objects based on raycasting hits.
 * - Do not draw floor vertical lines [0 to y_start[
 * + Draw (only) the vertical lines of the objects [y_start to y_stop]
 * - Do not draw ceiling vertical lines [y_stop to img_3d_buffer.height[
 * NOT-OPTI: some of the calculations could be optimized outside the loop.
 */
void	draw3d_obj_vlines(t_img *img, t_hit *hit, int col_width)
{
	int		i;
	int		j;
	t_ipos	y_interval;

	y_interval = ipos_new(0, 0);
	i = 0;
	while (hit[i].valid)
	{
		y_interval.x = (img->height / 2) * (1 + hit[i].dim.y / hit[i].dist_corr);
		y_interval.y = (img->height / 2) * (1 - hit[i].dim.y / hit[i].dist_corr);
		j = 0;
		while (j < col_width)
		{
			img->draw_vlines(img, i * col_width + j, y_interval, hit[i].type.y);
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
	draw3d_obj_vlines(&dt->img_3d_buffer, dt->hits, dt->column_width);
	return (0);
}
