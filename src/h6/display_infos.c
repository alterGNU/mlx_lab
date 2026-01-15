/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:14:41 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/15 23:35:35 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	display_player_infos(t_data *dt, int line_num)
{
	int		y;

	y = 5 + 12 * line_num;
	mlx_put_image_to_window(\
		dt->mlx_ptr, dt->win_ptr, dt->img_erase_txt.img_ptr, 5, y - 6);
	mlx_string_put(\
		dt->mlx_ptr, dt->win_ptr, 5, y + 6, WHITE_COLOR, dt->player.play_str);
}

void	display_fps_infos(t_data *dt, int line_num)
{
	int		y;
	float	fps;
	int		delta_ms;
	int		coloration;

	y = 5 + 12 * line_num;
	delta_ms = diff_time_in_ms(dt->fps_start_inter, dt->last_frame_time);
	fps = 0.f;
	if (delta_ms)
		fps = FPS_DELTA * 1000.f / (float)delta_ms;
	snprintf(dt->fps_str, sizeof(dt->fps_str), "FPS: %.2f ---> player have %d rays", fps, dt->nb_of_rays);
	coloration = GREEN_COLOR;
	if (fps < 50.f)
		coloration = RED_COLOR;
	mlx_put_image_to_window(\
		dt->mlx_ptr, dt->win_ptr, dt->img_erase_txt.img_ptr, 5, y - 6);
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 5, y + 6, coloration, dt->fps_str);
}

void	display_hits_infos(t_data *dt, int line_num)
{
	int		i;
	int		y;
	char	xray_str[64];

	y = 5 + 12 * line_num;
	i = -1;
	while (dt->hits[++i].valid && y + 12 <= dt->start2d.y)
	{
		snprintf(xray_str, sizeof(xray_str), \
			"h[%d]:p(%.2f, %.2f), a:%.2f, d:%.2f", i, dt->hits[i].pos.x, \
			dt->hits[i].pos.y, dt->hits[i].angle.x, dt->hits[i].distance);
		mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, \
			dt->img_erase_txt.img_ptr, 5, y - 6);
		mlx_string_put(dt->mlx_ptr, dt->win_ptr, 5, y + 6, WHITE_COLOR, xray_str);
		y += 12;
	}
}
