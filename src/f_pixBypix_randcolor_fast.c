/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pixBypix_randcolor_fast.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:54:43 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/01 19:01:40 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Display a random color image using our own pixel put function
 * -> draws pixel by pixel on image, then put image to on window (fast version).
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
#define WIN_TITLE "Random Color Panel (Slow)"
#define COLOR_BLACK 0xFFFFFF

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
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
	return (0);
}

void	put_pixel_to_image(t_data *dt, int x, int y, int color)
{
	char	*pixel;
	int		i;

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

int	create_random_color(void)
{
	int	r;
	int	g;
	int	b;

	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

int	draw_color_panel(t_data *dt)
{
	int	x;
	int	y;
	int	color;

	if (!dt->mlx_ptr || !dt->win_ptr)
		return (printf("Error: Invalid data pointers\n"), 1);
	color = create_random_color();
	x = -1;
	while (++x < WIN_X)
	{
		y = -1;
		while (++y < WIN_Y)
			put_pixel_to_image(dt, x, y, color);
	}
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img_ptr, 0, 0);
	return (0);
}

int	handle_key(int keycode, t_data *dt)
{
	if (keycode == ESC_KEY)
		return (mlx_loop_end(dt->mlx_ptr), 1);
	return (0);
}

int	main(void)
{
	t_data	dt;

	dt = ft_init_data();
	mlx_loop_hook(dt.mlx_ptr, &draw_color_panel, &dt);
	mlx_hook(dt.win_ptr, 17, 0, &mlx_loop_end, dt.mlx_ptr);
	mlx_hook(dt.win_ptr, 2, (1L << 0), &handle_key, &dt);
	mlx_loop(dt.mlx_ptr);
	return (free_data(dt));
}
