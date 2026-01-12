/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_collision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:51:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/12 15:46:11 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	collision_detected(t_maze maze, t_pos play_pos, t_pos ray_pos, float angle)
{
	int	index_play;
	int	x;
	int	y;
	int	index_ray;

	index_play = (int)floorf(play_pos.y) * maze.width + (int)floorf(play_pos.x);
	if (index_play < 0 || maze.width * maze.height <= index_play)
		return (printf("play_pos outside maze limits\n"));
	x = (int)floorf(ray_pos.x);
	y = (int)floorf(ray_pos.y);
	index_ray = y * maze.width + x;
	if (index_ray < 0 || maze.width * maze.height <= index_ray)
		return (-1);
	if (y < 0 && angle < 180.0f)
		return (-1);
	if (y == maze.height && angle > 180.0f)
		return (-1);
	if (x == maze.width && (angle < 90.0f || 270.0f < angle))
		return (-1);
	if (x < 0 && 90.0f < angle && angle < 270.0f)
		return (-1);
	if (maze.mat[index_play] != maze.mat[index_ray])
		return (1);
	return (0);
}

t_pos	h_found_hit_dda(t_data dt, t_pos play_pos, t_hit hit)
{
	t_pos	ray_pos;
	t_pos	mov_pos;
	float	atan;

	ray_pos = dup_pos(play_pos);
	if (hit.angle == 0.0f)
		return (init_pos(play_pos.x + dt.maze.width, play_pos.y));
	if (hit.angle == 180.0f)
		return (init_pos(play_pos.x - dt.maze.width, play_pos.y));
	atan = 1 / tanf(radian(hit.angle));
	if (hit.angle < 180.0f)
	{
		ray_pos.y = floorf(play_pos.y) - 0.0001f;
		mov_pos.y = -1.f;
	}
	else if (hit.angle > 180.0f)
	{
		ray_pos.y = ceilf(play_pos.y) + 0.0001f;
		mov_pos.y = 1.f;
	}
	ray_pos.x = play_pos.x + (play_pos.y - ray_pos.y) * atan;
	mov_pos.x = -mov_pos.y * atan;
	while (!collision_detected(dt.maze, play_pos, ray_pos, hit.angle))
		ray_pos = add_pos(ray_pos, mov_pos);
	return (init_pos(ray_pos.x, ray_pos.y));
}

t_pos	v_found_hit_dda(t_data dt, t_pos play_pos, t_hit hit)
{
	t_pos	ray_pos;
	t_pos	mov_pos;
	float	tan;

	ray_pos = dup_pos(play_pos);
	if (hit.angle == 90.0f)
		return (ray_pos.y = play_pos.y - dt.maze.height, ray_pos);
	if (hit.angle == 270.0f)
		return (ray_pos.y = play_pos.y + dt.maze.height, ray_pos);
	tan = tanf(radian(hit.angle));
	if (hit.angle < 90.0f || hit.angle > 270.0f)
	{
		ray_pos.x = ceilf(play_pos.x) + 0.0001f;
		mov_pos.x = 1.f;
	}
	else if (90 < hit.angle && hit.angle < 270.0f)
	{
		ray_pos.x = floorf(play_pos.x) - 0.0001f;
		mov_pos.x = -1.f;
	}
	ray_pos.y = play_pos.y + (play_pos.x - ray_pos.x) * tan;
	mov_pos.y = -mov_pos.x * tan;
	while (!collision_detected(dt.maze, play_pos, ray_pos, hit.angle))
		ray_pos = add_pos(ray_pos, mov_pos);
	return (ray_pos);
}

t_pos	found_hit_dda(t_data dt, t_pos start_pos, t_hit hit)
{
	t_pos	hit_h;
	t_pos	hit_v;
	float	dist_h;
	float	dist_v;

	hit_h = h_found_hit_dda(dt, start_pos, hit);
	hit_v = v_found_hit_dda(dt, start_pos, hit);
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
		dt->hits[0].pos = found_hit_dda(*dt, dt->player.pos, dt->hits[0]);
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
			dt->hits[i].pos = found_hit_dda(*dt, dt->player.pos, dt->hits[i]);
		}
	}
}
