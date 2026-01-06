/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooked_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:25:21 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/06 20:59:48 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static float	radian(float degree)
{
	return (degree * (M_PI / 180.0f));
}

int	handle_key(int keycode, t_data *dt)
{
	if (keycode == ESC_KEY)
		return (mlx_loop_end(dt->mlx_ptr), 1);
	else if (keycode == W_KEY)
	{
		dt->player.pos.x += cosf(radian(dt->player.dir)) * SPEED;
		dt->player.pos.y -= sinf(radian(dt->player.dir)) * SPEED;
		dt->player.step_count++;
	}
	else if (keycode == S_KEY)
	{
		dt->player.pos.x += cosf(radian(dt->player.dir)) * -SPEED;
		dt->player.pos.y -= sinf(radian(dt->player.dir)) * -SPEED;
		dt->player.step_count++;
	}
	else if (keycode == A_KEY)
	{
		dt->player.pos.x += cosf(radian(dt->player.dir - 90)) * -SPEED;
		dt->player.pos.y += sinf(radian(dt->player.dir - 90)) * -SPEED;
		dt->player.step_count++;
	}
	else if (keycode == D_KEY)
	{
		dt->player.pos.x += cosf(radian(dt->player.dir + 90)) * -SPEED;
		dt->player.pos.y += sinf(radian(dt->player.dir + 90)) * -SPEED;
		dt->player.step_count++;
	}
	else if (keycode == Q_KEY || keycode == LA_KEY)
	{
		dt->player.dir += ROT_STEP;
		if (dt->player.dir >= 360.0)
			dt->player.dir -= 360.0;
	}
	else if (keycode == E_KEY || keycode == RA__KEY)
	{
		dt->player.dir -= ROT_STEP;
		if (dt->player.dir < 0.0)
			dt->player.dir += 360.0;
	}
	return (0);
}

//static void	update_play_dir_string(t_data *dt)
//{
//	if (dt->play_dir)
//		free(dt->play_dir);
//	dt->play_dir = strdup("000 degrees");
//	dt->play_dir[0] = '0' + ((int)dt->player.dir / 100) % 10;
//	dt->play_dir[1] = '0' + ((int)dt->player.dir / 10) % 10;
//	dt->play_dir[2] = '0' + ((int)dt->player.dir) % 10;
//}

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
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_buffer.img_ptr, 0, 0);
	//update_play_dir_string(dt);
	//mlx_string_put(dt->mlx_ptr, dt->win_ptr, 10, 10, WHITE_COLOR, dt->play_dir);
	dt->img_drawn++;
	if (gettimeofday(&dt->last_frame_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	return (0);
}
