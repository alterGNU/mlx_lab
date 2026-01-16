/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/16 02:14:29 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw2d_player(t_img *img, t_play *p)
{
	t_pos	center;
	t_pos	angle_speed;

	center = init_pos(p->pos.x * TILE_X, p->pos.y * TILE_Y);
	angle_speed = init_pos(p->dir, p->radius * 3);
	draw_circle(img, center, p->radius, p->color);
	draw_vector(img, center, angle_speed, BLUE_COLOR);
}


/**
 * TODO: here lines `hit = init_pos(...)` could be optimized using prod_fpos(t_fpos a, t_fpos b) 
 *   --> hit = prod_fpos(dt->hits[i].pos, init_fpos(TILE_X, TILE_Y));
 */
void	draw2d_hit_lines(t_data *dt)
{
	int		i;
	t_pos	player;
	t_pos	hit;

	if (DRAW_2D_RAYS)
	{
		player = init_pos(dt->player.pos.x * TILE_X, dt->player.pos.y * TILE_Y);
		if (DRAW_2D_RAYS == 1)
		{
			hit = init_pos(dt->hits[0].pos.x * TILE_X, dt->hits[0].pos.y * TILE_Y);
			draw_dda_line(&dt->img_2d_buffer, player, hit, GREEN_COLOR);
			i = dt->nb_of_rays - 1;
			hit = init_pos(dt->hits[i].pos.x * TILE_X, dt->hits[i].pos.y * TILE_Y);
			draw_dda_line(&dt->img_2d_buffer, player, hit, GREEN_COLOR);
		}
		else
		{
			i = -1;
			while (dt->hits[++i].valid)
			{
				hit = init_pos(dt->hits[i].pos.x * TILE_X, dt->hits[i].pos.y * TILE_Y);
				draw_dda_line(&dt->img_2d_buffer, player, hit, GREEN_COLOR);
			}
		}
	}
}

void	draw3d_v_lines(t_data *dt)
{
	int		i;
	int		j;
	float	corrected_dist;
	int		y_start;
	int		y_stop;

	i = -1;
	while (dt->hits[++i].valid)
	{
		corrected_dist = dt->hits[i].distance * cos(radian(dt->player.dir - dt->hits[i].angle.x));
		y_start = (dt->img_3d_buffer.height / 2) * (1 + DIST_MIN / corrected_dist);
		y_stop = (dt->img_3d_buffer.height / 2) * (1 - DIST_MIN / corrected_dist);
		j = -1;
		while (++j < dt->column_width)
			draw_vline(&dt->img_3d_buffer, i * dt->column_width + j, y_start, y_stop, RED_COLOR);
	}
}

int	draw_buffer_images(t_data *dt)
{
	struct timeval	act_time;

	if (!dt->mlx_ptr || !dt->win_ptr)
		return (printf("Error: Invalid data pointers\n"), 1);
	if (gettimeofday(&act_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	if (!dup_t_img_by_words(&dt->img_2d_template, &dt->img_2d_buffer))
		return (fprintf(stderr, "Error: dup_t_img(2d) failed\n"), free_data(dt), 1);
	draw2d_hit_lines(dt);
	draw2d_player(&dt->img_2d_buffer, &dt->player); // second layer:player
	if (!dup_t_img_by_words(&dt->img_3d_template, &dt->img_3d_buffer))
		return (fprintf(stderr, "Error: dup_t_img(3d) failed\n"), free_data(dt), 1);
	draw3d_v_lines(dt);
	// FPS control to avoid busy-spinning
	if (dt->img_drawn)
	{
		while (diff_time_in_ms(dt->last_frame_time, act_time) < dt->delay_between_frames_ms)
		{
			if (gettimeofday(&act_time, NULL) < 0)
				return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
		}
	}
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_2d_buffer.img_ptr, dt->start2d.x, dt->start2d.y);
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_3d_buffer.img_ptr, dt->start3d.x, dt->start3d.y);
	dt->img_drawn++;
	if (gettimeofday(&dt->last_frame_time, NULL) < 0)
		return (perror("draw_buffer_image: gettimeofday() failed"), free_data(dt), 1);
	return (0);
}
