/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hit_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:24:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/25 10:01:58 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_hit	init_hit(void)
{
	t_hit	hit;

	hit.valid = 1;
	hit.type = ipos_new(0, -1);
	hit.pos = fpos_new(-1.f, -1.f);
	hit.dim = fpos_new(0.f, 0.f);
	hit.angle = fpos_new(-1.f, -1.f);
	hit.tan_angle = 0.f;
	hit.dist = fpos_new(0.f, 0.f);
	hit.y_inter = ipos_new(-1, -1);
	hit.txt_pix = fpos_new(-1.f, -1.f);
	hit.txt_ty = fpos_new(0.f, 0.f);
	hit.texture = NULL;
	hit.ima_xpm = NULL;
	return (hit);
}

void	set_hit_obj_dim(t_hit *hit)
{
	if (hit->type.x < 0)
		hit->dim = fpos_new(1.f, .8f);
	else
		hit->dim = fpos_new(1.f, 1.f);
}

void	set_hit_texture(const t_data *dt, t_hit *hit)
{
	if (hit->type.x < 0)
	{
		if (hit->type.x % 2)
			hit->texture = dt->txt_h;
		else
			hit->texture = dt->txt_v;
	}
	if (hit->type.x == NOW)
		hit->texture = dt->txt_north;
	if (hit->type.x == SOW)
		hit->texture = dt->txt_south;
	if (hit->type.x == EOW)
		hit->texture = dt->txt_east;
	if (hit->type.x == WOW)
		hit->texture = dt->txt_west;
}

void	set_hit_ima_xpm(const t_data *dt, t_hit *hit)
{
	if (hit->type.x < 0)
	{
		if (hit->type.x % 2)
			hit->ima_xpm = dt->ima_vins;
		else
			hit->ima_xpm = dt->ima_hins;
	}
	if (hit->type.x == NOW)
		hit->ima_xpm = dt->ima_north;
	if (hit->type.x == SOW)
		hit->ima_xpm = dt->ima_south;
	if (hit->type.x == EOW)
		hit->ima_xpm = dt->ima_east;
	if (hit->type.x == WOW)
		hit->ima_xpm = dt->ima_west;
}
