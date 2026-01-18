/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_player_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:34:13 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 16:33:00 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_play	init_player(void)
{
	t_play	player;

	player.pos = fpos_new(-0.1, -0.1);
	player.dir = -1.0;
	player.color = RED_COLOR;
	player.radius = CIRCLE_RADIUS;
	player.step_count = 0;
	player.play_str = calloc(sizeof(char), 31);
	return (player);
}

void	set_player(t_play *play, float x, float y, float dir)
{
	play->pos.x = x;
	play->pos.y = y;
	play->dir = dir;
	snprintf(play->play_str, 31, "Pos(%.2f, %.2f), Dir: %.2f", play->pos.x, play->pos.y, play->dir);
	play->step_count++;
}

int	print_player(t_play play)
{
	int	psf;

	psf = printf("Play{");
	psf += fpos_print(play.pos);
	psf += printf(", dir: %.2f", play.dir);
	psf += printf(", color: 0x%X, ", play.color);
	psf += printf("radius: %d, step: %d}", play.radius, play.step_count);
	return (psf);
}

void	free_player(t_play *player)
{
	if (player->play_str)
	{
		free(player->play_str);
		player->play_str = NULL;
	}
}
