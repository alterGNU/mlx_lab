/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:14:41 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/12 19:56:44 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	display_player_infos(t_data *dt)
{
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_2d_ptr, \
		dt->img_erase_txt.img_ptr, 0, 0);
	mlx_string_put(dt->mlx_ptr, dt->win_2d_ptr, 10, 12, WHITE_COLOR, \
		dt->player.play_str);
}

void	display_fps_infos(t_data *dt)
{
	int		win_x;
	float	fps;
	int		delta_ms;

	win_x = dt->maze.width * TILE_X + 10;
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_2d_ptr, \
		dt->img_erase_txt.img_ptr, win_x - 70, 0);
	delta_ms = diff_time_in_ms(dt->fps_start_inter, dt->last_frame_time);
	fps = 0.f;
	if (delta_ms)
		fps = FPS_DELTA * 1000.f / (float)delta_ms;
	snprintf(dt->fps_str, sizeof(dt->fps_str), "FPS: %.2f", fps);
	mlx_string_put(dt->mlx_ptr, dt->win_2d_ptr, win_x - 70, 12, WHITE_COLOR, \
		dt->fps_str);
}

void	display_hits_infos(t_data *dt)
{
	int		i;
	char	xray_str[64];
	int		txt_x;
	int		txt_y;

	txt_x = dt->player.pos.x * TILE_X - 270;
	if (txt_x < 0)
		txt_x = dt->player.pos.x * TILE_X + CIRCLE_RADIUS + 10;
	txt_y = dt->player.pos.y * TILE_Y - 3 * get_nb_of_rays();
	i = -1;
	while (dt->hits[++i].valid)
	{
		snprintf(xray_str, sizeof(xray_str), "hits[%d]:pos(%.2f, %.2f), ang:(%.2f, %.2f)", \
			i, dt->hits[i].pos.x, dt->hits[i].pos.y, dt->hits[i].angle.x, dt->hits[i].angle.y);
		mlx_string_put(dt->mlx_ptr, dt->win_2d_ptr, txt_x, txt_y + 12 * (i + 1), \
			RED_COLOR, xray_str);
	}
}
