/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_player_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:34:13 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/04 14:50:09 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_play	init_player(void)
{
	t_play	player;

	player.pos.x = -0.1;
	player.pos.y = -0.1;
	player.color = RED_COLOR;
	player.radius = CIRCLE_RADIUS;
	player.step_count = 0;
	return (player);
}

void	draw_player(t_img *img, t_play *player)
{
	int	cx;
	int	cy;

	cx = player->pos.x * TILE_X;
	cy = player->pos.y * TILE_Y;
	draw_circle(img, cx, cy, player->radius, player->color);
}
