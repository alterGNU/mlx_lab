/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:08:27 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/08 17:07:40 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
//-[ Key definitions ]----------------------------------------------------------
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define Q_KEY 113
# define E_KEY 101
# define LA_KEY 65361
# define RA__KEY 65363
//-[ Variables ]----------------------------------------------------------------
# define VALID_MAZE_CHARS "01NSEW"
# define M_PI 3.1415926535
//-[ Window ]-------------------------------------------------------------------
# define WIN_TITLE "Ray-Charle's Ghost: blind red-dot (No ray-casting)"
# define TILE_X 64 // width of one cell in pixels
# define TILE_Y 64 // height of one cell in pixels
//-[ Colors ]-------------------------------------------------------------------
# define BLACK_COLOR 0x000000
# define RED_COLOR 0xFF0000
# define GREEN_COLOR 0x00FF00
# define BLUE_COLOR 0x0000FF
# define YELLOW_COLOR 0xFFFF00
# define WHITE_COLOR 0xFFFFFF
# define FLOOR_COLOR 0xAAAAAA
# define WALL_COLOR 0x333333
//-[ Player ]-------------------------------------------------------------------
# define CIRCLE_RADIUS 8 // size of the player representation
// -[ Engine ]------------------------------------------------------------------
# define POS_SPEED 0.1f	// Position Var. Speed==movement-speed:step/move
# define ANG_SPEED 3.1f	// Angle Var. Speed==rotation-speed:degree/move
# define FPS 60 // desired frames per second
// =[ Include ]=================================================================
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
// =[ Structures ]==============================================================
typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_play
{
	t_pos	pos;
	float	dir;
	int		color;
	int		radius;
	int		step_count;
	char	*play_str;
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
	t_img			img_info;
	t_img			img_floor;
	t_img			img_wall;
	t_img			img_grid;
	t_img			img_buffer;
	int				img_drawn;
	int				delay_between_frames_ms;
	struct timeval	last_frame_time;
	struct timeval	time_start_fps_inter;
	int				nbf_start_fps_inter;
	char			fps_str[32];
}	t_data;
// =[ Files & Fun. Signatures ]=================================================
// -[ draw_to_img.c ]----------------------------------------------------------5
void	put_pixel_to_image(t_img *img, int x, int y, int color);			// ✅
void	draw_circle(t_img *img, t_pos c_pos, int r, int color);				// ✅
void	draw_dda_line(t_img *img, t_pos a_pos, t_pos b_pos, int color);		// ✅
void	draw_vector(t_img *img, t_pos start, t_pos vec, int color);			// ✅
// -[ hooked_funs.c ]----------------------------------------------------------2
int		handle_key(int keycode, t_data *dt);								// ❌
int		draw_buffer_image(t_data *dt);										// ❌
// -[ memcpy_utils.c ]--------------------------------------------------------2
void	*ft_memcpy(void *dst, const void *src, size_t len);					// ✅
void	*ft_memcpy_by_words(void *dst, const void *src, size_t len);		// ✅
// -[ t_data_struct.c ]--------------------------------------------------------5
t_data	init_data(const char **str_arr);									// ✅
void	free_data(t_data *dt);												// ✅
int		error_detected_after_init_data(t_data *dt);							// ✅
// -[ t_img_builders.c ]-------------------------------------------------------3
int		build_img_floor(t_img *img);										// ✅
int		build_img_wall(t_img *img);											// ✅
int		build_img_grid(t_maze *maze, t_img *grid, t_img *floor, t_img *wall);//✅
// -[ t_img_struct.c ]---------------------------------------------------------5
void	memset_zero_img(t_img *img);										// ✅
t_img	create_image(void *mlx_ptr, int width, int height);					// ✅
void	print_t_img(t_img img);												// ✅
void	free_image(t_img img, void *mlx_ptr);								// ✅
int		is_img_valid(t_img *img);											// ✅
// -[ t_img_duplicate.c ]------------------------------------------------------2
void	copy_t_img_metadata(t_img *src, t_img *dst);						// ✅
int		dup_t_img_by_words(t_img *src, t_img *dst);							// ✅
// -[ t_img_insert.c ]---------------------------------------------------------1
int		t_img_insert_rows_by_words(\
		t_img *src, t_img *dst, int dst_x, int dst_y);						// ✅
// -[ t_maze_struct.c ]--------------------------------------------------------3
t_maze	set_maze_and_player(const char **str_arr, t_play *player);			// ❌
void	free_maze(t_maze *maze);											// ✅
void	print_maze(t_maze maze);											// ✅
// -[ t_player_struct.c ]------------------------------------------------------5
t_play	init_player(void);													// ✅
void	set_player(t_play *play, float x, float y, float dir);				// ✅
int		print_player(t_play play);											// ✅
void	draw_player(t_img *img, t_play *player);							// ✅
void	free_player(t_play *player);										// ✅
// -[ t_pos_struct.c ]---------------------------------------------------------4
t_pos	init_pos(float x, float y);											// ✅
t_pos	set_pos(t_pos *pos, float x, float y);								// ✅
int		print_pos(t_pos pos);												// ✅
t_pos	dup_pos(t_pos src);													// ✅
// -[ utils.c ]----------------------------------------------------------------3
int		char_in_str(char c, const char *str);								// ✅
void	print_str_array(const char **str_arr);								// ✅
int		diff_time_in_ms(struct timeval start, struct timeval end);			// ✅
int		convert_fps_to_frame_delay(int fps);								// ✅
// -[ utils_math.c ]-----------------------------------------------------------3
float	radian(float degree);												// ✅
int		ft_max(int a, int b);												// ✅
float	norm_angle(float angle);											// ✅
#endif