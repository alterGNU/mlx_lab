/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:47:06 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/10 17:22:13 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//static int	is_a_wall(t_maze maze, int x, int y)
//{
//	if (x < 0 || x > maze.width || y < 0 || y > maze.height)
//		return (1);
//	if (maze.mat[y * maze.width + x] == 1)
//		return (printf("COLLISION DETECTED INSIDE x=%d y=%d\n", x, y));
//	return (0);
//}

//static t_pos	found_hit_dda(t_maze maze, t_pos a_pos, t_pos b_pos)
//{
//	int		dx;
//	int		dy;
//	int		steps;
//	float	sx;
//	float	sy;
//
//	dx = b_pos.x - a_pos.x;
//	dy = b_pos.y - a_pos.y;
//	steps = ft_max(abs(dx), abs(dy));
//	sx = (float)dx / steps;
//	sy = (float)dy / steps;
//	while (steps-- >= 0)
//	{
//		//put_pixel_to_image(img, round(a_pos.x), round(a_pos.y), color);
//		if (is_a_wall(maze, round(a_pos.x), round(a_pos.y)))
//		{
//			return (b_pos);
//			//return (init_pos(a_pos.x, a_pos.y));
//		}
//		a_pos.x += sx;
//		a_pos.y += sy;
//	}
//	return (b_pos);
//}

/**
 * 
 * 1 1 1 1 1
 * 1 0 0 0 1
 * 1 0 0 E 1
 * 1 0 0 0 1
 * 1 1 1 1 1
 * 
static t_pos	found_hit_dda(t_maze maze, t_pos a_pos, t_pos b_pos)
{
	int		dx;
	int		dy;
	//int		steps;
	int		x;
	float	sum_dx;
	float	y;

	dx = b_pos.x - a_pos.x; // dx < 0 --> [135,225]
	dy = b_pos.y - a_pos.y;
	printf("a_pos: (%.2f, %.2f)--->\n", a_pos.x, a_pos.y);
	if (0 < dx && dy <= dx)
	{
		printf("CAS 1\n");
		x = (int)(a_pos.x);
		sum_dx = (float)(x + 1) - a_pos.x;
		while (++x <= maze.width)
		{
			printf("(x=%d, y=%.2f)", x, y);
			y = (a_pos.y + ((float)dy / dx));
			if (is_a_wall(maze, x, round(y)))
			{
				printf("===>RETURN WALL at (%.2f, %.2f)\n", x + sum_dx, y);
				return (init_pos(x, 1 - y));
			}
		}
	}
	else
	{
		printf("CAS 2\n");
	}
	return (init_pos(-1, -1));
}
*/

void	update_hit_tpos(t_data *dt)
{
	int		i;
	float	angle;
	float	angle_start;
	float	x_hit;
	float	y_hit;

	if (dt->nb_of_rays <= 1)
	{
		x_hit = dt->player.pos.x + cosf(radian(dt->player.dir)) * dt->big_ben;
		y_hit = dt->player.pos.y - sinf(radian(dt->player.dir)) * dt->big_ben;
		dt->hits[0] = set_hit(&dt->hits[0], x_hit, y_hit, dt->player.dir);
	}
	else
	{
		angle_start = norm_angle(dt->player.dir - (FOV / 2.0f));
		i = -1;
		while (dt->hits[++i].valid)
		{
			angle = norm_angle(angle_start + i * FOV * FOV_PRE / (FOV - FOV_PRE));
			x_hit = dt->player.pos.x + cosf(radian(angle)) * dt->big_ben;
			y_hit = dt->player.pos.y - sinf(radian(angle)) * dt->big_ben;
			dt->hits[i] = set_hit(&dt->hits[i], x_hit, y_hit, angle);
			//*dt->hit_tpos[i] = found_hit_dda(dt->maze, dt->player.pos, init_pos(x_hit, y_hit));
		}
	}
}
