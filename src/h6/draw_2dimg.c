/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2dimg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 11:09:07 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw2d_player(t_img *img, t_play *p)
{
	t_fpos	center;
	t_fpos	angle_speed;

	center = init_fpos(p->pos.x * TILE_X, p->pos.y * TILE_Y);
	angle_speed = init_fpos(p->dir, p->radius * 3);
	draw_circle(img, center, p->radius, p->color);
	draw_vector(img, center, angle_speed, BLUE_COLOR);
}

/**
 * TODO: use prod_scal_fpos(t_fpos *a, const float scalar)
 */
void	draw2d_hit_lines(t_data *dt)
{
	int		i;
	t_fpos	player;
	t_fpos	hit;

	player = init_fpos(dt->player.pos.x * TILE_X, dt->player.pos.y * TILE_Y);
	if (DRAW_2D_RAYS == 1)
	{
		hit = init_fpos(dt->hits[0].pos.x * TILE_X, dt->hits[0].pos.y * TILE_Y);
		draw_dda_line(&dt->img_2d_buffer, player, hit, GREEN_COLOR);
		i = dt->nb_of_rays - 1;
		hit = init_fpos(dt->hits[i].pos.x * TILE_X, dt->hits[i].pos.y * TILE_Y);
		draw_dda_line(&dt->img_2d_buffer, player, hit, GREEN_COLOR);
	}
	else
	{
		i = -1;
		while (dt->hits[++i].valid)
		{
			hit = init_fpos(dt->hits[i].pos.x * TILE_X, \
				dt->hits[i].pos.y * TILE_Y);
			draw_dda_line(&dt->img_2d_buffer, player, hit, GREEN_COLOR);
		}
	}
}

int	draw_buffer_2dimg(t_data *dt)
{
	if (!dup_t_img_by_words(&dt->img_2d_template, &dt->img_2d_buffer))
		return (fprintf(stderr, "Error: dup_t_img_by_words() failed\n"), 
			free_data(dt), 1);
	if (DRAW_2D_RAYS)
		draw2d_hit_lines(dt);
	draw2d_player(&dt->img_2d_buffer, &dt->player);
	return (0);
}
