/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:47:06 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/09 10:02:46 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_hit_tpos(t_data *dt)
{
	int		i;
	float	angle;
	float	x_hit;
	float	y_hit;

	i = -1;
	while (dt->hit_tpos[++i])
	{
		angle = norm_angle(dt->player.dir - (FOV / 2.0f) + (i * FOV_PRE));

		x_hit = dt->player.pos.x + cosf(radian(angle));
		y_hit = dt->player.pos.y - sinf(radian(angle));
		*dt->hit_tpos[i] = init_pos(x_hit , y_hit);
		//printf("hit_tpos[%d]: angle=%.2f ORIGIN=", i, angle);
		//print_pos(dt->player.pos);
		//printf(" --- END=");
		//print_pos(*dt->hit_tpos[i]);
		//printf("\n");
	}
}
