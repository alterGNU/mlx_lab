/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_bresenhamdot_ghostmode_busy_spin.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:19:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/04 01:19:24 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * FEATURES:
 * Movable player represented by a red dot (bresenham red circle) using [AWSD]
 * dot-ghost-mode: no-orientation and no-collision detection.
 * Drawing optimization flag to draw only when needed (FAILURE:busy-spin-loop).
 * 
 * OBJECTIFS:
 *  - being able to move a player in the maze (red dot chilling player).
 *  - draw only when needed: _(~optimization->less mallocs when player static)_
 *    - at start.
 *    - when player's position changes.
 * IMPLEMENTATION:
 *  - Add a player structure with position, color, and rayon.
 *  - Add Keyboard hook: _(while being pressed)_
 *    - `[W]` -> step forward
 *    - `[S]` -> step backward.
 *    - `[D]` -> step on the right.
 *    - `[A]` -> step on the left.
 * - OBSERVATIONS:
 *  - Everything works as expected, except for the flag optimization:
 *  - Unfortunately, even with the optimization to reduce drawing calls when the
 *    player is static, the program still makes a significant number of malloc
 *    and free calls.
 *  - This is likely due to the way the MiniLibX library handles image rendering
 *    and window updates, which may involve internal mem. alloc. regardless of 
 *    the drawing frequency.
 */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ESC_KEY 65307
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define WIN_TITLE "Moving player with int flag (busy-spin-loop)"
#define TILE_X 32
#define TILE_Y 32
#define FLOOR_XPM "./docs/floor.xpm"
#define WALL_XPM "./docs/wall.xpm"
#define VALID_MAZE_CHARS "01P"
#define RED_COLOR 0xFF0000
#define CIRCLE_RAYON 8
#define STEP 0.1f

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_play
{
	t_pos	pos;
	int		color;
	int		rayon;
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
	t_maze	maze;
	t_play	player;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img_floor;
	t_img	img_wall;
	t_img	img_buffer;
	int		img_drawn;
	int		draw_needed;
}	t_data;

int	char_in_str(char c, const char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

t_play	init_player(void)
{
	t_play	player;

	player.pos.x = -0.1;
	player.pos.y = -0.1;
	player.color = RED_COLOR;
	player.rayon = CIRCLE_RAYON;
	player.step_count = 0;
	return (player);
}

t_maze	set_maze_and_player(const char **str_arr, t_play *player)
{
	t_maze	maze;
	int		mat_tot_len;
	int		x;
	int		y;

	maze.mat = NULL;
	maze.width = strlen(str_arr[0]);
	maze.height = 0;
	while (str_arr[maze.height])
	{
		if ((int)strlen(str_arr[maze.height]) != maze.width)
		{
			fprintf(stderr, "Inconsistent row lengths in maze definition.\n");
			return (maze.width = 0, maze.height = 0, maze);
		}
		maze.height++;
	}
	mat_tot_len = maze.width * maze.height;
	if (mat_tot_len <= 0)
		return (maze);
	maze.mat = malloc(sizeof(int) * mat_tot_len);
	if (!maze.mat)
		return (maze);
	x = -1;
	while (++x < maze.width)
	{
		y = -1;
		while (++y < maze.height)
		{
			if (char_in_str(str_arr[y][x], VALID_MAZE_CHARS))
			{
				if (str_arr[y][x] == 'P')
				{
					player->pos.x = x + 0.5;
					player->pos.y = y + 0.5;
					maze.mat[y * maze.width + x] = 0;
				}
				else
					maze.mat[y * maze.width + x] = str_arr[y][x] - '0';
			}
			else
				return (free(maze.mat), maze.mat = NULL, maze.width = 0, \
					fprintf(stderr, "Invalid char:'%c'.\n", str_arr[y][x]), \
					maze.height = 0, maze);
		}
	}
	return (maze);
}

void	free_maze(t_maze *maze)
{
	if (maze->mat)
		free(maze->mat);
	maze->mat = NULL;
	maze->width = 0;
	maze->height = 0;
}

void	print_str_array(const char **str_arr)
{
	int	i;

	i = 0;
	printf("string array:\n[");
	while (str_arr[i])
	{
		if (i)
			printf(" ");
		printf("\"%s\", \n", str_arr[i]);
		i++;
	}
	printf("  NULL ]\n\n");
}

void	print_maze(t_maze maze)
{
	int	x;
	int	i;
	int	tot_size;

	tot_size = maze.width * maze.height;
	printf("Maze:\n");
	if (!maze.mat || tot_size <= 0)
		printf("is empty.\n");
	else
	{
		i = -1;
		while (++i < tot_size)
		{
			x = i % maze.width;
			if (i && x == 0)
				printf("\n");
			printf("%c", maze.mat[i] + '0');
		}
		printf("\n");
	}
	printf("\n");
}

t_img	ft_load_image(void *mlx_ptr, const char *filename)
{
	t_img	img;

	img.img_ptr = NULL;
	img.addr = NULL;
	img.width = 0;
	img.height = 0;
	img.bpp = 0;
	img.size_line = 0;
	img.endian = -1;
	if (mlx_ptr && filename)
	{
		img.img_ptr = mlx_xpm_file_to_image(mlx_ptr, (char *)filename, &img.width, &img.height);
		if (img.img_ptr)
			img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_line, &img.endian);
	}
	return (img);
}

t_img	ft_create_buffer_image(void *mlx_ptr, int width, int height)
{
	t_img	img;

	img.img_ptr = NULL;
	img.addr = NULL;
	img.width = width;
	img.height = height;
	img.bpp = 0;
	img.size_line = 0;
	img.endian = -1;
	if (mlx_ptr && width > 0 && height > 0)
	{
		img.img_ptr = mlx_new_image(mlx_ptr, width, height);
		if (img.img_ptr)
			img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_line, &img.endian);
	}
	return (img);
}

void	free_image(t_img img, void *mlx_ptr)
{
	if (mlx_ptr && img.img_ptr)
		mlx_destroy_image(mlx_ptr, img.img_ptr);
	img.img_ptr = NULL;
	img.addr = NULL;
	img.width = 0;
	img.height = 0;
	img.bpp = 0;
	img.size_line = 0;
	img.endian = -1;
}

t_data	init_data(const char **str_arr)
{
	t_data	dt;
	int		win_x;
	int		win_y;

	dt.draw_needed = 1;
	dt.player = init_player();
	dt.mlx_ptr = NULL;
	dt.win_ptr = NULL;
	dt.img_drawn = 0;
	dt.maze = set_maze_and_player(str_arr, &dt.player);
	if (!dt.maze.mat)
		return (dt);
	if (dt.player.pos.x < 0 || dt.player.pos.y < 0)
		return (fprintf(stderr, "NO PLAYER\n"), free_maze(&dt.maze), dt);
	win_x = dt.maze.width * TILE_X;
	win_y = dt.maze.height * TILE_Y;
	if (win_x <= 0 || win_y <= 0)
		return (free_maze(&dt.maze), dt);
	dt.mlx_ptr = mlx_init();
	if (!dt.mlx_ptr)
		return (free_maze(&dt.maze), dt);
	dt.win_ptr = mlx_new_window(dt.mlx_ptr, win_x, win_y, WIN_TITLE);
	if (!dt.win_ptr)
		return (free_maze(&dt.maze), mlx_destroy_display(dt.mlx_ptr), free(dt.mlx_ptr), dt.mlx_ptr = NULL, dt);
	dt.img_floor = ft_load_image(dt.mlx_ptr, FLOOR_XPM);
	if (!dt.img_floor.img_ptr)
		return (free_maze(&dt.maze), mlx_destroy_window(dt.mlx_ptr, dt.win_ptr), mlx_destroy_display(dt.mlx_ptr), free(dt.mlx_ptr), dt.mlx_ptr = NULL, dt);
	dt.img_wall = ft_load_image(dt.mlx_ptr, WALL_XPM);
	if (!dt.img_wall.img_ptr)
		return (free_maze(&dt.maze), mlx_destroy_image(dt.mlx_ptr, dt.img_floor.img_ptr), mlx_destroy_window(dt.mlx_ptr, dt.win_ptr), mlx_destroy_display(dt.mlx_ptr), free(dt.mlx_ptr), dt.mlx_ptr = NULL, dt);
	dt.img_buffer = ft_create_buffer_image(dt.mlx_ptr, win_x, win_y);
	if (!dt.img_buffer.img_ptr)
		return (free_maze(&dt.maze), mlx_destroy_image(dt.mlx_ptr, dt.img_wall.img_ptr), mlx_destroy_image(dt.mlx_ptr, dt.img_floor.img_ptr), mlx_destroy_window(dt.mlx_ptr, dt.win_ptr), mlx_destroy_display(dt.mlx_ptr), free(dt.mlx_ptr), dt.mlx_ptr = NULL, dt);
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

int	handle_key(int keycode, t_data *dt)
{
	if (keycode == ESC_KEY)
		return (mlx_loop_end(dt->mlx_ptr), 1);
	else if (keycode == W_KEY)
	{
		if (dt->player.pos.y - STEP >= 0)
		{
			dt->player.step_count++;
			dt->player.pos.y -= STEP;
			dt->draw_needed = 1;
		}
	}
	else if (keycode == S_KEY)
	{
		if (dt->player.pos.y < (float)dt->maze.height)
		{
			dt->player.step_count++;
			dt->player.pos.y += STEP;
			dt->draw_needed = 1;
		}
	}
	else if (keycode == A_KEY)
	{
		if (dt->player.pos.x - STEP >= 0)
		{
			dt->player.step_count++;
			dt->player.pos.x -= STEP;
			dt->draw_needed = 1;
		}
	}
	else if (keycode == D_KEY)
	{
		if (dt->player.pos.x < (float)dt->maze.width)
		{
			dt->player.step_count++;
			dt->player.pos.x += STEP;
			dt->draw_needed = 1;
		}
	}
	return (0);
}

int	mlx_xpm_cpy_src_in_dst(t_img *src, t_img *dst, int dst_x, int dst_y)
{
	int	x;
	int	y;
	int	bpp;
	int	src_pix;

	if (!dst || !src || !dst->addr || !src->addr || dst_x < 0 || dst_y < 0)
		return (printf("Invalid arguments\n"), 1);
	if (dst_x + src->width > dst->width || dst_y + src->height > dst->height)
		return (printf("Source image exceeds destination bounds\n"), 1);
	if (src->bpp != dst->bpp)
		return (printf("Different bpp not supported\n"), 1);
	bpp = dst->bpp / 8;
	x = -1;
	while (++x < src->height)
	{
		y = -1;
		while (++y < src->width)
		{
			src_pix = *(int *)(src->addr + (x * src->size_line + y * bpp));
			*(int *)(dst->addr + ((dst_y + x) * \
				dst->size_line + (dst_x + y) * bpp)) = src_pix;
		}	
	}
	return (0);
}

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
	i = img->bpp - 8;
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static void	draw_hline(t_img *img, int x1, int x2, int y, int color)
{
	while (x1 <= x2)
	{
		if (x1 >= 0 && x1 < img->width && y >= 0 && y < img->height)
			put_pixel_to_image(img, x1, y, color);
		x1++;
	}
}

static void	draw_filled_circle_bresenham(t_img *img, int cx, int cy, int r, int color)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = r;
	d = 1 - r;

	while (x <= y)
	{
		draw_hline(img, cx - x, cx + x, cy + y, color);
		draw_hline(img, cx - x, cx + x, cy - y, color);
		draw_hline(img, cx - y, cx + y, cy + x, color);
		draw_hline(img, cx - y, cx + y, cy - x, color);

		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}

void	draw_player(t_img *img, t_play *player)
{
	int	cx;
	int	cy;

	cx = player->pos.x * TILE_X;
	cy = player->pos.y * TILE_Y;
	draw_filled_circle_bresenham(img, cx, cy, player->rayon, player->color);
}


int	draw_buffer_image(t_data *dt)
{
	int	tot_len;
	int	i;
	int	x;
	int	y;
	int	res;

	if (!dt->mlx_ptr || !dt->win_ptr)
		return (printf("Error: Invalid data pointers\n"), 1);
	if (dt->draw_needed == 0)
		return (0);
	dt->draw_needed = 0;
	tot_len = dt->maze.width * dt->maze.height;
	i = -1;
	while (++i < tot_len)
	{
		x = i % dt->maze.width;
		y = i / dt->maze.width;
		if (dt->maze.mat[i] == 0)
			res = mlx_xpm_cpy_src_in_dst(&dt->img_floor, &dt->img_buffer, x * TILE_X, y * TILE_Y);
		else if (dt->maze.mat[i] == 1)
			res = mlx_xpm_cpy_src_in_dst(&dt->img_wall, &dt->img_buffer, x * TILE_X, y * TILE_Y);
		else
			res = 1;
		if (res)
			return (fprintf(stderr, "Error draw_buffer_image() failed\n"),
					mlx_loop_end(dt->mlx_ptr), 1);
	}
	draw_player(&dt->img_buffer, &dt->player);
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_buffer.img_ptr, 0, 0);
	dt->img_drawn++;
	return (0);
}

int	main(void)
{
	t_pos	start_pos;
	t_data	dt;
	struct timeval start_time, end_time;
	long	sec_diff;

	const char	*str_arr[] = {
		"1111111111",
		"1000000001",
		"1011111101",
		"1000000101",
		"1111010101",
		"1000010001",
		"1011110101",
		"10000000P1",
		"1111111111",
		NULL
	};
	gettimeofday(&start_time, NULL);
	print_str_array(str_arr);
	dt = init_data(str_arr);
	if (!dt.maze.mat || !dt.mlx_ptr || !dt.win_ptr || dt.player.pos.x < 0 || dt.player.pos.y < 0)
		return (free_data(&dt), fprintf(stderr, "Failed to initialize data.\n"), 1);
	print_maze(dt.maze);
	printf("Starting program:\n - Player starting position(%.2f, %.2f)\n\n", dt.player.pos.x, dt.player.pos.y);
	start_pos.x = dt.player.pos.x;
	start_pos.y = dt.player.pos.y;
	mlx_loop_hook(dt.mlx_ptr, &draw_buffer_image, &dt);
	mlx_hook(dt.win_ptr, 17, 0, &mlx_loop_end, dt.mlx_ptr);
	mlx_hook(dt.win_ptr, 2, (1L << 0), &handle_key, &dt);
	mlx_loop(dt.mlx_ptr);
	gettimeofday(&end_time, NULL);
	sec_diff = end_time.tv_sec - start_time.tv_sec;
	printf("Exiting program:\n - Duration: %ld seconds\n - %d images drawn into window\n", sec_diff, dt.img_drawn);
	printf(" - Player walked %d steps:\n   - from pos(%.2f, %.2f)\n   - to   pos(%.2f, %.2f)\n\n", dt.player.step_count, start_pos.x, start_pos.y, dt.player.pos.x, dt.player.pos.y);
	return (free_data(&dt), 0);
}
