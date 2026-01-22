/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_update_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:51:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/22 09:26:47 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	set_hit_type_ver(const t_data *dt, const t_fpos hit_v, t_hit *hit)
{
	t_ipos	play;
	int		type;

	play = ipos_new((int)dt->player.pos.x, (int)dt->player.pos.y);
	if (dt->maze.mat[play.y * dt->maze.width + play.x] == 1)
	{
		type = WIW;
		if (dt->player.pos.x < hit_v.x)
			type = EIW;
	}
	else
	{
		type = WOW;
		if (dt->player.pos.x < hit_v.x)
			type = EOW;
	}
	set_hit_type(dt, hit, type);
}

static void	set_hit_type_hor(const t_data *dt, const t_fpos hit_h, t_hit *hit)
{
	t_ipos	play;
	int		type;

	play = ipos_new((int)dt->player.pos.x, (int)dt->player.pos.y);
	if (dt->maze.mat[play.y * dt->maze.width + play.x] == 1)
	{

		type = NIW;
		if (dt->player.pos.y < hit_h.y)
			type = SIW;
	}
	else
	{
		type = NOW;
		if (dt->player.pos.y < hit_h.y)
			type = SOW;
	}
	set_hit_type(dt, hit, type);
}

void	found_hit_dda(const t_data *dt, t_hit *hit)
{
	t_fpos	hit_h;
	t_fpos	hit_v;
	float	dist_h;
	float	dist_v;
	float	cos_angle_corr;

	hit_h = h_found_hit_dda(dt, hit);
	hit_v = v_found_hit_dda(dt, hit);
	dist_h = fpos_dist(dt->player.pos, hit_h);
	dist_v = fpos_dist(dt->player.pos, hit_v);
	cos_angle_corr = cosf(radian(norm_angle(dt->player.dir - \
		hit->angle.x)));
	if (dist_h < dist_v)
	{
		hit->pos = hit_h;
		hit->distance = dist_h;
		set_hit_type_hor(dt, hit_h, hit);
	}
	else
	{
		hit->pos = hit_v;
		hit->distance = dist_v;
		set_hit_type_ver(dt, hit_v, hit);
	}
	hit->dist_corr = hit->distance * cos_angle_corr;
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
		dt->hits[i].angle.y = radian(dt->hits[i].angle.x);
		dt->hits[i].tan_angle = tanf(dt->hits[i].angle.y);
		found_hit_dda(dt, &dt->hits[i]);
	}
}
