/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2dimg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 04:34:28 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw2d_player(t_ima *img, t_play *p)
{
	t_fpos	center;
	t_fpos	angle_speed;

	center = fpos_new(p->pos.x * TILE_X, p->pos.y * TILE_Y);
	angle_speed = fpos_new(p->dir, p->radius * 3);
	draw_circle(img, center, p->radius, p->color);
	draw_vector_opti(img, center, angle_speed, p->color);
}

/**
 * NOTE: Could be opt by avoiding mult. calls to fpos_dot_new()
 */
void	draw2d_hit_lines(t_data *dt)
{
	int		i;
	t_fpos	play_pos;
	t_fpos	hit_pos;

	play_pos = fpos_dot_new(dt->player.pos, dt->tile_dim);
	if (DRAW_2D_RAYS == 1)
	{
		hit_pos = fpos_dot_new(dt->hits[0].pos, dt->tile_dim);
		draw_dda_line_opti(&dt->img_2d_buffer, play_pos, hit_pos, RAY2D_C);
		hit_pos = fpos_dot_new(dt->hits[dt->nb_of_rays - 1].pos, dt->tile_dim);
		draw_dda_line_opti(&dt->img_2d_buffer, play_pos, hit_pos, RAY2D_C);
	}
	else
	{
		i = -1;
		while (dt->hits[++i].valid)
		{
			hit_pos = fpos_dot_new(dt->hits[i].pos, dt->tile_dim);
			draw_dda_line_opti(&dt->img_2d_buffer, play_pos, hit_pos, RAY2D_C);
		}
	}
}

int	draw_buffer_2dimg(t_data *dt)
{
	if (!dup_t_ima_by_words(&dt->img_2d_template, &dt->img_2d_buffer))
		return (fprintf(stderr, "Error: dup_t_ima_by_words() failed\n"), 
			free_data(dt), 1);
	if (DRAW_2D_RAYS)
		draw2d_hit_lines(dt);
	draw2d_player(&dt->img_2d_buffer, &dt->player);
	return (0);
}
