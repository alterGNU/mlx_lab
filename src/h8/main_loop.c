/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:25:21 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 19:20:54 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * FIX	: re-writte collision_detected() fun. to handle diagonal wall
 * TODO	: could use a minimal distance to wall :DIST_MIN_WALL
 * NOTE	: Engine related-codex can be moved to an engine-file if needed.
 */
static int	move_player_pos(t_data *dt, float rot, float speed)
{
	t_fpos	next_pos;

	next_pos = fpos_new(dt->player.pos.x + cosf(radian(dt->player.dir + rot)) \
		* speed, dt->player.pos.y - sinf(radian(dt->player.dir + rot)) * speed);
	if (!dt->player.mode)
	{
		if (0 <= next_pos.x && next_pos.x < dt->maze.width && \
			0 <= next_pos.y && next_pos.y < dt->maze.height)
			return (set_player(&dt->player, next_pos.x, next_pos.y, \
				dt->player.dir), 1);
	}
	if (!collision_detected(dt, next_pos))
		return (set_player(&dt->player, next_pos.x, next_pos.y, \
				dt->player.dir), 1);
	return (0);
}

/**
 * Use set_player() instead of directly modifying dt->player.{pos, dir} 'cause:
 * -> set_player() is the function that updates dt->player.step_count
 * -> set_player() is the function that updates dt->player.play_str
 * TODO: player.step_count wrongly incremented
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

static int	first_image(t_data *dt)
{
	if (gettimeofday(&dt->fps_start_inter, NULL) < 0)
		return (perror("main_loop: !gettimeofday()"), free_data(dt), 1);
	update_hit_tpos(dt);
	display_player_infos(dt, 0);
	display_fps_infos(dt, 1);
	if (DISPLAY_FUNCALLED)
		display_function_called(dt, 2);
	if (DRAW_HITS_TXT)
		display_hits_infos(dt, 3);
	return (0);
}

// BUG: fps_str not updated correctly when play-mode changes wihtout moving
int	main_loop(t_data *dt)
{
	t_play	old_player;

	if (!dt->img_drawn)
	{
		if (first_image(dt))
			return (1);
	}
	old_player = dt->player;
	move_player(dt);
	if (player_diff(&old_player, &dt->player))
	{
		display_player_infos(dt, 0);
		update_hit_tpos(dt);
	}
	if (draw_buffer_images(dt))
		return (free_data(dt), exit(1), 1);
	if (dt->img_drawn % FPS_DELTA == 0)
	{
		display_fps_infos(dt, 1);
		if (DISPLAY_FUNCALLED)
			display_function_called(dt, 2);
		if (DRAW_HITS_TXT)
			display_hits_infos(dt, 3);
		dt->fps_start_inter = dt->last_frame_time;
	}
	return (0);
}
