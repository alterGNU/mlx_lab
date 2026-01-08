/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/08 18:34:59 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// TODO: rename to display_player_infos()
void	display_debug_infos(t_data *dt)
{
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_erase_txt.img_ptr, 0, 0);
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 10, 12, WHITE_COLOR, dt->player.play_str);
}

int	display_fps_infos(t_data *dt)
{
	struct timeval	act_time;
	int				win_x;
	float			fps;

	if (gettimeofday(&act_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	if (dt->img_drawn % FPS == 0)
	{
		// diff_time_in_ms returns milliseconds; convert to seconds for FPS
		fps = FPS * 1000.f / diff_time_in_ms(dt->time_start_fps_inter, act_time);
		snprintf(dt->fps_str, sizeof(dt->fps_str), "FPS: %.2f", fps);
		if (gettimeofday(&dt->time_start_fps_inter, NULL) < 0) // same as: dt->time_start_fps_inter = act_time;
			return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
		dt->nbf_start_fps_inter = dt->img_drawn;
		win_x = dt->maze.width * TILE_X + 10;
		mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_erase_txt.img_ptr, win_x - 70, 0);
		mlx_string_put(dt->mlx_ptr, dt->win_ptr, win_x - 70, 12, WHITE_COLOR, dt->fps_str);
	}
	return (0);
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
	// FPS control to avoid busy-spinning
	if (dt->img_drawn)
	{
		while (diff_time_in_ms(dt->last_frame_time, act_time) < dt->delay_between_frames_ms)
		{
			if (gettimeofday(&act_time, NULL) < 0)
				return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
		}
	}
	//----------------------------
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_buffer.img_ptr, 5, 20);
	display_debug_infos(dt);
	display_fps_infos(dt);
	dt->img_drawn++;
	// same as dt->last_frame_time = act_time;
	if (gettimeofday(&dt->last_frame_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	return (0);
}
