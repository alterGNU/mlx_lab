/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:54:43 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/06 16:49:56 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SQUARE_SIZE 2
#define ESC_KEY 65307
#define LEFT_CLICK 1
#define RIGHT_CLICK 3
#define WIN_X 1024
#define WIN_Y 1024
#define WIN_TITLE "Paint from wish"
#define COLOR_WHITE 0xFFFFFF
#define COLOR_BLACK 0x000000

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		cursor_x;
	int		cursor_y;
	int		flag_draw;
	int		mouse_pressed;
}	t_data;

t_data	ft_init_data(void)
{
	t_data	dt;

	dt.mlx_ptr = NULL;
	dt.win_ptr = NULL;
	dt.img_ptr = NULL;
	dt.addr = NULL;
	dt.bpp = 0;
	dt.size_line = 0;
	dt.endian = -1;
	dt.cursor_x = -100;
	dt.cursor_y = -100;
	dt.flag_draw = 1;
	dt.mouse_pressed = 0;
	dt.mlx_ptr = mlx_init();
	if (!dt.mlx_ptr)
		return (dt);
	dt.win_ptr = mlx_new_window(dt.mlx_ptr, WIN_X, WIN_Y, WIN_TITLE);
	if (!dt.win_ptr)
	{
		return (mlx_destroy_display(dt.mlx_ptr), free(dt.mlx_ptr), \
				dt.mlx_ptr = NULL, dt);
	}
	dt.img_ptr = mlx_new_image(dt.mlx_ptr, WIN_X, WIN_Y);
	if (!dt.img_ptr)
		return (mlx_destroy_display(dt.mlx_ptr), free(dt.mlx_ptr), \
				dt.mlx_ptr = NULL, mlx_destroy_display(dt.mlx_ptr), \
				free(dt.mlx_ptr), dt.mlx_ptr = NULL, dt);
	dt.addr = mlx_get_data_addr(dt.img_ptr, &dt.bpp, &dt.size_line, &dt.endian);
	return (dt);
}

int	free_data(t_data dt)
{
	if (dt.img_ptr)
		mlx_destroy_image(dt.mlx_ptr, dt.img_ptr);
	if (dt.win_ptr)
		mlx_destroy_window(dt.mlx_ptr, dt.win_ptr);
	if (dt.mlx_ptr)
	{
		mlx_destroy_display(dt.mlx_ptr);
		free(dt.mlx_ptr);
	}
	dt.mlx_ptr = NULL;
	dt.win_ptr = NULL;
	dt.img_ptr = NULL;
	dt.addr = NULL;
	dt.bpp = 0;
	dt.size_line = 0;
	dt.endian = 0;
	dt.flag_draw = 0;
	return (0);
}

void	put_pixel_to_image(t_data *dt, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x < 0 || x >= WIN_X || y < 0 || y >= WIN_Y || !dt->addr)
		return ;
	pixel = dt->addr + (y * dt->size_line + x * (dt->bpp / 8));
	i = dt->bpp - 8;
	while (i >= 0)
	{
		if (dt->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (dt->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	clear_image(t_data *dt)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			put_pixel_to_image(dt, x, y, COLOR_BLACK);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_ptr, 0, 0);
}

int	draw_white_square(t_data *dt)
{
	int	x;
	int	y;

	if (!dt->mlx_ptr || !dt->win_ptr)
		return (printf("Error: Invalid data pointers\n"), 1);
	if (dt->flag_draw)
	{
		x = ft_max(dt->cursor_x - SQUARE_SIZE / 2, 0);
		while (0 <= x && x < WIN_X && x <= dt->cursor_x + SQUARE_SIZE / 2)
		{
			y = ft_max(dt->cursor_y - SQUARE_SIZE / 2, 0);
			while (0 <= y && y < WIN_Y && y <= dt->cursor_y + SQUARE_SIZE / 2)
			{
				put_pixel_to_image(dt, x, y, COLOR_WHITE);
				y++;
			}
			x++;
		}
		mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_ptr, 0, 0);
		dt->flag_draw = 0;
	}
	return (0);
}

int	handle_key(int keycode, t_data *dt)
{
	if (keycode == ESC_KEY)
		return (mlx_loop_end(dt->mlx_ptr), 1);
	return (0);
}

int update_cursor_position(int x, int y, t_data *dt)
{
	int	i;
	int	j;

	dt->cursor_x = x;
	dt->cursor_y = y;
	if (dt->mouse_pressed)
	{
		i = ft_max(x - SQUARE_SIZE / 2, 0);
		while (i < WIN_X && i <= x + SQUARE_SIZE / 2)
		{
			j = ft_max(y - SQUARE_SIZE / 2, 0);
			while (j < WIN_Y && j <= y + SQUARE_SIZE / 2)
			{
				put_pixel_to_image(dt, i, j, COLOR_WHITE);
				j++;
			}
			i++;
		}
		mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_ptr, 0, 0);
	}
	return (0);
}

int	handle_mouse_click(int button, int x, int y, t_data *dt)
{
	int	i;
	int	j;

	if (button == LEFT_CLICK && dt && dt->mlx_ptr && dt->win_ptr)
	{
		dt->mouse_pressed = 1;
		i = ft_max(x - SQUARE_SIZE / 2, 0);
		while (i < WIN_X && i <= x + SQUARE_SIZE / 2)
		{
			j = ft_max(y - SQUARE_SIZE / 2, 0);
			while (j < WIN_Y && j <= y + SQUARE_SIZE / 2)
			{
				put_pixel_to_image(dt, i, j, COLOR_WHITE);
				j++;
			}
			i++;
		}
		mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_ptr, 0, 0);
	}
	else if (button == RIGHT_CLICK && dt && dt->mlx_ptr && dt->win_ptr)
	{
		clear_image(dt);
	}
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_data *dt)
{
	(void)x;
	(void)y;
	if (button == LEFT_CLICK)
		dt->mouse_pressed = 0;
	return (0);
}

int	main(void)
{
	t_data	dt;

	dt = ft_init_data();
	mlx_hook(dt.win_ptr, 17, 0, &mlx_loop_end, dt.mlx_ptr);
	mlx_hook(dt.win_ptr, 2, (1L << 0), &handle_key, &dt);
	mlx_hook(dt.win_ptr, 4, (1L << 2), &handle_mouse_click, &dt);
	mlx_hook(dt.win_ptr, 5, (1L << 3), &handle_mouse_release, &dt);
	mlx_hook(dt.win_ptr, 6, (1L << 6), &update_cursor_position, &dt);
	mlx_loop(dt.mlx_ptr);
	return (free_data(dt));
}
