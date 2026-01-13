/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/13 21:54:42 by lagrondi         ###   ########.fr       */
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


void	draw2d_hit_lines(t_data *dt)
{
	int		i;
	t_pos	play_pos;
	t_pos	hit_tpos;

	play_pos = init_pos(dt->player.pos.x * TILE_X, dt->player.pos.y * TILE_Y);
	i = -1;
	while (dt->hits[++i].valid)
	{
		hit_tpos = init_pos(dt->hits[i].pos.x * TILE_X, dt->hits[i].pos.y * TILE_Y);
		draw_dda_line(&dt->img_2d_buffer, play_pos, hit_tpos, GREEN_COLOR);
	}
}

//void	draw3d_v_lines(t_data *dt)
//{
//	int		i;
//	int		j;
//	float	wall_height;
//	t_pos	a;
//	t_pos	b;
//
//	i = -1;
//	while (dt->hits[++i].valid)
//	{
//		wall_height = (dt->maze.cell_nb * dt->img_3d_buffer.height) / dt->hits[i].distance;
//		if (wall_height > dt->img_3d_buffer.height)
//			wall_height = dt->img_3d_buffer.height;
//		j = 0;
//		while (++j <  8)
//		{
//			a = init_pos(i + j, (dt->img_3d_buffer.height - wall_height) / 2);
//			b = init_pos(i + j, (dt->img_3d_buffer.height + wall_height) / 2);
//			draw_dda_line(&dt->img_3d_buffer, a, b, RED_COLOR);
//		}
//	}
//}
void	draw3d_v_lines(t_data *dt)
{
	int		i;
	int		j;
	float	wall_height;
	float	corrected_dist;
	int		screen_h;
	int		top;
	int		bottom;
	t_pos	a;
	t_pos	b;

	screen_h = dt->img_3d_buffer.height;
	i = -1;
	while (dt->hits[++i].valid)
	{
		/* fisheye correction */
		corrected_dist = dt->hits[i].distance
			* cos(dt->hits[i].angle - dt->player.dir);

		wall_height = (dt->maze.cell_nb * screen_h) / corrected_dist;
		if (wall_height > screen_h)
			wall_height = screen_h;

		top = (screen_h / 2) - (wall_height / 2);
		bottom = top + wall_height;

		j = -1;
		while (++j < 8) /* wall thickness */
		{
			a.x = i * 8 + j;
			a.y = top;
			b.x = i * 8 + j;
			b.y = bottom;

			draw_dda_line(&dt->img_3d_buffer, a, b, RED_COLOR);
		}
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
	if (!dup_t_img_by_words(&dt->img_3d_template, &dt->img_3d_buffer))
		return (fprintf(stderr, "Error: dup_t_img(3d) failed\n"), free_data(dt), 1);
	draw3d_v_lines(dt);
	draw2d_hit_lines(dt);
	draw2d_player(&dt->img_2d_buffer, &dt->player); // second layer:player
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
