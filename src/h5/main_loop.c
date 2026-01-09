/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:25:21 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/09 12:59:20 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	main_loop(t_data *dt)
{
	if (gettimeofday(&dt->fps_arr[dt->img_drawn % FPS_IMG_NB], NULL) < 0)
		return (perror("main_loop: gettimeofday() failed"), free_data(dt), 1);
	move_player(dt);
	display_player_infos(dt);
	// update_hit_tpos(dt);
	if (draw_buffer_image(dt))
		return (free_data(dt), exit(1), 1);
	if (dt->img_drawn % (FPS_IMG_NB - 1) == 0)
		display_fps_infos(dt);
	return (0);
}
