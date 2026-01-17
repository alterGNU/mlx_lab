/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:08:27 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/16 17:13:37 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
// -[ Debug/UI toggles ]--------------------------------------------------------
# define DRAW_HITS_TXT 0		// 0: disable, 1: enable hit positions display
# define DRAW_2DIMG 0			// 0: do not draw 2d image (map), else: draw it
# define DRAW_2D_RAYS 2			// 0: none, 1: first/last, 2: all rays
//-[ Window ]-------------------------------------------------------------------
# define WIN_TITLE "Caster the Ghost: (3D Monochrome-RayCasting)"
# define WIN_BORDER 5			// space between window border & images
# define WIN_DBG_TXT_LEN 250	// length(in pixels)of debug txt area
//-[ 2DImage ]------------------------------------------------------------------
# define TILE_X 16 				// width(in pixels) of one 2Dcell
# define TILE_Y 16 				// height(in pixels) of one 2Dcell
# define CIRCLE_RADIUS 8		// size of the player representation
//-[ 3DImage ]------------------------------------------------------------------
// TODO: replace by resolution
# define IMG3D_WIDTH 2048
# define IMG3D_HEIGHT 1024
# define FLOOR_RGB 0x00FF00
# define CEIL_RGB 0x0000FF
// -[ Engine ]------------------------------------------------------------------
# define POS_SPEED .1f		// Position Var. Speed==movement-speed:step/move
# define ANG_SPEED 1.f		// Angle Var. Speed==rotation-speed:degree/move
# define FPS 1000			// Desired frames per second
# define FPS_DELTA 10		// Number of images to consider for FPS calculation
# define FOV 60.f			// Player's Hori-Field-Of-View Angle(in degrees)
# define FOV_PRE .1f		// Hori-Field-Of-View-Precision(in degrees)
// TODO: could be replace by objects size (height+width)
# define DIST_MIN 1.f		// Distance where OBJECTS_HEIGHT == IMG3D_HEIGHT
//=[ Variables ]================================================================
# define VALID_MAZE_CHARS "01NSEW"
# define M_PI 3.1415926535
//-[ Key definitions ]----------------------------------------------------------
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define Q_KEY 113
# define E_KEY 101
# define LA_KEY 65361
# define RA_KEY 65363
//-[ Colors ]-------------------------------------------------------------------
# define BLACK_COLOR 0x000000
# define RED_COLOR 0xFF0000
# define GREEN_COLOR 0x00FF00
# define BLUE_COLOR 0x0000FF
# define YELLOW_COLOR 0xFFFF00
# define WHITE_COLOR 0xFFFFFF
# define FLOOR_COLOR 0xAAAAAA
# define WALL_COLOR 0x333333
// =[ Include ]=================================================================
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
// =[ Structures ]==============================================================
typedef struct s_fpos
{
	float	x;
	float	y;
}	t_fpos;

typedef struct s_hit
{
	int		valid;	//sentinel-> valid_hit = 1; invalid_hit = 0
	t_fpos	pos;
	t_fpos	angle; // x: degree, y: tan(radian)
	float	distance;
}	t_hit;

typedef struct s_play
{
	t_fpos	pos;
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
	int		cell_nb;
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
	int				nb_of_rays;		// define by FOV and FOV_PRE (2D & 3D)
	float			rot_elem;		// rotation angle per ray (2D)
	int				column_width;	// width in pixels of one column (3D image)
	t_hit			*hits;			// array of hits, size = nb_of_rays
	void			*mlx_ptr;
	void			*win_ptr;
	t_fpos			win_dim;		// window dimensions in pixels(avoid using mlx getter)
	t_fpos			start2d;		// top-left position of 2D image in window
	t_fpos			start3d;		// top-left position of 3D image in window
	t_img			img_erase_txt;
	t_img			img_2d_floor;
	t_img			img_2d_wall;
	t_img			img_2d_template;
	t_img			img_2d_buffer;
	t_img			img_3d_template;
	t_img			img_3d_buffer;
	int				img_drawn;
	int				delay_between_frames_ms;
	struct timeval	last_frame_time;
	struct timeval	fps_start_inter;
	char			fps_str[64];
	char			mv_flags[7];
}	t_data;
// =[ Files & Fun. Signatures ]=================================================
// -[ display_infos.c ]--------------------------------------------------------3
void	display_player_infos(t_data *dt, int line_num);						// ✅
void	display_fps_infos(t_data *dt, int line_num);						// ✅
void	display_hits_infos(t_data *dt, int line_num);						// ✅
// -[ draw_2dimg.c ]-----------------------------------------------------------3
void	draw2d_player(t_img *img, t_play *p);								// ✅
void	draw2d_hit_lines(t_data *dt);										// ✅
int		draw_buffer_2dimg(t_data *dt);										// ✅
// -[ draw_3dimg.c ]-----------------------------------------------------------2
void	draw3d_obj_vlines(t_data *dt);										// ✅
int		draw_buffer_3dimg(t_data *dt);										// ✅
// -[ draw_frame.c ]-----------------------------------------------------------4
int		draw_buffer_images(t_data *dt);										// ❌
// -[ draw_to_img.c ]----------------------------------------------------------6
void	put_pixel_to_image(t_img *img, int x, int y, int color);			// ✅
void	draw_vline(t_img *img, int x, int start_y, int stop_y, int color);	// ✅
void	draw_hline(t_img *img, int x, t_fpos pos, int color);				// ✅
void	draw_circle(t_img *img, t_fpos c_pos, int r, int color);				// ✅
void	draw_dda_line(t_img *img, t_fpos a_pos, t_fpos b_pos, int color);		// ✅
void	draw_vector(t_img *img, t_fpos start, t_fpos vec, int color);			// ✅
// -[ main_loop.c ]------------------------------------------------------------2
int		main_loop(t_data *dt);												// ❌
// -[ memcpy_utils.c ]---------------------------------------------------------2
void	*ft_memcpy(void *dst, const void *src, size_t len);					// ✅
void	*ft_memcpy_by_words(void *dst, const void *src, size_t len);		// ✅
// -[ mov_flags.c ]------------------------------------------------------------3
void	init_movement_flags(t_data *dt);									// ✅
int		key_pressed(int keycode, t_data *dt);								// ✅
int		key_released(int keycode, t_data *dt);								// ✅
// -[ ray_casting.c ]----------------------------------------------------------1
void	update_hit_tpos(t_data *dt);										// ✅
// -[ raycast_collisions.c ]---------------------------------------------------5
int		collision_detected(const t_data *dt, t_fpos ray_pos, float angle);	// ✅
t_fpos	h_found_hit_dda(const t_data *dt, const t_hit *hit);				// ✅
t_fpos	v_found_hit_dda(const t_data *dt, const t_hit *hit);				// ✅
void	found_hit_dda(const t_data *dt, t_hit *hit);						// ✅
void	update_hit_tpos(t_data *dt);										// ✅
// -[ t_data_struct.c ]-------------------------------------------------------5
t_data	init_data(const char **str_arr);									// ✅
void	free_data(t_data *dt);												// ✅
int		error_detected_after_init_data(t_data *dt);							// ✅
// -[ t_hit_struct.c ]---------------------------------------------------------4
t_hit	set_hit(t_hit *hit, float x, float y, float angle);					// ✅
t_hit	*create_hit_array(int size);										// ✅
void	free_hit_array(t_hit **hit_arr);									// ✅
int		print_hit_array(t_hit *hit_arr);									// ✅
// -[ t_img_builders.c ]-------------------------------------------------------5
int		build_img_text(t_img *img);											// ✅
int		build_img_floor(t_img *img);										// ✅
int		build_img_wall(t_img *img);											// ✅
int		build_img_grid(t_maze *maze, t_img *grid, t_img *floor, t_img *wall);//✅
int		build_img_3d(t_img *img);											// ✅
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
// -[ t_player_struct.c ]------------------------------------------------------4
t_play	init_player(void);													// ✅
void	set_player(t_play *play, float x, float y, float dir);				// ✅
int		print_player(t_play play);											// ✅
void	free_player(t_play *player);										// ✅
// -[ t_fpos_struct.c ]--------------------------------------------------------4
t_fpos	init_fpos(float x, float y);										// ✅
t_fpos	set_fpos(t_fpos *pos, float x, float y);							// ✅
int		print_fpos(t_fpos pos);												// ✅
t_fpos	dup_pos(t_fpos src);												// ✅
// -[ t_fpos_utils.c ]---------------------------------------------------------2
float	fpos_dist(t_fpos a, t_fpos b);										// ✅
void	add_fpos(t_fpos *a, const t_fpos *b);								// ✅
// -[ utils.c ]----------------------------------------------------------------4
int		char_in_str(char c, const char *str);								// ✅
void	print_str_array(const char **str_arr);								// ✅
int		diff_time_in_ms(struct timeval start, struct timeval end);			// ✅
int		convert_fps_to_frame_delay(int fps);								// ✅
// -[ utils_math.c ]-----------------------------------------------------------5
float	radian(float degree);												// ✅
int		ft_max(int a, int b);												// ✅
int		ft_abs(int a);														// ✅
float	norm_angle(float angle);											// ✅
int		get_nb_of_rays(void);												// ✅
#endif