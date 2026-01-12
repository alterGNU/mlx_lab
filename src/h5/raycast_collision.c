/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_collision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:51:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/12 13:58:29 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	collision_detected(t_maze maze, float fx, float fy, float angle)
{
	int	x;
	int	y;
	int	index;

	x = (int)floorf(fx);
	y = (int)floorf(fy);
	index = y * maze.width + x;
	printf("h_coll: from (%.2f, %.2f) check if maze[%d][%d]-->", fx, fy, x, y);
	if (angle < 180.0f && y < 0)
		return (printf(" COLLISION:MAZE-NORT-LIMIT\n"), -1);
	if (angle > 180.0f && y == maze.height)
		return (printf(" COLLISION:MAZE-SOUTH-LIMIT\n"), -1);
	if (x == maze.width && (angle < 90.0f || angle > 270.0f))
		return (printf(" COLLISION:MAZE-EAST-LIMIT\n"), -1);
	if (x < 0 && 90.0f < angle && angle < 270.0f)
		return (printf(" COLLISION:MAZE-WEST-LIMIT\n"), -1);
	if (0 <= index && index < maze.width * maze.height && maze.mat[index] == 1)
		return (printf(" COLLISION WALL maze[%d]\n", index), 1);
	return (printf("NO-maze[%d]\n", index), 0);

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
		return (printf("CHOOSED HOIZONTAL-HIT\n"), hit_h);
	return (printf("CHOOSED VERTICAL-HIT\n"), hit_v);
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