/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_coll_vert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:47:06 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/12 13:59:16 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_pos	v_found_hit_dda(t_data dt, t_pos start_pos, t_hit hit)
{
	float	rx;
	float	ry;
	float	sx;
	float	sy;
	float	ntan;
	int		steps; // loop counter to avoid infinite loop

	if (hit.angle == 90.0f)
		return (printf(" Facing VERTICAL-NORTH\n"), init_pos(start_pos.x, start_pos.y - dt.maze.height));
	if (hit.angle == 270.0f)
		return (printf(" Facing VERTICAL-SOUTH\n"), init_pos(start_pos.x, start_pos.y + dt.maze.height));
	ntan = tanf(radian(hit.angle));
	if (hit.angle < 90.0f || hit.angle > 270.0f)
	{
		printf(" Facing RIGHT\n");
		if (collision_detected(dt.maze, start_pos.x, start_pos.y, hit.angle))
		{
			rx = ceilf(start_pos.x);
			ry = start_pos.y + (start_pos.x - rx) * ntan;
			return (init_pos(rx, ry));
		}
		rx = ceilf(start_pos.x) + 0.0001f;
		sx = 1.f;
		steps = dt.maze.width + dt.maze.height;
	}
	else if (90 < hit.angle && hit.angle < 270.0f)
	{
		printf(" Facing LEFT\n");
		if (collision_detected(dt.maze, start_pos.x, start_pos.y, hit.angle))
		{
			rx = floorf(start_pos.x);
			ry = start_pos.y + (start_pos.x - rx) * ntan;
			return (init_pos(rx, ry));
		}
		rx = floorf(start_pos.x) - 0.0001f;
		sx = -1.f;
	}
	ry = start_pos.y + (start_pos.x - rx) * ntan;
	sy = -sx * ntan;
	steps = dt.maze.height + dt.maze.width;
	while (steps-- > 0)
	{
		printf(" DDA LOOP at (%.2f, %.2f)--->\n", rx, ry);
		if (collision_detected(dt.maze, rx, ry, hit.angle))
			steps = 0;
		else
		{
			rx += sx;
			ry += sy;
		}
	}
	return (init_pos(rx, ry));
}
