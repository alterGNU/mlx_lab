/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/10 12:35:58 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_all_hit_lines(t_data *dt)
{
	int		i;
	t_pos	play_pos;
	t_pos	hit_tpos;
	char	xray_str[64];

	play_pos = init_pos(dt->player.pos.x * TILE_X, dt->player.pos.y * TILE_Y);
	i = -1;
	while (dt->hits[++i].valid)
	{
		hit_tpos = init_pos(dt->hits[i].pos.x * TILE_X, dt->hits[i].pos.y * TILE_Y);
		draw_dda_line(&dt->img_buffer, play_pos, hit_tpos, GREEN_COLOR);
		snprintf(xray_str, sizeof(xray_str), "hit_pos[%d]: (%.2f, %.2f)", i, dt->hits[i].pos.x, dt->hits[i].pos.y);
		mlx_string_put(dt->mlx_ptr, dt->win_ptr, 40, 40 * (i + 1), BLACK_COLOR, xray_str);
	}
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
	draw_all_hit_lines(dt); // third layer:ray-cast hit lines TODO: move to line 44!!!!!!!
	// FPS control to avoid busy-spinning
	if (dt->img_drawn)
	{
		while (diff_time_in_ms(dt->last_frame_time, act_time) < dt->delay_between_frames_ms)
		{
			if (gettimeofday(&act_time, NULL) < 0)
				return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
		}
	}
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_buffer.img_ptr, 5, 20);
	dt->img_drawn++;
	if (gettimeofday(&dt->last_frame_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	return (0);
}
