/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:25:21 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/17 02:27:08 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * TODO:
 * - some of this function are engine-specific (move_player, coll-detect...):
 *   --> Clean code an move to an engine file if needed.
 */
static int	move_player_pos(t_data *dt, float rot, float speed)
{
	float	next_x;
	float	next_y;

	next_x = dt->player.pos.x + cosf(radian(dt->player.dir + rot)) * speed;
	next_y = dt->player.pos.y - sinf(radian(dt->player.dir + rot)) * speed;
	if (0 <= next_x && next_x < dt->maze.width && \
		0 <= next_y && next_y < dt->maze.height)
		return (set_player(&dt->player, next_x, next_y, dt->player.dir), 1);
	return (0);
}

/**
 * Use set_player() instead of directly modifying dt->player.{pos, dir} 'cause:
 * -> set_player() is the function that updates dt->player.step_count
 * -> set_player() is the function that updates dt->player.play_str
 */
static void	move_player(t_data *dt)
{
	if (dt->mv_flags[0] == 'Q')
		set_player(&dt->player, dt->player.pos.x, dt->player.pos.y, \
			norm_angle(dt->player.dir + ANG_SPEED));
	if (dt->mv_flags[2] == 'E')
		set_player(&dt->player, dt->player.pos.x, dt->player.pos.y, \
			norm_angle(dt->player.dir - ANG_SPEED));
	if (dt->mv_flags[1] == 'W')
		move_player_pos(dt, 0, POS_SPEED);
	if (dt->mv_flags[4] == 'S')
		move_player_pos(dt, 0, -POS_SPEED);
	if (dt->mv_flags[3] == 'A')
		move_player_pos(dt, 90, POS_SPEED);
	if (dt->mv_flags[5] == 'D')
		move_player_pos(dt, -90, POS_SPEED);
}

/**
 * TODO:
 * 	- Player could have a rotation counter too
 */
static int	player_moved(t_play *old_play, t_play *new_play)
{
	if (old_play->pos.x != new_play->pos.x || \
		old_play->pos.y != new_play->pos.y || \
		old_play->dir != new_play->dir || \
		old_play->step_count != new_play->step_count)
		return (1);
	return (0);
}

int	main_loop(t_data *dt)
{
	t_play	old_player;

	if (!dt->img_drawn)
	{
		if (gettimeofday(&dt->fps_start_inter, NULL) < 0)
			return (perror("main_loop: !gettimeofday()"), free_data(dt), 1);
		update_hit_tpos(dt);
		display_player_infos(dt, 0);
		display_fps_infos(dt, 1);
		if (DRAW_HITS_TXT)
			display_hits_infos(dt, 2);
	}
	old_player = dt->player;
	move_player(dt);
	if (player_moved(&old_player, &dt->player))
	{
		update_hit_tpos(dt);
		display_player_infos(dt, 0);
	}
	if (draw_buffer_images(dt))
		return (free_data(dt), exit(1), 1);
	if (dt->img_drawn % FPS_DELTA == 0)
	{
		display_fps_infos(dt, 1);
		if (DRAW_HITS_TXT)
			display_hits_infos(dt, 2);
		dt->fps_start_inter = dt->last_frame_time;
	}
	return (0);
}
