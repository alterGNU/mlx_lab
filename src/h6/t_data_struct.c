/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:20:43 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/17 02:08:15 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	zero_memset_data(t_data *dt)
{
	dt->player = (t_play){{0.0f, 0.0f}, 0.0f, 0, 0, -1, NULL};
	dt->maze = (t_maze){NULL, 0, 0, 0};
	dt->mlx_ptr = NULL;
	dt->win_ptr = NULL;
	dt->win_dim = (t_fpos){0.0f, 0.0f};
	dt->img_erase_txt = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	dt->img_2d_floor = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	dt->img_2d_wall = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	dt->img_2d_template = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	dt->img_2d_buffer = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	dt->img_3d_template = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	dt->img_3d_buffer = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	dt->img_drawn = 0;
	dt->start2d = (t_fpos){0.0f, 0.0f};
	dt->start3d = (t_fpos){0.0f, 0.0f};
	dt->delay_between_frames_ms = convert_fps_to_frame_delay(FPS);
	memset(&dt->last_frame_time, 0, sizeof(struct timeval));
	memset(&dt->fps_start_inter, 0, sizeof(struct timeval));
	memset(dt->fps_str, 0, sizeof(dt->fps_str));
	memset(dt->mv_flags, 0, sizeof(dt->mv_flags));
	dt->rot_elem = 0.0f;
	dt->nb_of_rays = 0;
	dt->hits = NULL;
}

t_data	init_data(const char **str_arr)
{
	t_data	dt;
	int		map2d_x;
	int		map2d_y;
	int		img3d_width;

	zero_memset_data(&dt);
	init_movement_flags(&dt);
	dt.player = init_player();
	dt.maze = set_maze_and_player(str_arr, &dt.player);
	dt.mlx_ptr = mlx_init();
	if (!dt.mlx_ptr)
		return (dt);
	map2d_x = dt.maze.width * TILE_X;
	map2d_y = dt.maze.height * TILE_Y;
	if (map2d_x <= 0 || map2d_y <= 0)
		return (dt);
	dt.nb_of_rays = get_nb_of_rays();
	if (dt.nb_of_rays > 1)
		dt.rot_elem = FOV / (dt.nb_of_rays - 1);
	//if (FOV > FOV_PRE)
	//	dt.rot_elem = FOV * FOV_PRE / (FOV - FOV_PRE);
	dt.column_width = (int)(IMG3D_WIDTH / dt.nb_of_rays);
	img3d_width = dt.nb_of_rays * dt.column_width;
	dt.win_dim.x = ft_imax(map2d_x, WIN_DBG_TXT_LEN) + img3d_width + 3 * WIN_BORDER;
	dt.win_dim.y = ft_imax(map2d_y + WIN_DBG_TXT_LEN + 3 * WIN_BORDER, IMG3D_HEIGHT + 2 * WIN_BORDER);
	if (dt.win_dim.x <= 0 || dt.win_dim.y <= 0)
		return (dt);
	set_fpos(&dt.start2d, 5.0f, (float)dt.win_dim.y - (float)map2d_y - 5.0f);
	set_fpos(&dt.start3d, (float)dt.win_dim.x - (float)img3d_width - 5.0f, 5.0f);
	dt.win_ptr = mlx_new_window(dt.mlx_ptr, dt.win_dim.x, dt.win_dim.y, WIN_TITLE);
	if (!dt.win_ptr)
		return (dt);
	dt.img_erase_txt = create_image(dt.mlx_ptr, ft_imax(map2d_x, WIN_DBG_TXT_LEN), 14);
	dt.img_2d_floor = create_image(dt.mlx_ptr, TILE_X, TILE_Y);
	dt.img_2d_wall = create_image(dt.mlx_ptr, TILE_X, TILE_Y);
	dt.img_2d_template = create_image(dt.mlx_ptr, map2d_x, map2d_y);
	dt.img_2d_buffer = create_image(dt.mlx_ptr, map2d_x, map2d_y);
	dt.hits = create_hit_array(dt.nb_of_rays);
	dt.img_3d_template = create_image(dt.mlx_ptr, img3d_width, IMG3D_HEIGHT);
	dt.img_3d_buffer = create_image(dt.mlx_ptr, img3d_width, IMG3D_HEIGHT);
	return (dt);
}

void	free_data(t_data *dt)
{
	free_hit_array(&dt->hits);
	free_player(&dt->player);
	free_maze(&dt->maze);
	free_image(dt->img_erase_txt, dt->mlx_ptr);
	free_image(dt->img_2d_floor, dt->mlx_ptr);
	free_image(dt->img_2d_wall, dt->mlx_ptr);
	free_image(dt->img_2d_template, dt->mlx_ptr);
	free_image(dt->img_2d_buffer, dt->mlx_ptr);
	free_image(dt->img_3d_template, dt->mlx_ptr);
	free_image(dt->img_3d_buffer, dt->mlx_ptr);
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
	if (!dt->player.play_str)
	{
		fprintf(stderr, "data->player.play_str=NULL, calloc() failed\n");
		error++;
	}
	if (dt->player.pos.x < 0.0 || dt->player.pos.y < 0.0 ||
		dt->player.radius <= 0 || dt->player.step_count < 0)
	{
		fprintf(stderr, "data->player init invalid: play{pos(%.2f, %.2f), ",
				dt->player.pos.x, dt->player.pos.y);
		fprintf(stderr, "radius:%d, step_count:%d}\n",
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
	if ((int)dt->win_dim.x <= 0 || (int)dt->win_dim.y <= 0)
	{
		fprintf(stderr, "data->win_dim init invalid: win{width:%d, height:%d, ",
				(int)dt->win_dim.x, (int)dt->win_dim.y);
		fprintf(stderr, "mat:NULL}\n");
		error++;
	}
	check_ptr_not_null(dt->mlx_ptr, "mlx_ptr", &error);
	check_ptr_not_null(dt->win_ptr, "win_ptr", &error);
	check_ptr_not_null(dt->img_erase_txt.img_ptr, "img_erase_txt", &error);
	check_ptr_not_null(dt->img_2d_floor.img_ptr, "img_2d_floor", &error);
	check_ptr_not_null(dt->img_2d_wall.img_ptr, "img_2d_wall", &error);
	check_ptr_not_null(dt->img_2d_template.img_ptr, "img_2d_template", &error);
	check_ptr_not_null(dt->img_2d_buffer.img_ptr, "img_2d_buffer", &error);
	check_ptr_not_null(dt->img_3d_template.img_ptr, "img_3d_template", &error);
	check_ptr_not_null(dt->img_3d_buffer.img_ptr, "img_3d_buffer", &error);
	return (error);
}
