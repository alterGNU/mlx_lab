/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:08:27 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/04 21:43:18 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define WIN_TITLE "Moving player with int flag (busy-spin-loop)"
# define TILE_X 32
# define TILE_Y 32
# define FLOOR_XPM "./docs/floor.xpm"
# define WALL_XPM "./docs/wall.xpm"
# define VALID_MAZE_CHARS "01P"
# define RED_COLOR 0xFF0000
# define CIRCLE_RADIUS 8
# define STEP 0.1f
# define FPS 60

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_play
{
	t_pos	pos;
	int		color;
	int		radius;
	int		step_count;
}	t_play;

typedef struct s_maze
{
	int		*mat;
	int		width;
	int		height;
}	t_maze;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_data
{
	t_play			player;
	t_maze			maze;
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img_floor;
	t_img			img_wall;
	t_img			img_buffer;
	int				img_drawn;
	int				delay_between_frames_ms;
	struct timeval	last_frame_time;
}	t_data;

// draw_to_img.c
void	put_pixel_to_image(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, int x, t_pos pos, int color);
void	draw_circle(t_img *img, t_pos c_pos, int r, int color);

// hooked_funs.c
int		handle_key(int keycode, t_data *dt);
int		draw_buffer_image(t_data *dt);

// t_data_struct.c
t_data	init_data(const char **str_arr);
void	free_data(t_data *dt);
int		error_detected_after_init_data(t_data *dt);

// t_img_struct.c
t_img	ft_load_image(void *mlx_ptr, const char *filename);
t_img	ft_create_buffer_image(void *mlx_ptr, int width, int height);
void	free_image(t_img img, void *mlx_ptr);

// t_maze_struct.c
t_maze	set_maze_and_player(const char **str_arr, t_play *player);
void	free_maze(t_maze *maze);
void	print_maze(t_maze maze);

// t_player_struct.c
t_play	init_player(void);
int		print_player(t_play play);
void	draw_player(t_img *img, t_play *player);

// t_pos_struct.c
t_pos	init_pos(float x, float y);
t_pos	set_pos(t_pos *pos, float x, float y);
int		print_pos(t_pos pos);
t_pos	dup_pos(t_pos src);

// utils.c
int		char_in_str(char c, const char *str);
void	print_str_array(const char **str_arr);
int		mlx_xpm_cpy_src_in_dst(t_img *src, t_img *dst, int dst_x, int dst_y);
int		diff_time_in_ms(struct timeval start, struct timeval end);
int		convert_fps_to_frame_delay(int fps);
#endif