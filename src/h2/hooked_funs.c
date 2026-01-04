/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooked_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:25:21 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/04 19:30:37 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	handle_key(int keycode, t_data *dt)
{
	if (keycode == ESC_KEY)
		return (mlx_loop_end(dt->mlx_ptr), 1);
	else if (keycode == W_KEY)
	{
		if (dt->player.pos.y - STEP >= 0)
		{
			dt->player.step_count++;
			dt->player.pos.y -= STEP;
		}
	}
	else if (keycode == S_KEY)
	{
		if (dt->player.pos.y < (float)dt->maze.height)
		{
			dt->player.step_count++;
			dt->player.pos.y += STEP;
		}
	}
	else if (keycode == A_KEY)
	{
		if (dt->player.pos.x - STEP >= 0)
		{
			dt->player.step_count++;
			dt->player.pos.x -= STEP;
		}
	}
	else if (keycode == D_KEY)
	{
		if (dt->player.pos.x < (float)dt->maze.width)
		{
			dt->player.step_count++;
			dt->player.pos.x += STEP;
		}
	}
	return (0);
}

int	draw_buffer_image(t_data *dt)
{
	int				tot_len;
	int				i;
	int				x;
	int				y;
	int				res;
	struct timeval	act_time;

	if (!dt->mlx_ptr || !dt->win_ptr)
		return (printf("Error: Invalid data pointers\n"), 1);
	tot_len = dt->maze.width * dt->maze.height;
	i = -1;
	while (++i < tot_len)
	{
		x = i % dt->maze.width;
		y = i / dt->maze.width;
		if (dt->maze.mat[i] == 0)
			res = mlx_xpm_cpy_src_in_dst(&dt->img_floor, &dt->img_buffer, x * TILE_X, y * TILE_Y);
		else if (dt->maze.mat[i] == 1)
			res = mlx_xpm_cpy_src_in_dst(&dt->img_wall, &dt->img_buffer, x * TILE_X, y * TILE_Y);
		else
			res = 1;
		if (res)
			return (fprintf(stderr, "Error draw_buffer_image() failed\n"),
					mlx_loop_end(dt->mlx_ptr), 1);
	}
	draw_player(&dt->img_buffer, &dt->player);
	if (gettimeofday(&act_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	if (dt->img_drawn)
	{
		while (diff_time_in_ms(dt->last_frame_time, act_time) < dt->delay_between_frames_ms)
		{
			if (gettimeofday(&act_time, NULL) < 0)
				return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
		}
	}
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_buffer.img_ptr, 0, 0);
	dt->img_drawn++;
	if (gettimeofday(&dt->last_frame_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	return (0);
}
