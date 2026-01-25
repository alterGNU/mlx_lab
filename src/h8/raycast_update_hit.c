/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_update_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:51:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/25 08:25:55 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	set_hit_type_ver(const t_data *dt, const t_fpos hit_v, t_hit *hit)
{
	t_ipos	play;

	play = ipos_new((int)dt->player.pos.x, (int)dt->player.pos.y);
	if (dt->maze.mat[play.y * dt->maze.width + play.x] == 1)
	{
		if (dt->player.pos.x < hit_v.x)
			hit->type = ipos_new(EIW, EIW_COLOR);
		else
			hit->type = ipos_new(WIW, WIW_COLOR);
	}
	else
	{
		if (dt->player.pos.x < hit_v.x)
			hit->type = ipos_new(EOW, EOW_COLOR);
		else
			hit->type = ipos_new(WOW, WOW_COLOR);
	}
}

static void	set_hit_type_hor(const t_data *dt, const t_fpos hit_h, t_hit *hit)
{
	t_ipos	play;

	play = ipos_new((int)dt->player.pos.x, (int)dt->player.pos.y);
	if (dt->maze.mat[play.y * dt->maze.width + play.x] == 1)
	{

		if (dt->player.pos.y < hit_h.y)
			hit->type = ipos_new(SIW, SIW_COLOR);
		else
			hit->type = ipos_new(NIW, NIW_COLOR);
	}
	else
	{
		if (dt->player.pos.y < hit_h.y)
			hit->type = ipos_new(SOW, SOW_COLOR);
		else
			hit->type = ipos_new(NOW, NOW_COLOR);
	}
}

void	found_hit_set_type(const t_data *dt, t_hit *hit)
{
	t_fpos	hit_h;
	t_fpos	hit_v;
	float	dist_h;
	float	dist_v;

	hit_h = h_found_hit_dda(dt, hit);
	hit_v = v_found_hit_dda(dt, hit);
	dist_h = fpos_dist(dt->player.pos, hit_h);
	dist_v = fpos_dist(dt->player.pos, hit_v);
	if (dist_h < dist_v)
	{
		hit->pos = hit_h;
		hit->dist.x = dist_h;
		set_hit_type_hor(dt, hit_h, hit);
	}
	else
	{
		hit->pos = hit_v;
		hit->dist.x = dist_v;
		set_hit_type_ver(dt, hit_v, hit);
	}
	hit->dist.y = hit->dist.x * \
		cosf(radian(norm_angle(dt->player.dir - hit->angle.x)));
}

static void	set_hit_txt_and_precomp(t_data *dt, t_hit *hit)
{
	if (dt->txt_mode == 2)
	{
		set_hit_ima_xpm(dt, hit);
		if (DRAW_FUN_AUTO == 0)
			precomp_hit_xpm(hit, (float)dt->img_3d_buffer.dim.y);
	}
	else if (dt->txt_mode == 1)
	{
		set_hit_texture(dt, hit);
		if (DRAW_FUN_AUTO == 0)
			precomp_hit_vtext(hit, (float)dt->img_3d_buffer.dim.y);
	}
	else
	{
		if (DRAW_FUN_AUTO == 0)
			precomp_hit_vline(hit, (float)dt->img_3d_buffer.dim.y);
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
		dt->hits[i].angle.y = radian(dt->hits[i].angle.x);
		dt->hits[i].tan_angle = tanf(dt->hits[i].angle.y);
		found_hit_set_type(dt, &dt->hits[i]);
		set_hit_obj_dim(&dt->hits[i]);
		set_hit_txt_and_precomp(dt, &dt->hits[i]);
	}
}
