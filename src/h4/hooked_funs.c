/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooked_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:25:21 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/07 18:49:20 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	move_player(t_data *dt, float rot, float speed)
{
	float	next_x;
	float	next_y;

	next_x = dt->player.pos.x + cosf(radian(dt->player.dir + rot)) * speed;
	next_y = dt->player.pos.y - sinf(radian(dt->player.dir + rot)) * speed;
	if (0 <= next_x && next_x < dt->maze.width && \
		0 <= next_y && next_y < dt->maze.height)
		set_player(&dt->player, next_x, next_y, dt->player.dir);
}

int	handle_key(int keycode, t_data *dt)
{
	float	tmp_dir;

	if (keycode == ESC_KEY)
		return (mlx_loop_end(dt->mlx_ptr), 1);
	else if (keycode == W_KEY)
		move_player(dt, 0, SPEED);
	else if (keycode == S_KEY)
		move_player(dt, 0, -SPEED);
	else if (keycode == A_KEY)
		move_player(dt, 90, SPEED);
	else if (keycode == D_KEY)
		move_player(dt, -90, SPEED);
	else if (keycode == Q_KEY || keycode == LA_KEY)
	{
		tmp_dir = dt->player.dir + ROT_STEP;
		if (tmp_dir >= 360.0)
			tmp_dir -= 360.0;
		set_player(&dt->player, dt->player.pos.x, dt->player.pos.y, tmp_dir);
	}
	else if (keycode == E_KEY || keycode == RA__KEY)
	{
		tmp_dir = dt->player.dir - ROT_STEP;
		if (tmp_dir < 0.0)
			tmp_dir += 360.0;
		set_player(&dt->player, dt->player.pos.x, dt->player.pos.y, tmp_dir);
	}
	return (0);
}

static void	display_debug_infos(t_data *dt)
{
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_info.img_ptr, 0, 0);
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 10, 12, WHITE_COLOR, dt->player.play_str);
}

int	draw_buffer_image(t_data *dt)
{
	struct timeval	act_time;

	if (!dt->mlx_ptr || !dt->win_ptr)
		return (printf("Error: Invalid data pointers\n"), 1);
	if (gettimeofday(&act_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	if (!dup_t_img_by_words(&dt->img_grid, &dt->img_buffer))
		return (fprintf(stderr, "Error: dup_t_img() failed\n"), free_data(dt), 1);
	draw_player(&dt->img_buffer, &dt->player); // second layer:player
	if (dt->img_drawn)
	{
		while (diff_time_in_ms(dt->last_frame_time, act_time) < dt->delay_between_frames_ms)
		{
			if (gettimeofday(&act_time, NULL) < 0)
				return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
		}
	}
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_buffer.img_ptr, 5, 20);
	display_debug_infos(dt);
	dt->img_drawn++;
	if (gettimeofday(&dt->last_frame_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	return (0);
}
