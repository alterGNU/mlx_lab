/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooked_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:25:21 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 11:03:04 by lagrondi         ###   ########.fr       */
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

static int	switch_duplicate_method(t_data *dt)
{
	if (mem_block_type == 0)
		return (dup_t_img_by_bits(&dt->img_grid, &dt->img_buffer));
	else if (mem_block_type == 1)
		return (dup_t_img_by_bytes(&dt->img_grid, &dt->img_buffer));
	else if (mem_block_type == 2)
		return (dup_t_img_by_words(&dt->img_grid, &dt->img_buffer));
	else
		return (dup_t_img_memcpy(&dt->img_grid, &dt->img_buffer));
}

int	draw_buffer_image(t_data *dt)
{
	struct timeval	act_time;

	if (!dt->mlx_ptr || !dt->win_ptr)
		return (printf("Error: Invalid data pointers\n"), 1);
	if (gettimeofday(&act_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	if (!switch_duplicate_method(dt))
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
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_buffer.img_ptr, 0, 0);
	dt->img_drawn++;
	if (gettimeofday(&dt->last_frame_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	return (0);
}
