/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_collision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:51:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/16 13:47:56 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * TODO:
 * - Should be called by mouvement fun. too! (if next step collides, block it)
 * - Should return objects types hit {Out-In}side-Wall:(N,S,E,W),Bounderies,...
 * - Can be rewritte to use t_ipos and t_fpos
 * - Can be optimized a bit more (order! and some cases dont need to be checked)
 *   -> if(index_play <0 || dt->maze.cell_nb <= index_play) can be removed
 */
int	collision_detected(const t_data *dt, t_pos ray_pos, float angle)
{
	int	index_play;
	int	x;
	int	y;
	int	index_ray;

	index_play = (int)floorf(dt->player.pos.y) * dt->maze.width + \
		(int)floorf(dt->player.pos.x);
	if (index_play < 0 || dt->maze.cell_nb <= index_play)
		return (printf("play_pos outside maze limits\n"));
	x = (int)floorf(ray_pos.x);
	y = (int)floorf(ray_pos.y);
	if (y < 0 && angle < 180.0f)									// On FIRST MAZE LINE facing NORTH
		return (-1);												// --> HIT NORTH BOUNDARY
	if (y == dt->maze.height && angle > 180.0f)						// On LAST MAZE LINE facing SOUTH
		return (-1);												// --> HIT SOUTH BOUNDARY
	if (x == dt->maze.width && (angle < 90.0f || 270.0f < angle))	// On LAST MAZE COLUMN facing EAST
		return (-1);												// --> HIT EAST BOUNDARY
	if (x < 0 && 90.0f < angle && angle < 270.0f)					// On FIRST MAZE COLUMN facing WEST
		return (-1);												// --> HIT WEST BOUNDARY
	index_ray = y * dt->maze.width + x;
	if (index_ray < 0 || dt->maze.cell_nb <= index_ray)				// Ray outside maze limits
		return (-1);
	if (dt->maze.mat[index_play] != dt->maze.mat[index_ray])		// Different cell -> HIT
		return (1);
	return (0);
}

t_pos	h_found_hit_dda(const t_data *dt, const t_hit *hit)
{
	t_pos	ray;
	t_pos	mov;

	ray = dt->player.pos;
	mov = init_pos(0.f, 0.f);
	if (hit->angle.x == 0.0f)
		return (init_pos(dt->player.pos.x + dt->maze.width, dt->player.pos.y));
	if (hit->angle.x == 180.0f)
		return (init_pos(dt->player.pos.x - dt->maze.width, dt->player.pos.y));
	if (hit->angle.x < 180.0f)
	{
		ray.y = floorf(dt->player.pos.y) - 0.0001f;
		mov.y = -1.f;
	}
	else if (hit->angle.x > 180.0f)
	{
		ray.y = ceilf(dt->player.pos.y) + 0.0001f;
		mov.y = 1.f;
	}
	ray.x = dt->player.pos.x + (dt->player.pos.y - ray.y) / hit->angle.y;
	mov.x = -mov.y / hit->angle.y;
	while (!collision_detected(dt, ray, hit->angle.x))
		add_pos(&ray, &mov);
	return (ray);
}

t_pos	v_found_hit_dda(const t_data *dt, const t_hit *hit)
{
	t_pos	ray;
	t_pos	mov;

	ray = dt->player.pos;
	mov = init_pos(0.f, 0.f);
	if (hit->angle.x == 90.0f)
		return (ray.y = dt->player.pos.y - dt->maze.height, ray);
	if (hit->angle.x == 270.0f)
		return (ray.y = dt->player.pos.y + dt->maze.height, ray);
	if (hit->angle.x < 90.0f || hit->angle.x > 270.0f)
	{
		ray.x = ceilf(dt->player.pos.x) + 0.0001f;
		mov.x = 1.f;
	}
	else if (90 < hit->angle.x && hit->angle.x < 270.0f)
	{
		ray.x = floorf(dt->player.pos.x) - 0.0001f;
		mov.x = -1.f;
	}
	ray.y = dt->player.pos.y + (dt->player.pos.x - ray.x) * hit->angle.y;
	mov.y = -mov.x * hit->angle.y;
	while (!collision_detected(dt, ray, hit->angle.x))
		add_pos(&ray, &mov);
	return (ray);
}

void	found_hit_dda(const t_data *dt, t_hit *hit)
{
	t_pos	hit_h;
	t_pos	hit_v;
	float	dist_h;
	float	dist_v;

	hit_h = h_found_hit_dda(dt, hit);
	hit_v = v_found_hit_dda(dt, hit);
	dist_h = tpos_dist(dt->player.pos, hit_h);
	dist_v = tpos_dist(dt->player.pos, hit_v);
	if (dist_h < dist_v)
	{
		hit->pos = hit_h;
		hit->distance = dist_h;
	}
	else
	{
		hit->pos = hit_v;
		hit->distance = dist_v;
	}
}

void	update_hit_tpos(t_data *dt)
{
	int		i;
	float	angle_start;

	if (dt->nb_of_rays > 1)
		angle_start = norm_angle(dt->player.dir + (FOV / 2.0f));
	else
		angle_start = dt->player.dir;
	i = -1;
	while (dt->hits[++i].valid)
	{
		dt->hits[i].angle.x = norm_angle(angle_start - i * dt->rot_elem);
		dt->hits[i].angle.y = tanf(radian(dt->hits[i].angle.x));
		found_hit_dda(dt, &dt->hits[i]);
	}
}
