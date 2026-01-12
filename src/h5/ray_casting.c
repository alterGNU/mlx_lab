/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:47:06 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/12 09:45:11 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	h_collision_detected(t_maze maze, float fx, float fy, float angle)
{
	int	x;
	int	y;
	int	index;

	x = (int)floorf(fx);
	y = (int)floorf(fy);
	index = y * maze.width + x;
	printf(" from (%.2f, %.2f) check if maze[%d][%d]-->", fx, fy, x, y);
	if (angle < 180.0f && y <= 0)
		return (printf(" COLLISION:MAZE-NORT-LIMIT\n"), -1);
	if (angle > 180.0f && y + 1 >= maze.height)
		return (printf(" COLLISION:MAZE-SOUTH-LIMIT\n"), -1);
	if (maze.mat[index] == 1)
		return (printf(" COLLISION WALL maze[%d]\n", index), 1);
	return (printf("NO-maze[%d]\n", index), 0);
}

static t_pos	h_found_hit_dda(t_maze maze, t_pos start_pos, t_hit hit)
{
	float	rx;
	float	ry;
	float	sx;
	float	sy;
	float	atan;
	int		steps; // loop counter to avoid infinite loop
	int		res_check;

	steps = 0;
	if (hit.angle == 0.0f)
	{
		printf(" Facing HORIZONTAL-EAST\n");
		ry = start_pos.y;
		rx = (float)maze.width;
	}
	else if (hit.angle == 180.0f)
	{
		printf(" Facing HORIZONTAL-WEST\n");
		ry = start_pos.y;
		rx = 0.f;
	}
	else if (hit.angle < 180.0f)
	{
		atan = 1 / tanf(radian(hit.angle));
		printf(" Facing UP\n");
		if (h_collision_detected(maze, start_pos.x, start_pos.y, hit.angle))
		{
			ry = floorf(start_pos.y);
			rx = start_pos.x + (start_pos.y - ry) * atan;
			return (init_pos(rx, ry));
		}
		ry = floorf(start_pos.y) - 0.0001f;
		rx = start_pos.x + (start_pos.y - ry) * atan;
		sy = -1.f;
		sx = -sy * atan;
		steps = maze.width + maze.height;
	}
	else if (hit.angle > 180.0f)
	{
		atan = 1 / tanf(radian(hit.angle));
		printf(" Facing DOWN\n");
		if (h_collision_detected(maze, start_pos.x, start_pos.y, hit.angle))
		{
			ry = ceilf(start_pos.y);
			rx = start_pos.x + (start_pos.y - ry) * atan;
			return (init_pos(rx, ry));
		}
		ry = ceilf(start_pos.y) + 0.0001f;
		rx = start_pos.x + (start_pos.y - ry) * atan;
		sy = 1.f;
		sx = -sy * atan;
		steps = maze.height + maze.width;
	}
	while (steps-- > 0)
	{
		printf(" DDA LOOP at (%.2f, %.2f)--->\n", rx, ry);
		res_check = h_collision_detected(maze, rx, ry, hit.angle);
		if (res_check == 1)
			steps = 0;
		else if (res_check == -1)
		{
			ry += sy;
			rx += sx;
			steps = 0;
		}
		else
		{
			ry += sy;
			rx += sx;
		}
	}
	return (init_pos(rx, ry));
}

static int	v_collision_detected(t_maze maze, float fx, float fy, float angle)
{
	int	x;
	int	y;
	int	index;

	x = (int)floorf(fx);
	y = (int)floorf(fy);
	index = y * maze.width + x;
	printf(" from (%.2f, %.2f) check if maze[%d][%d]-->", fx, fy, x, y);
	if (x == maze.width && (angle < 90.0f || angle > 270.0f))
		return (printf(" COLLISION:MAZE-EAST-LIMIT\n"), -1);
	if (x < 0 && 90.0f < angle && angle < 270.0f)
		return (printf(" COLLISION:MAZE-WEST-LIMIT\n"), -1);
	if (maze.mat[index] == 1)
		return (printf(" COLLISION WALL maze[%d]\n", index), 1);
	return (printf("NO-maze[%d]\n", index), 0);
}

static t_pos	v_found_hit_dda(t_maze maze, t_pos start_pos, t_hit hit)
{
	float	rx;
	float	ry;
	float	sx;
	float	sy;
	float	ntan;
	int		steps; // loop counter to avoid infinite loop
	int		res_check;

	steps = 0;
	if (hit.angle == 90.0f)
	{
		printf(" Facing VERTICAL-NORTH\n");
		ry = start_pos.y;
		rx = 0.f;
	}
	else if (hit.angle == 270.0f)
	{
		printf(" Facing VERTICAL-SOUTH\n");
		ry = start_pos.y;
		rx = (float)maze.width;
	}
	else if (hit.angle < 90.0f || hit.angle > 270.0f)
	{
		ntan = tanf(radian(hit.angle));
		printf(" Facing RIGHT\n");
		if (v_collision_detected(maze, start_pos.x, start_pos.y, hit.angle))
		{
			rx = ceilf(start_pos.x);
			ry = start_pos.y + (start_pos.x - rx) * ntan;
			return (init_pos(rx, ry));
		}
		rx = ceilf(start_pos.x) + 0.0001f;
		ry = start_pos.y + (start_pos.x - rx) * ntan;
		sx = 1.f;
		sy = -sx * ntan;
		steps = maze.width + maze.height;
	}
	else if (90 < hit.angle && hit.angle < 270.0f)
	{
		ntan = tanf(radian(hit.angle));
		printf(" Facing LEFT\n");
		if (v_collision_detected(maze, start_pos.x, start_pos.y, hit.angle))
		{
			rx = floorf(start_pos.x);
			ry = start_pos.y + (start_pos.x - rx) * ntan;
			return (init_pos(rx, ry));
		}
		rx = floorf(start_pos.x) - 0.0001f;
		ry = start_pos.y + (start_pos.x - rx) * ntan;
		sx = -1.f;
		sy = -sx * ntan;
		steps = maze.height + maze.width;
	}
	while (steps-- > 0)
	{
		printf(" DDA LOOP at (%.2f, %.2f)--->\n", rx, ry);
		res_check = v_collision_detected(maze, rx, ry, hit.angle);
		if (res_check == 1)
			steps = 0;
		else if (res_check == -1)
		{
			rx += 0.0001f;
			ry += 0.0001f;
			steps = 0;
		}
		else
		{
			rx += sx;
			ry += sy;
		}
	}
	return (init_pos(rx, ry));
}

t_pos	found_hit_dda(t_maze maze, t_pos start_pos, t_hit hit)
{
	t_pos	hit_h;
	t_pos	hit_v;
	float	dist_h;
	float	dist_v;

	hit_h = h_found_hit_dda(maze, start_pos, hit);
	hit_v = v_found_hit_dda(maze, start_pos, hit);
	dist_h = tpos_dist(start_pos, hit_h);
	dist_v = tpos_dist(start_pos, hit_v);
	if (dist_h < dist_v)
		return (hit_h);
	return (hit_v);
}

void	update_hit_tpos(t_data *dt)
{
	int		i;
	float	angle_start;
	float	x_hit;
	float	y_hit;
	float	rot_elem;

	if (dt->nb_of_rays <= 1)
	{
		dt->hits[0].angle = dt->player.dir;
		x_hit = dt->player.pos.x + cosf(radian(dt->player.dir)) * dt->big_ben;
		y_hit = dt->player.pos.y - sinf(radian(dt->player.dir)) * dt->big_ben;
		dt->hits[0] = set_hit(&dt->hits[0], x_hit, y_hit, dt->player.dir);
		dt->hits[0].pos = found_hit_dda(dt->maze, dt->player.pos, dt->hits[0]);
	}
	else
	{
		rot_elem = FOV * FOV_PRE / (FOV - FOV_PRE);
		angle_start = norm_angle(dt->player.dir - (FOV / 2.0f));
		i = -1;
		while (dt->hits[++i].valid)
		{
			dt->hits[i].angle = norm_angle(angle_start + i * rot_elem);
			x_hit = dt->player.pos.x + cosf(radian(dt->hits[i].angle)) * dt->big_ben;
			y_hit = dt->player.pos.y - sinf(radian(dt->hits[i].angle)) * dt->big_ben;
			dt->hits[i] = set_hit(&dt->hits[i], x_hit, y_hit, dt->hits[i].angle);
			dt->hits[i].pos = found_hit_dda(dt->maze, dt->player.pos, dt->hits[i]);
		}
	}
}
