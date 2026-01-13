/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_collision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmouttap <lmouttap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:51:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/12 21:08:17 by lmouttap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	collision_detected(t_maze maze, t_pos play_pos, t_pos ray_pos, float angle)
{
	int	index_play;
	int	x;
	int	y;
	int	index_ray;

	// TODO:l23-25:Can be removed if wanted since player can not be outside maze
	index_play = (int)floorf(play_pos.y) * maze.width + (int)floorf(play_pos.x);
	if (index_play < 0 || maze.cell_nb <= index_play)
		return (printf("play_pos outside maze limits\n"));
	x = (int)floorf(ray_pos.x);
	y = (int)floorf(ray_pos.y);
	if (y < 0 && angle < 180.0f)
		return (-1);
	if (y == maze.height && angle > 180.0f)
		return (-1);
	if (x == maze.width && (angle < 90.0f || 270.0f < angle))
		return (-1);
	if (x < 0 && 90.0f < angle && angle < 270.0f)
		return (-1);
	index_ray = y * maze.width + x;
	if (index_ray < 0 || maze.cell_nb <= index_ray)
		return (-1);
	if (maze.mat[index_play] != maze.mat[index_ray])
		return (1);
	return (0);
}

t_pos	h_found_hit_dda(t_data dt, t_pos play_pos, t_hit hit)
{
	t_pos	ray_pos;
	t_pos	mov_pos;

	ray_pos = play_pos;
	mov_pos = init_pos(0.f, 0.f);
	if (hit.angle.x == 0.0f)
		return (init_pos(play_pos.x + dt.maze.width, play_pos.y));
	if (hit.angle.x == 180.0f)
		return (init_pos(play_pos.x - dt.maze.width, play_pos.y));
	if (hit.angle.x < 180.0f)
	{
		ray_pos.y = floorf(play_pos.y) - 0.0001f;
		mov_pos.y = -1.f;
	}
	else if (hit.angle.x > 180.0f)
	{
		ray_pos.y = ceilf(play_pos.y) + 0.0001f;
		mov_pos.y = 1.f;
	}
	ray_pos.x = play_pos.x + (play_pos.y - ray_pos.y) / hit.angle.y;
	mov_pos.x = -mov_pos.y / hit.angle.y;
	while (!collision_detected(dt.maze, play_pos, ray_pos, hit.angle.x))
		add_pos(&ray_pos, &mov_pos);
	return (ray_pos);
}

t_pos	v_found_hit_dda(t_data dt, t_pos play_pos, t_hit hit)
{
	t_pos	ray_pos;
	t_pos	mov_pos;

	ray_pos = play_pos;
	mov_pos = init_pos(0.f, 0.f);
	if (hit.angle.x == 90.0f)
		return (ray_pos.y = play_pos.y - dt.maze.height, ray_pos);
	if (hit.angle.x == 270.0f)
		return (ray_pos.y = play_pos.y + dt.maze.height, ray_pos);
	if (hit.angle.x < 90.0f || hit.angle.x > 270.0f)
	{
		ray_pos.x = ceilf(play_pos.x) + 0.0001f;
		mov_pos.x = 1.f;
	}
	else if (90 < hit.angle.x && hit.angle.x < 270.0f)
	{
		ray_pos.x = floorf(play_pos.x) - 0.0001f;
		mov_pos.x = -1.f;
	}
	ray_pos.y = play_pos.y + (play_pos.x - ray_pos.x) * hit.angle.y;
	mov_pos.y = -mov_pos.x * hit.angle.y;
	while (!collision_detected(dt.maze, play_pos, ray_pos, hit.angle.x))
		add_pos(&ray_pos, &mov_pos);
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
		return (hit.distance = dist_h, hit_h);
	return (hit.distance = dist_v, hit_v);
}

void	update_hit_tpos(t_data *dt)
{
	int		i;
	float	angle_start;

	if (dt->nb_of_rays > 1)
		angle_start = norm_angle(dt->player.dir - (FOV / 2.0f));
	else
		angle_start = dt->player.dir;
	i = -1;
	while (dt->hits[++i].valid)
	{
		dt->hits[i].angle.x = norm_angle(angle_start + i * dt->rot_elem);
		dt->hits[i].angle.y = tanf(radian(dt->hits[i].angle.x));
		dt->hits[i].pos = found_hit_dda(*dt, dt->player.pos, dt->hits[i]);
	}
}
