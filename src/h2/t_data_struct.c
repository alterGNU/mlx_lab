/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:20:43 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/04 19:25:09 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	zero_memset_data(t_data *dt)
{
	dt->player = (t_play){{0.0f, 0.0f}, 0, 0, 0};
	dt->maze = (t_maze){NULL, 0, 0};
	dt->mlx_ptr = NULL;
	dt->win_ptr = NULL;
	dt->img_floor = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	dt->img_wall = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	dt->img_buffer = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	dt->img_drawn = 0;
	dt->delay_between_frames_ms = convert_fps_to_frame_delay(FPS);
	memset(&dt->last_frame_time, 0, sizeof(struct timeval));
}

t_data	init_data(const char **str_arr)
{
	t_data	dt;
	int		win_x;
	int		win_y;

	zero_memset_data(&dt);
	dt.player = init_player();
	dt.maze = set_maze_and_player(str_arr, &dt.player);
	dt.mlx_ptr = mlx_init();
	if (!dt.mlx_ptr)
		return (dt);
	win_x = dt.maze.width * TILE_X;
	win_y = dt.maze.height * TILE_Y;
	if (win_x <= 0 || win_y <= 0)
		return (dt);
	dt.win_ptr = mlx_new_window(dt.mlx_ptr, win_x, win_y, WIN_TITLE);
	if (!dt.win_ptr)
		return (dt);
	dt.img_floor = ft_load_image(dt.mlx_ptr, FLOOR_XPM);
	dt.img_wall = ft_load_image(dt.mlx_ptr, WALL_XPM);
	dt.img_buffer = ft_create_buffer_image(dt.mlx_ptr, win_x, win_y);
	dt.img_drawn = 0;
	return (dt);
}

void	free_data(t_data *dt)
{
	free_maze(&dt->maze);
	free_image(dt->img_floor, dt->mlx_ptr);
	free_image(dt->img_wall, dt->mlx_ptr);
	free_image(dt->img_buffer, dt->mlx_ptr);
	if (dt->win_ptr)
	{
		mlx_destroy_window(dt->mlx_ptr, dt->win_ptr);
		dt->win_ptr = NULL;
	}
	if (dt->mlx_ptr)
	{
		mlx_destroy_display(dt->mlx_ptr);
		free(dt->mlx_ptr);
		dt->mlx_ptr = NULL;
	}
}

static void	check_ptr_not_null(void *ptr, const char *ptr_name, int *error)
{
	if (!ptr)
	{
		fprintf(stderr, "data->%s not initialized\n", ptr_name);
		(*error)++;
	}
}

int	error_detected_after_init_data(t_data *dt)
{
	int	error;

	error = 0;
	if (dt->player.pos.x < 0.0 || dt->player.pos.y < 0.0 || \
		dt->player.radius <= 0 || dt->player.step_count)
	{
		fprintf(stderr, "data->player init invalid: play{pos(%f, %f), ", \
			dt->player.pos.x, dt->player.pos.y);
		fprintf(stderr, "radius:%d, step_count:%d}\n", \
			dt->player.radius, dt->player.step_count);
		error++;
	}
	if (dt->maze.width <= 0 || dt->maze.height <= 0 || !dt->maze.mat)
	{
		fprintf(stderr, "data->maze init invalid: maze{width:%d, height:%d, ",
			dt->maze.width, dt->maze.height);
		fprintf(stderr, "mat:NULL}\n");
		error++;
	}
	check_ptr_not_null(dt->mlx_ptr, "mlx", &error);
	check_ptr_not_null(dt->win_ptr, "win", &error);
	check_ptr_not_null(dt->img_floor.img_ptr, "img_floor", &error);
	check_ptr_not_null(dt->img_wall.img_ptr, "img_wall", &error);
	check_ptr_not_null(dt->img_buffer.img_ptr, "img_buffer", &error);
	return (error);
}
