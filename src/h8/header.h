/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:08:27 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 04:36:16 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
// -[ Debug/UI toggles ]------------------------t-------------------------------
# define DRAW_FUN_AUTO 1		// 0: fun draw 3d not autonomous, 1: autonomous
# define OPTI_MODE 1			// 0: generic, 1: for little-endian 32bpp
# define DRAW_MINIMAP 1			// 0: do not draw 2d image (map), else: draw it
# define DRAW_2D_RAYS 1			// 0: none, 1: first/last, 2: all rays
# define DRAW_HITS_TXT 0		// 0: disable, 1: enable hit positions display
//-[ Window ]-------------------------------------------------------------------
# if DRAW_FUN_AUTO > 0
#  if OPTI_MODE > 0
#   define WIN_TITLE "Caster the Ghost-(MODE:AUTONOMOUS+OPTI)"
#  else
#   define WIN_TITLE "Caster the Ghost-(MODE:AUTONOMOUS)"
#  endif
# else
#  if OPTI_MODE > 0
#   define WIN_TITLE "Caster the Ghost-(MODE:OPTI)"
#  else
#   define WIN_TITLE "Caster the Ghost-(MODE:GENERIC)"
#  endif
# endif
# define WIN_BORDER 5			// space between window border & images
# define WIN_DBG_TXT_LEN 250	// length(in pixels)of debug txt area
//-[ 2DImage ]------------------------------------------------------------------
# define RAY2D_C 0xFFFF00		// color of the rays drawn on the 2D image
# define FLOOR2D_COLOR 0xAAAAAA	// color of the floor in 2D image
# define WALL2D_COLOR 0x333333	// color of the walls in 2D image
# define TILE_X 32 				// width(in pixels) of one 2Dcell
# define TILE_Y 32 				// height(in pixels) of one 2Dcell
# define CIRCLE_RADIUS 8		// size of the player representation
//# define TILE_X 16 				// width(in pixels) of one 2Dcell
//# define TILE_Y 16 				// height(in pixels) of one 2Dcell
//# define CIRCLE_RADIUS 4		// size of the player representation
//-[ 3DImage ]------------------------------------------------------------------
# define DARK_FACTOR .5f // dark-factor for inside3D 0.4f=darker, 1.4f=lighter
// TODO: replace by resolution format string RESOLUTION "1024x768"
//# define IMG3D_WIDTH 1200
//# define IMG3D_HEIGHT 800
# define IMG3D_WIDTH 1024
# define IMG3D_HEIGHT 768
//# define IMG3D_WIDTH 512
//# define IMG3D_HEIGHT 512
# define FLOOR3D_RGB 0x4A5866
# define CEIL3D_RGB 0xC7AF36
# define NOW_COLOR 0x912a2a
# define EOW_COLOR 0x7a1b1b
# define SOW_COLOR 0x541818
# define WOW_COLOR 0x6e2b2b
# define NIW_COLOR 0X519137
# define EIW_COLOR 0x35751b
# define SIW_COLOR 0X224215
# define WIW_COLOR 0x406930
// -[ Engine ]------------------------------------------------------------------
# define PRE_RAY 0.0001f	// Ray detection precision
# define EPSILON 0.000001f	// Small value to avoid division by zero
# define POS_SPEED .1f		// Position Var. Speed==movement-speed:step/move
# define ANG_SPEED 2.f		// Angle Var. Speed==rotation-speed:degree/move
//# define FPS 20			// Desired frames per second
# define FPS 1000			// Desired frames per second
# define FPS_DELTA 10		// Number of images to consider for FPS calculation
# define FOV 64.f			// Player's Hori-Field-Of-View Angle(in degrees)2**6
//# define FOV 32.f			// Player's Hori-Field-Of-View Angle(in degrees)2**5
//# define FOV_PRE 64.		// 64/64=1
//# define FOV_PRE 12.8		// 64/5=12.8->makes sure to get an ODD nb of rays
//# define FOV_PRE 0.5			// Hori-Field-Of-View-Precision(in degrees)2**-1
//# define FOV_PRE 0.25			// Hori-Field-Of-View-Precision(in degrees)2**-2
//# define FOV_PRE 0.125		// Hori-Field-Of-View-Precision(in degrees)2**-3
# define FOV_PRE .0625		// Hori-Field-Of-View-Precision(in degrees)2**-4
//# define FOV_PRE .003125		// Hori-Field-Of-View-Precision(in degrees)2**-5
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
# define G_KEY 103
# define T_KEY 116
# define LA_KEY 65361
# define RA_KEY 65363
//-[ Colors ]-------------------------------------------------------------------
# define BLACK_COLOR 0x000000
# define RED_COLOR 0xFF0000
# define GREEN_COLOR 0x00FF00
# define BLUE_COLOR 0x0000FF
# define YELLOW_COLOR 0xFFFF00
# define WHITE_COLOR 0xFFFFFF
# define LIGHT_GREEN_COLOR 0x255C33
# define DARK_GREEN_COLOR 0x13381D
# define LIGHT_RED_COLOR 0xA82727
# define DARK_RED_COLOR 0x6E1A1A
# define DARK_BLUE_COLOR 0x180D3B
# define LIGHT_BLUE_COLOR 0x3F278F
// =[ Include ]=================================================================
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
// =[ ENUMERATION ] ============================================================
typedef enum e_wall_type
{
	WIW=-4, // West Outside Wall
	SIW=-3, // South Inside Wall
	EIW=-2, // East Inside Wall
	NIW=-1, // North Inside Wall
	UNSET=0,
	NOW=1, // North Outside Wall
	EOW=2, // East Outside Wall
	SOW=3, // South Outside Wall
	WOW=4, // West Outside Wall
}	t_wall_type;
// =[ Structures ]==============================================================
typedef struct s_ipos
{
	int				x;
	int				y;
}	t_ipos;

typedef struct s_fpos
{
	float			x;
	float			y;
}	t_fpos;

typedef struct s_text
{
	t_ipos			dim;
	int				size;
	int				*img;
}	t_text;

typedef struct s_hit
{
	int				valid;	//sentinel-> valid_hit = 1; invalid_hit = 0
	t_ipos			type;	// x: wall_type(enum), y: coloration
	t_fpos			pos;	// 2d position of the hit
	t_fpos			dim;	// 3D size of the object hit (x:width, y:height)
	t_fpos			angle;	// x: degree, y: radian
	float			tan_angle;
	t_fpos			dist;	// x: real distance, y: corrected distance(fish-eye effect)
	t_ipos			img_pix;// pixel coord. in image.
	t_ipos			y_inter;// x:y start in image, y:y stop in image.
	t_fpos			txt_pix;// pixel coord. in texture image.
	t_fpos			txt_ty;	// x:step on texture pixel column, y:offset on texture pixel column
	t_text			*texture;
	unsigned int	color;
}	t_hit;

typedef struct s_play
{
	t_fpos			pos;
	float			dir;
	unsigned int	color;
	int				radius;
	int				step_count;
	char			*play_str;
	int				mode; // 0: ghost_mode->no collision, 1: mortal_mode->collision enabled
}	t_play;

typedef struct s_maze
{
	int				*mat;
	int				width;
	int				height;
	int				cell_nb;
}	t_maze;

typedef struct s_img
{
	void			*img_ptr;
	char			*addr;
	//t_ipos			dim; // TODO: replace width & height by dim.x and dim.y
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
	void			(*put_pix_to_img)(struct s_img *, int, int, int);
	void			(*draw_vlines)(struct s_img *, int, t_ipos, int);
	int				(*dark_filter)(int color, float darkness_factor);
}	t_ima;

typedef struct s_data
{
	char			txt_mode_str[8];
	int				txt_mode;
	t_fpos			tile_dim;
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
	t_ima			img_erase_txt;
	t_ima			img_2d_floor;
	t_ima			img_2d_wall;
	t_ima			img_2d_template;
	t_ima			img_2d_buffer;
	t_ima			img_3d_out_temp;
	t_ima			img_3d_ins_temp;
	t_ima			img_3d_buffer;
	int				img_drawn;
	int				delay_between_frames_ms;
	struct timeval	last_frame_time;
	struct timeval	fps_start_inter;
	char			fps_str[64];
	char			mv_flags[7];
	t_text			*txt_north;
	t_text			*txt_south;
	t_text			*txt_east;
	t_text			*txt_west;
	t_text			*txt_v;
	t_text			*txt_h;
}	t_data;
// =[ Files & Fun. Signatures ]=================================================
// -[ display_infos.c ]--------------------------------------------------------3
void	display_player_infos(t_data *dt, int line_num);						// ✅
void	display_fps_infos(t_data *dt, int line_num);						// ❌
void	display_hits_infos(t_data *dt, int line_num);						// ❌
// -[ draw_2dimg.c ]-----------------------------------------------------------3
void	draw2d_player(t_ima *img, t_play *p);								// ✅
void	draw2d_hit_lines(t_data *dt);										// ✅
int		draw_buffer_2dimg(t_data *dt);										// ✅
// -[ draw_3dbuff_img.c ]------------------------------------------------------1
int		draw_buffer_3dimg(t_data *dt);										// ✅
// -[ draw_3dfun_auto.c ]------------------------------------------------------4
void	draw3d_obj_vlines_auto(t_ima *img, t_hit *hit, int col_width);		// ✅
void	draw3d_obj_vlines_auto_le32(t_ima *img, t_hit *hit, int col_width);	// ✅
void	draw3d_obj_texture_auto(t_ima *img, t_hit *hit, int col_width);		// ✅
void	draw3d_obj_texture_auto_le32(t_ima *img, t_hit *hit, int col_width);// ✅
// -[ draw_3dfun.c ]-----------------------------------------------------------4
void	draw3d_obj_vlines(t_ima *img, t_hit *hit, int col_width);			// ✅
void	draw3d_obj_vlines_le32(t_ima *img, t_hit *hit, int col_width);		// ✅
void	draw3d_obj_texture(t_ima *img, t_hit *hit, int col_width);			// ✅
void	draw3d_obj_texture_le32(t_ima *img, t_hit *hit, int col_width);		// ✅
// -[ draw_buffer_images.c ]---------------------------------------------------1
int		draw_buffer_images(t_data *dt);										// ❌
// -[ draw_geo_shapes.c ]------------------------------------------------------5
void	draw_dda_line(t_ima *img, t_fpos a_pos, t_fpos b_pos, int color);	// ✅
void	draw_dda_line_opti(t_ima *img, t_fpos a_pos, t_fpos b_pos, int color);
void	draw_circle(t_ima *img, t_fpos c_pos, int r, int color);			// ✅
void	draw_vector(t_ima *img, t_fpos start, t_fpos vec, int color);		// ✅
void	draw_vector_opti(t_ima *img, t_fpos c, t_fpos ang, int color);		// ✅
// -[ draw_lines.c ]-----------------------------------------------------------4
void	draw_hline(t_ima *img, int x, t_fpos pos, int color);				// ✅
void	draw_vlines_generic(t_ima *img, int x, t_ipos y_inter, int color);	// ✅
void	draw_vlines_little_end_32(t_ima *img, int x, t_ipos y_inter, int color);
void	draw_vlines_big_end_32(t_ima *img, int x, t_ipos y_inter, int color);//✅
// -[ main_loop.c ]------------------------------------------------------------4
int		main_loop(t_data *dt);												// ❌
// -[ memcpy_utils.c ]---------------------------------------------------------2
void	*ft_memcpy(void *dst, const void *src, size_t len);					// ✅
void	*ft_memcpy_by_words(void *dst, const void *src, size_t len);		// ✅
// -[ mov_flags.c ]------------------------------------------------------------3
void	init_movement_flags(t_data *dt);									// ✅
int		key_pressed(int keycode, t_data *dt);								// ✅
int		key_released(int keycode, t_data *dt);								// ✅
// - [ put_pix_to_img.c ]------------------------------------------------------4
void	put_pix_to_img_little_end(t_ima *img, int x, int y, int color);		// ✅
void	put_pix_to_img_little_end_32(t_ima *img, int x, int y, int color);	// ✅
void	put_pix_to_img_big_end(t_ima *img, int x, int y, int color);		// ✅
void	put_pix_to_img_big_end_32(t_ima *img, int x, int y, int color);		// ✅
// -[ raycast_collisions.c ]---------------------------------------------------3
int		collision_detected(const t_data *dt, t_fpos ray_pos);				// ❌
t_fpos	h_found_hit_dda(const t_data *dt, const t_hit *hit);				// ✅
t_fpos	v_found_hit_dda(const t_data *dt, const t_hit *hit);				// ✅
// -[raycast_update_hit.c ]----------------------------------------------------5
void	found_hit_set_type(const t_data *dt, t_hit *hit);					// ✅
void	update_hit_tpos(t_data *dt);										// ✅
// -[ t_data_struct.c ]--------------------------------------------------------5
t_data	init_data(const char **str_arr);									// ❌
void	free_data(t_data *dt);												// ✅
int		error_detected_after_init_data(t_data *dt);							// ❌
// -[ t_data_struct_utils.c ]--------------------------------------------------2
void	set_txt_mode_str(t_data *dt);										// ❌
void	toggle_texture_mode(t_data *dt);									// ✅
// -[ t_fpos_struct.c ]--------------------------------------------------------4
t_fpos	fpos_new(float x, float y);											// ✅
t_fpos	fpos_set(t_fpos *pos, float x, float y);							// ✅
int		fpos_print(t_fpos pos);												// ✅
t_fpos	fpos_dup(t_fpos src);												// ✅
// -[ t_fpos_utils.c ]---------------------------------------------------------5
float	fpos_dist(t_fpos a, t_fpos b);										// ✅
void	fpos_add(t_fpos *a, const t_fpos *b);								// ✅
t_fpos	fpos_dot_new(const t_fpos a, const t_fpos b);						// ✅
void	fpos_scal(t_fpos *a, float scalar);									// ✅
float	fpos_prod(const t_fpos a);											// ✅
// -[ t_hit_array.c ]----------------------------------------------------------3
t_hit	*create_hit_array(int size);										// ✅
void	free_hit_array(t_hit **hit_arr);									// ✅
int		print_hit_array(t_hit *hit_arr);									// ✅
// -[ t_hit_struct.c ]---------------------------------------------------------6
t_hit	init_hit(void);														// ✅
void	set_hit_obj_dim(t_hit *hit);										// ✅
void	set_hit_texture(const t_data *dt, t_hit *hit);						// ✅
// -[ t_ima_builders.c ]-------------------------------------------------------5
int		build_img_text(t_ima *img, int color);								// ✅
int		build_img_floor(t_ima *img);										// ✅
int		build_img_wall(t_ima *img);											// ✅
int		build_img_grid(t_maze *maze, t_ima *grid, t_ima *floor, t_ima *wall);//✅
int		build_img_3d(t_ima *img, int ceil_color, int floor_color);			// ✅
// -[ t_ima_manipulations.c ]--------------------------------------------------3
int		t_ima_insert_rows_by_words(\
		t_ima *src, t_ima *dst, int dst_x, int dst_y);						// ✅
int		dup_t_ima_by_words(t_ima *src, t_ima *dst);							// ✅
// -[ t_ima_struct.c ]---------------------------------------------------------5
void	memset_zero_img(t_ima *img);										// ✅
void	set_ima_fun_ptrs(t_ima *img);										// ✅
t_ima	create_image(void *mlx_ptr, int width, int height);					// ✅
void	free_image(t_ima img, void *mlx_ptr);								// ✅
int		is_img_valid(t_ima *img);											// ✅
//void	print_t_ima(t_ima img);
// -[ t_ipos_struct.c ]--------------------------------------------------------4
t_ipos	ipos_new(int x, int y);												// ✅
void	ipos_set(t_ipos *pos, int x, int y);								// ✅
int		ipos_print(t_ipos pos);												// ✅
t_ipos	ipos_dup(t_ipos src);												// ✅
// -[ t_ipos_utils.c ]---------------------------------------------------------3
t_ipos	ipos_add_new(const t_ipos *a, const t_ipos *b);						// ✅
t_ipos	ipos_dot_new(const t_ipos *a, const t_ipos *b);						// ✅
t_ipos	ipos_scal_new(const t_ipos *a, int b);								// ✅
// -[ t_maze_struct.c ]--------------------------------------------------------4
t_maze	set_maze_and_player(const char **str_arr, t_play *player);			// ❌
void	free_maze(t_maze *maze);											// ✅
void	print_maze(t_maze maze);											// ✅
// -[ t_player_struct_utils.c ]------------------------------------------------2
void	toggle_player_mode(t_play *player);									// ✅
int		player_diff(const t_play *play_a, const t_play *play_b);			// ✅
// -[ t_player_struct.c ]------------------------------------------------------4
t_play	init_player(void);													// ✅
void	set_player(t_play *play, float x, float y, float dir);				// ❌
int		print_player(t_play play);											// ✅
void	free_player(t_play *player);										// ✅
// -[ t_pos conv.c ]----------------------------------------------------------3
void	fpos_floor(t_ipos *a, const t_fpos *b);								// ✅
void	fpos_ceil(t_ipos *a, const t_fpos *b);								// ✅
void	fpos_round(t_ipos *a, const t_fpos *b);								// ✅
// -[ t_texture_setters.c ]---------------------------------------------------6
int		set_north_texture(t_data *dt);										// ❌
int		set_east_texture(t_data *dt);										// ❌
int		set_south_texture(t_data *dt);										// ❌
int		set_west(t_data *dt);												// ❌
int		set_horizontal_texture(t_data *dt);									// ❌
int		set_vertical_texture(t_data *dt);									// ❌
// -[ t_texture_struct.c ]-----------------------------------------------------2
t_text	*init_texture(int width, int height);								// ✅
void	free_texture(t_text **txt);											// ✅
// -[ utils_color.c ]---------------------------------------------------------2
int		dark_filter_big_end(int color, float darkness_factor);				// ✅
int		dark_filter_little_end(int color, float darkness_factor);			// ✅
// -[ utils_fmath.c ]----------------------------------------------------------5
float	ft_fmax(float a, float b);											// ✅
float	ft_fmin(float a, float b);											// ✅
float	ft_fabs(float a);													// ✅
float	radian(float degree);												// ✅
float	norm_angle(float angle);											// ✅
// -[ utils_imath.c ]----------------------------------------------------------3
int		ft_imax(int a, int b);												// ✅
int		ft_imin(int a, int b);												// ✅
int		ft_iabs(int a);														// ✅
// -[ utils.c ]----------------------------------------------------------------5
int		char_in_str(char c, const char *str);								// ✅
void	print_str_array(const char **str_arr);								// ✅
int		diff_time_in_ms(struct timeval start, struct timeval end);			// ✅
int		convert_fps_to_frame_delay(int fps);								// ✅
int		get_nb_of_rays(void);												// ✅
#endif