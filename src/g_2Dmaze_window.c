/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_2Dmaze_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:19:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/03 18:17:31 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Display a simple 2D maze using XPM images directly on the window.
 * 
 * - IMPLEMENTATION:
 *   - Load floor and wall images from XPM files.
 *   - Create a maze from a string array.
 *   - Draw the maze directly onto the window using mlx_put_image_to_window().
 *   - Clean exit on [ESC] key or window close (using mlx_loop_end()).
 *   - Display how long the program ran and how many images were drawn.
 * - OBSERVATIONS:
 *   - This approach is straightforward but may be slower for large mazes
 *     since it draws directly to the window pixel by pixel.
 *   - To many malloc calls:
 *     - For 20s exec--> 5M images dawned --> 10M malloc/free calls.
 */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define ESC_KEY 65307
#define WIN_TITLE "2D Maze directly on Window (slow)"
#define TILE_X 32
#define TILE_Y 32
#define FLOOR_XPM "./docs/floor.xpm"
#define WALL_XPM "./docs/wall.xpm"
#define VALID_MAZE_CHARS "01"

typedef struct s_maze
{
	int		*mat; // 2D matrix stored in 1D array
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
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img_floor;
	t_img	img_wall;
	int		img_drawn;
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

t_maze	init_maze(const char **str_arr)
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
				maze.mat[y * maze.width + x] = str_arr[y][x] - '0';
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
			printf("%d", maze.mat[i]);
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

	dt.mlx_ptr = NULL;
	dt.win_ptr = NULL;
	dt.img_drawn = 0;
	dt.maze = init_maze(str_arr);
	if (!dt.maze.mat)
		return (dt);
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
	return (dt);
}

void	free_data(t_data *dt)
{
	free_maze(&dt->maze);
	free_image(dt->img_floor, dt->mlx_ptr);
	free_image(dt->img_wall, dt->mlx_ptr);
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
	return (0);
}

int	draw_image(t_data *dt)
{
	int	tot_len;
	int	i;
	int	x;
	int	y;

	if (!dt->mlx_ptr || !dt->win_ptr)
		return (printf("Error: Invalid data pointers\n"), 1);
	tot_len = dt->maze.width * dt->maze.height;
	i = -1;
	while (++i < tot_len)
	{
		x = i % dt->maze.width;
		y = i / dt->maze.width;
		if (dt->maze.mat[i] == 0)
		{
			mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_floor.img_ptr, x * TILE_X, y * TILE_Y);
			dt->img_drawn++;
		}
		else if (dt->maze.mat[i] == 1)
		{
			mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_wall.img_ptr, x * TILE_X, y * TILE_Y);
			dt->img_drawn++;
		}
		else
			return (fprintf(stderr, "Invalid maze value at (%d, %d): %d\n", x, y, dt->maze.mat[i]), mlx_loop_end(dt->mlx_ptr), 1);
	}
	return (0);
}

int	main(void)
{
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
		"1000000001",
		"1111111111",
		NULL
	};
	gettimeofday(&start_time, NULL);
	print_str_array(str_arr);
	dt = init_data(str_arr);
	if (!dt.maze.mat || !dt.mlx_ptr || !dt.win_ptr)
		return (free_data(&dt), fprintf(stderr, "Failed to initialize data.\n"), 1);
	print_maze(dt.maze);
	mlx_loop_hook(dt.mlx_ptr, &draw_image, &dt);
	mlx_hook(dt.win_ptr, 17, 0, &mlx_loop_end, dt.mlx_ptr);
	mlx_hook(dt.win_ptr, 2, (1L << 0), &handle_key, &dt);
	mlx_loop(dt.mlx_ptr);
	gettimeofday(&end_time, NULL);
	sec_diff = end_time.tv_sec - start_time.tv_sec;
	printf("Exiting program:\n - after %ld seconds\n - %d images drawn into window\n", sec_diff, dt.img_drawn);
	return (free_data(&dt), 0);
}
