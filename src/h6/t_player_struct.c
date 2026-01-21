/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_player_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:34:13 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/21 19:44:24 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * NOTE: player.mod:0 ghost_mode->no collision, 1: mortal_mode->collision enabled
 */
t_play	init_player(void)
{
	t_play	player;

	player.pos = fpos_new(-0.1, -0.1);
	player.dir = -1.0;
	player.color = BLUE_COLOR;
	player.radius = CIRCLE_RADIUS;
	player.step_count = 0;
	player.play_str = calloc(sizeof(char), 64);
	player.mode = 0;
	return (player);
}

//TODO: player.step_count wrongly incremented
void	set_player(t_play *play, float x, float y, float dir)
{
	play->pos.x = x;
	play->pos.y = y;
	play->dir = dir;
	if (play->mode)
		snprintf(play->play_str, 63, "Pos(%.2f, %.2f), Dir: %.2f, Mode=MORTAL", play->pos.x, play->pos.y, play->dir);
	else
		snprintf(play->play_str, 63, "Pos(%.2f, %.2f), Dir: %.2f, Mode=GHOST", play->pos.x, play->pos.y, play->dir);
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

/**
 * NOTE: player 
 */
void	free_player(t_play *player)
{
	if (player->play_str)
	{
		free(player->play_str);
		player->play_str = NULL;
	}
}
