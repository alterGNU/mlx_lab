/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dimg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/16 16:30:04 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Draws vertical lines representing 3D objects based on raycasting hits.
 * - Do not draw floor vertical lines [0 to y_start[
 * + Draw (only) the vertical lines of the objects [y_start to y_stop]
 * - Do not draw ceiling vertical lines [y_stop to img_3d_buffer.height[
 * 
 */
void	draw3d_obj_vlines(t_data *dt)
{
	int		i;
	int		j;
	float	plan_dist;
	int		y_start;
	int		y_stop;

	i = 0;
	while (dt->hits[i].valid)
	{
		plan_dist = dt->hits[i].distance * \
			cos(radian(dt->player.dir - dt->hits[i].angle.x));
		y_start = (dt->img_3d_buffer.height / 2) * (1 + DIST_MIN / plan_dist);
		y_stop = (dt->img_3d_buffer.height / 2) * (1 - DIST_MIN / plan_dist);
		j = 0;
		while (j < dt->column_width)
		{
			draw_vline(&dt->img_3d_buffer, i * dt->column_width + j, \
				y_start, y_stop, RED_COLOR);
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
	draw3d_obj_vlines(dt);
	return (0);
}
