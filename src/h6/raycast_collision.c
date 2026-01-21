/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_collision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:51:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/21 19:43:10 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check_collision(const t_maze *maze, int play_case, t_ipos ray_floor)
{
	if (ray_floor.x < 0 || ray_floor.x >= maze->width || \
		ray_floor.y < 0 || ray_floor.y >= maze->height)
		return (-1);
	if (play_case != maze->mat[ray_floor.y * maze->width + ray_floor.x])
		return (1);
	return (0);
}

/**
 * FIXED: detect ray collision on diagonal walls
 * NOTE	: if used for player collision detection will not work on diagonal walls
 * TODO	: Copy and improve to be used for player collision, then rename for:
 *        -> ray_collision_detection()
 */
int	collision_detected(const t_data *dt, t_fpos ray_pos)
{
	int		val;
	t_ipos	r_floor;
	t_ipos	r_round;

	val = dt->maze.mat[(int)floorf(dt->player.pos.y) * dt->maze.width + \
		(int)floorf(dt->player.pos.x)];
	r_floor = ipos_new((int)floorf(ray_pos.x), (int)floorf(ray_pos.y));
	if (check_collision(&dt->maze, val, r_floor))
		return (1);
	r_round = ipos_new((int)roundf(ray_pos.x), (int)roundf(ray_pos.y));
	if (ft_fabs((float)r_round.x - ray_pos.x) < PRE_RAY + EPSILON && \
		ft_fabs((float)r_round.y - ray_pos.y) < PRE_RAY + EPSILON)
	{
		if (check_collision(&dt->maze, val, r_round))
			return (1);
		if (check_collision(&dt->maze, val, ipos_new(r_round.x - 1, r_round.y)))
			return (1);
		if (check_collision(&dt->maze, val, ipos_new(r_round.x, r_round.y - 1)))
			return (1);
		if (check_collision(&dt->maze, val, \
			ipos_new(r_round.x - 1, r_round.y - 1)))
			return (1);
	}
	return (0);
}

t_fpos	h_found_hit_dda(const t_data *dt, const t_hit *hit)
{
	t_fpos	ray;
	t_fpos	mov;

	ray = dt->player.pos;
	mov = fpos_new(0.f, 0.f);
	if (hit->angle.x == 0.0f)
		return (fpos_new(dt->player.pos.x + dt->maze.width, dt->player.pos.y));
	if (hit->angle.x == 180.0f)
		return (fpos_new(dt->player.pos.x - dt->maze.width, dt->player.pos.y));
	if (hit->angle.x < 180.0f)
	{
		ray.y = floorf(dt->player.pos.y) - PRE_RAY;
		mov.y = -1.f;
	}
	else if (hit->angle.x > 180.0f)
	{
		ray.y = ceilf(dt->player.pos.y) + PRE_RAY;
		mov.y = 1.f;
	}
	ray.x = dt->player.pos.x + (dt->player.pos.y - ray.y) / hit->tan_angle;
	mov.x = -mov.y / hit->tan_angle;
	while (!collision_detected(dt, ray))
		fpos_add(&ray, &mov);
	return (ray);
}

t_fpos	v_found_hit_dda(const t_data *dt, const t_hit *hit)
{
	t_fpos	ray;
	t_fpos	mov;

	ray = dt->player.pos;
	mov = fpos_new(0.f, 0.f);
	if (hit->angle.x == 90.0f)
		return (ray.y = dt->player.pos.y - dt->maze.height, ray);
	if (hit->angle.x == 270.0f)
		return (ray.y = dt->player.pos.y + dt->maze.height, ray);
	if (hit->angle.x < 90.0f || hit->angle.x > 270.0f)
	{
		ray.x = ceilf(dt->player.pos.x) + PRE_RAY;
		mov.x = 1.f;
	}
	else if (90 < hit->angle.x && hit->angle.x < 270.0f)
	{
		ray.x = floorf(dt->player.pos.x) - PRE_RAY;
		mov.x = -1.f;
	}
	ray.y = dt->player.pos.y + (dt->player.pos.x - ray.x) * hit->tan_angle;
	mov.y = -mov.x * hit->tan_angle;
	while (!collision_detected(dt, ray))
		fpos_add(&ray, &mov);
	return (ray);
}
