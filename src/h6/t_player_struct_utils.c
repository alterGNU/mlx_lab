/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_player_struct_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:34:13 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 06:27:40 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	toggle_player_mode(t_play *player)
{
	if (player->mode)
	{
		player->mode = 0;
		snprintf(player->play_str, 63, \
			"Pos(%.2f, %.2f), Dir: %.2f, Mode=GHOST", player->pos.x, \
			player->pos.y, player->dir);
		player->color = BLUE_COLOR;
	}
	else
	{
		player->mode = 1;
		snprintf(player->play_str, 63, \
			"Pos(%.2f, %.2f), Dir: %.2f, Mode=MORTAL", player->pos.x, \
			player->pos.y, player->dir);
		player->color = RED_COLOR;
	}
}

int	player_diff(const t_play *play_a, const t_play *play_b)
{
	if (play_a->pos.x != play_b->pos.x || \
		play_a->pos.y != play_b->pos.y || \
		play_a->dir != play_b->dir || \
		play_a->step_count != play_b->step_count || \
		play_a->mode != play_b->mode)
		return (1);
	return (0);
}
