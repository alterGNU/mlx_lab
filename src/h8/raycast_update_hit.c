/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_update_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:51:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/25 04:53:37 by lagrondi         ###   ########.fr       */
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

static void	precomp_hit_vtext(t_hit *hit, float img_height)
{
	t_text	*txt;			// cast->easier access to texture struct
	float	line_height;	// dst image line height-->used to compute y_inter,ty_step
	float	line_offset;	// dst image line offset-->where to start drawing line-->use to compute y_inter
	float	ty_offset;		// ==> hit->txt_ty.y;

	txt = hit->texture;
	line_height = hit->dim.y * img_height / hit->dist.y;
	hit->txt_ty.x = (float)txt->dim.y / line_height;
	ty_offset = 0.f;
	if (line_height > img_height)
	{
		ty_offset = (line_height - (float)img_height) / 2.0f;
		line_height = (float)img_height;
	}
	line_offset = (img_height - line_height) / 2.0f;
	// compute y start & y stop in dst image
	hit->y_inter.x = ft_imax(line_offset, 0);
	hit->y_inter.y = ft_imin(line_height + line_offset, img_height - 1);
	if (hit->y_inter.x < hit->y_inter.y)
	{
		// compute texture x coord. & initial y coord. in texture
		if (hit->type.x % 2)
		{
			hit->txt_pix.x = (float)(hit->pos.x - (int)hit->pos.x) * (float)txt->dim.x;
			if (hit->angle.x > 180.f)
				hit->txt_pix.x = (float)txt->dim.x - hit->txt_pix.x;
		}
		else
		{
			hit->txt_pix.x = (float)(hit->pos.y - (int)hit->pos.y) * (float)txt->dim.x;
			if (90 < hit->angle.x && hit->angle.x < 270.f)
				hit->txt_pix.x = (float)txt->dim.x - hit->txt_pix.x;
		}
		hit->txt_pix.y = ty_offset * hit->txt_ty.x;
	}
}

static void	precomp_hit_xpm(t_hit *hit, float img_height)
{
	t_fpos line;

	line.x = hit->dim.y * img_height / hit->dist.y;
	hit->txt_ty = fpos_new((float)hit->ima_xpm->dim.y / line.x, 0.f);
	if (line.x > img_height)
	{
		hit->txt_ty.y = (line.x - (float)img_height) / 2.f;
		line.x = img_height;
	}
	line.y = (img_height - line.x) / 2.0f;
	hit->y_inter = ipos_new(ft_imax(line.y, 0),
							ft_imin(line.x + line.y, img_height - 1));
	if (hit->type.x % 2)
	{
		hit->txt_pix = fpos_new(fmodf(hit->pos.x, 1.0f) * (float)hit->ima_xpm->dim.x, fpos_prod(hit->txt_ty));
		if (hit->angle.x > 180.f)
			hit->txt_pix.x = (float)hit->ima_xpm->dim.x - hit->txt_pix.x;
	}
	else
	{
		hit->txt_pix = fpos_new(fmodf(hit->pos.y, 1.0f) * (float)hit->ima_xpm->dim.x, fpos_prod(hit->txt_ty));
		if (90 < hit->angle.x && hit->angle.x < 270.f)
			hit->txt_pix.x = (float)hit->ima_xpm->dim.x - hit->txt_pix.x;
	}
}

static void precomp_hit_vline(t_hit *hit, float img_height)
{
	t_fpos	line;

	line.x = hit->dim.y * img_height / hit->dist.y;
	if (line.x > img_height)
	{
		hit->txt_ty.y = (line.x - (float)img_height) / 2.f;
		line.x = img_height;
	}
	line.y = (img_height - line.x) / 2.0f;
	hit->y_inter = ipos_new(ft_imax(line.y, 0), ft_imin(line.x + line.y, img_height - 1));
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
		if (dt->txt_mode == 2)
		{
			set_hit_ima_xpm(dt, &dt->hits[i]);
			if (DRAW_FUN_AUTO == 0)
			{
				precomp_hit_xpm(&dt->hits[i], (float)dt->img_3d_buffer.dim.y);
			}
		}
		else if (dt->txt_mode == 1)
		{
			set_hit_texture(dt, &dt->hits[i]);
			if (DRAW_FUN_AUTO == 0)
			{
				precomp_hit_vtext(&dt->hits[i], (float)dt->img_3d_buffer.dim.y);
			}
		}
		else
		{
			if (DRAW_FUN_AUTO == 0)
			{
				precomp_hit_vline(&dt->hits[i], (float)dt->img_3d_buffer.dim.y);
			}
		}
	}
}
