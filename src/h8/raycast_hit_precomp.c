/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_hit_precomp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:51:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/25 08:23:17 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	precomp_hit_vline(t_hit *hit, float img_height)
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

static void	set_txt_pix_texture(t_hit *hit, float ty_offset)
{
	if (hit->type.x % 2)
	{
		hit->txt_pix.x = fmodf(hit->pos.x, 1.0f) * (float)hit->texture->dim.x;
		if (hit->angle.x > 180.f)
			hit->txt_pix.x = (float)hit->texture->dim.x - hit->txt_pix.x;
	}
	else
	{
		hit->txt_pix.x = fmodf(hit->pos.y, 1.0f) * (float)hit->texture->dim.x;
		if (90 < hit->angle.x && hit->angle.x < 270.f)
			hit->txt_pix.x = (float)hit->texture->dim.x - hit->txt_pix.x;
	}
	hit->txt_pix.y = ty_offset * hit->txt_ty.x;
}

/**
 * t_text	*txt;		-> cast->easier access to texture struct
 * float	line_height;-> dst line height-->used to compute y_inter,ty_step
 * float	line_offset;-> dst line offset-->use to compute y_inter
 * float	ty_offset;	-> hit->txt_ty.y;
 */
void	precomp_hit_vtext(t_hit *hit, float img_height)
{
	t_text	*txt;
	float	line_height;
	float	line_offset;
	float	ty_offset;

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
	hit->y_inter.x = ft_imax(line_offset, 0);
	hit->y_inter.y = ft_imin(line_height + line_offset, img_height - 1);
	if (hit->y_inter.x < hit->y_inter.y)
		set_txt_pix_texture(hit, ty_offset);
}

static void	set_txt_pix_xpm(t_hit *hit, float ty_offset)
{
	if (hit->type.x % 2)
	{
		hit->txt_pix.x = fmodf(hit->pos.x, 1.0f) * (float)hit->ima_xpm->dim.x;
		if (hit->angle.x > 180.f)
			hit->txt_pix.x = (float)hit->ima_xpm->dim.x - hit->txt_pix.x;
	}
	else
	{
		hit->txt_pix.x = fmodf(hit->pos.y, 1.0f) * (float)hit->ima_xpm->dim.x;
		if (90 < hit->angle.x && hit->angle.x < 270.f)
			hit->txt_pix.x = (float)hit->ima_xpm->dim.x - hit->txt_pix.x;
	}
	hit->txt_pix.y = ty_offset * hit->txt_ty.x;
}

void	precomp_hit_xpm(t_hit *hit, float img_height)
{
	t_fpos	line;

	line.x = hit->dim.y * img_height / hit->dist.y;
	hit->txt_ty = fpos_new((float)hit->ima_xpm->dim.y / line.x, 0.f);
	if (line.x > img_height)
	{
		hit->txt_ty.y = (line.x - (float)img_height) / 2.f;
		line.x = img_height;
	}
	line.y = (img_height - line.x) / 2.0f;
	hit->y_inter = ipos_new(ft_imax(line.y, 0), \
		ft_imin(line.x + line.y, img_height - 1));
	if (hit->y_inter.x < hit->y_inter.y)
		set_txt_pix_xpm(hit, hit->txt_ty.y);
}
