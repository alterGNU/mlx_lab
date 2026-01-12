/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_coll_hori.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:47:06 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/12 13:57:13 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_pos	h_found_hit_dda(t_data dt, t_pos start_pos, t_hit hit)
{
	float	rx;
	float	ry;
	float	sx;
	float	sy;
	float	atan;
	int		steps; // loop counter to avoid infinite loop

	if (hit.angle == 0.0f)
	{
		printf(" Facing HORIZONTAL-EAST\n");
		return (init_pos(start_pos.x + dt.maze.width, start_pos.y));
	}
	if (hit.angle == 180.0f)
	{
		printf(" Facing HORIZONTAL-WEST\n");
		return (init_pos(start_pos.x - dt.maze.width, start_pos.y));
		ry = start_pos.y;
		rx = dt.maze.width;
	}
	if (hit.angle < 180.0f)
	{
		atan = 1 / tanf(radian(hit.angle));
		printf(" Facing UP\n");
		if (collision_detected(dt.maze, start_pos.x, start_pos.y, hit.angle))
		{
			ry = floorf(start_pos.y);
			rx = start_pos.x + (start_pos.y - ry) * atan;
			return (init_pos(rx, ry));
		}
		ry = floorf(start_pos.y) - 0.0001f;
		rx = start_pos.x + (start_pos.y - ry) * atan;
		sy = -1.f;
		sx = -sy * atan;
		steps = dt.maze.width * dt.maze.height;
	}
	else if (hit.angle > 180.0f)
	{
		atan = 1 / tanf(radian(hit.angle));
		printf(" Facing DOWN\n");
		if (collision_detected(dt.maze, start_pos.x, start_pos.y, hit.angle))
		{
			ry = ceilf(start_pos.y);
			rx = start_pos.x + (start_pos.y - ry) * atan;
			return (init_pos(rx, ry));
		}
		ry = ceilf(start_pos.y) + 0.0001f;
		rx = start_pos.x + (start_pos.y - ry) * atan;
		sy = 1.f;
		sx = -sy * atan;
		steps = dt.maze.width * dt.maze.height;
	}
	while (steps-- > 0)
	{
		printf(" DDA LOOP at (%.2f, %.2f)--->\n", rx, ry);
		if(collision_detected(dt.maze, rx, ry, hit.angle))
			steps = 0;
		else
		{
			ry += sy;
			rx += sx;
		}
	}
	return (init_pos(rx, ry));
}
