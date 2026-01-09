/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:14:41 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/09 14:29:33 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	display_player_infos(t_data *dt)
{
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, \
		dt->img_erase_txt.img_ptr, 0, 0);
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 10, 12, WHITE_COLOR, \
		dt->player.play_str);
}

void	display_fps_infos(t_data *dt)
{
	int		win_x;
	float	fps;
	int		delta_ms;

	win_x = dt->maze.width * TILE_X + 10;
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, \
		dt->img_erase_txt.img_ptr, win_x - 70, 0);
	delta_ms = diff_time_in_ms(dt->fps_start_inter, dt->last_frame_time);
	fps = 0.f;
	if (delta_ms)
		fps = FPS_DELTA * 1000.f / (float)delta_ms;
	snprintf(dt->fps_str, sizeof(dt->fps_str), "FPS: %.2f", fps);
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, win_x - 70, 12, WHITE_COLOR, \
		dt->fps_str);
}
