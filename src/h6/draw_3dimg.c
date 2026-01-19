/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dimg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/20 00:15:25 by lagrondi         ###   ########.fr       */
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
void	draw3d_obj_vlines(t_img *img, t_hit *hit, t_play player, int col_width)
{
	int		i;
	int		j;
	float	plan_dist;
	t_ipos	y_interval;

	y_interval = ipos_new(0, 0);
	i = 0;
	while (hit[i].valid)
	{
		plan_dist = hit[i].distance * cos(radian(player.dir - hit[i].angle.x));
		y_interval.x = (img->height / 2) * (1 + DIST_MIN / plan_dist);
		y_interval.y = (img->height / 2) * (1 - DIST_MIN / plan_dist);
		j = 0;
		while (j < col_width)
		{
			img->draw_vlines(img, i * col_width + j, y_interval, RED_COLOR);
			j++;
		}
		i++;
	}
}

int	draw_buffer_3dimg(t_data *dt)
{
	if (!dup_t_img_by_words(&dt->img_3d_template, &dt->img_3d_buffer))
		return (fprintf(stderr, "Error: dup_t_img_by_words() failed\n"), 
			free_data(dt), 1);
	draw3d_obj_vlines(&dt->img_3d_buffer, dt->hits, dt->player, \
		dt->column_width);
	return (0);
}
