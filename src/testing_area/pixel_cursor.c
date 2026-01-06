/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:54:43 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/06 16:49:53 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * A black pixel follows the mouse cursor on a white image.
 * 
 * - IMPLEMENTATION:
 *   - Clean exit on [ESC] key or window close (using mlx_loop_end())
 *   - Create our put_pixel_to_img() that put pixel in image 
 *   - Once full image is drawn in memory, call mlx_put_image_to_window()
 * - OBSERVATIONS:
 *   - This approach is more complex, but way faster for large images.
 *   - The drawing process is done in memory, then displayed in one go.
 */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESC_KEY 65307
#define WIN_X 1024
#define WIN_Y 1024
#define WIN_TITLE "Pixel Cursor"
#define COLOR_WHITE 0xFFFFFF
#define COLOR_BLACK 0x000000

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

t_img	ft_init_image(void *mlx_ptr)
{
	t_img	img;

	img.addr = NULL;
	img.bpp = 0;
	img.size_line = 0;
	img.endian = -1;
	img.img_ptr = mlx_new_image(mlx_ptr, WIN_X, WIN_Y);
	if (!img.img_ptr)
		return (img);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_line, &img.endian);
	return (img);
}

void	free_image(t_img img, void *mlx_ptr)
{
	if (mlx_ptr && img.img_ptr)
		mlx_destroy_image(mlx_ptr, img.img_ptr);
	img.addr = NULL;
	img.bpp = 0;
	img.size_line = 0;
	img.endian = -1;
}

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		old_cursor_x;
	int		old_cursor_y;
	int		new_cursor_x;
	int		new_cursor_y;
	int		loop_count;
}	t_data;

t_data	ft_init_data(void)
{
	t_data	dt;

	dt.mlx_ptr = NULL;
	dt.win_ptr = NULL;
	dt.old_cursor_x = 0;
	dt.old_cursor_y = 0;
	dt.new_cursor_x = 0;
	dt.new_cursor_y = 0;
	dt.loop_count = 0;
	dt.mlx_ptr = mlx_init();
	if (!dt.mlx_ptr)
		return (dt);
	dt.win_ptr = mlx_new_window(dt.mlx_ptr, WIN_X, WIN_Y, WIN_TITLE);
	if (!dt.win_ptr)
	{
		return (mlx_destroy_display(dt.mlx_ptr), free(dt.mlx_ptr), \
				dt.mlx_ptr = NULL, dt);
	}
	dt.img = ft_init_image(dt.mlx_ptr);
	if (!dt.img.img_ptr)
		return (mlx_destroy_display(dt.mlx_ptr), free(dt.mlx_ptr), \
				dt.mlx_ptr = NULL, mlx_destroy_display(dt.mlx_ptr), \
				free(dt.mlx_ptr), dt.mlx_ptr = NULL, dt);
	return (dt);
}

int	free_data(t_data dt)
{
	free_image(dt.img, dt.mlx_ptr);
	if (dt.win_ptr)
		mlx_destroy_window(dt.mlx_ptr, dt.win_ptr);
	if (dt.mlx_ptr)
	{
		mlx_destroy_display(dt.mlx_ptr);
		free(dt.mlx_ptr);
	}
	dt.mlx_ptr = NULL;
	dt.win_ptr = NULL;
	dt.old_cursor_x = 0;
	dt.old_cursor_y = 0;
	dt.new_cursor_x = 0;
	dt.new_cursor_y = 0;
	dt.loop_count = 0;
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

int	draw_white_image(t_data *dt)
{
	int	x;
	int	y;

	if (!dt->mlx_ptr || !dt->win_ptr)
		return (printf("Error: Invalid data pointers\n"), 1);
	if (!dt->loop_count)
	{
		x = -1;
		while (++x < WIN_X)
		{
			y = -1;
			while (++y < WIN_Y)
				put_pixel_to_image(&dt->img, x, y, COLOR_WHITE);
		}
		mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img.img_ptr, 0, 0);
		dt->loop_count++;
	}
	else if (dt->new_cursor_x != dt->old_cursor_x || dt->new_cursor_y != dt->old_cursor_y)
	{
		put_pixel_to_image(&dt->img, dt->old_cursor_x, dt->old_cursor_y, COLOR_WHITE);
		put_pixel_to_image(&dt->img, dt->new_cursor_x, dt->new_cursor_y, COLOR_BLACK);
		dt->old_cursor_x = dt->new_cursor_x;
		dt->old_cursor_y = dt->new_cursor_y;
		mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img.img_ptr, 0, 0);
		dt->loop_count++;
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
	(void) x;
	(void) y;
	mlx_mouse_get_pos(dt->mlx_ptr, dt->win_ptr, &dt->new_cursor_x, &dt->new_cursor_y);
	return (0);
}

int	main(void)
{
	t_data	dt;

	dt = ft_init_data();
	mlx_loop_hook(dt.mlx_ptr, &draw_white_image, &dt);
	mlx_hook(dt.win_ptr, 17, 0, &mlx_loop_end, dt.mlx_ptr);
	mlx_hook(dt.win_ptr, 2, (1L << 0), &handle_key, &dt);
	mlx_hook(dt.win_ptr, 6, (1L << 6), &update_cursor_position, &dt);
	mlx_loop(dt.mlx_ptr);
	return (free_data(dt));
}
