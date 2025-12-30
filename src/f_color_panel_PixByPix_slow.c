/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_color_panel_PixByPix_slow.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:54:43 by lagrondi          #+#    #+#             */
/*   Updated: 2025/12/30 15:48:56 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Display a color panel (X axis = Red, Y axis = Green) pixel by pixel slowly.
 * 
 * - IMPLEMENTATION:
 *   - Clean exit on [ESC] key or window close (using mlx_loop_end())
 *   - Use mlx_pixel_put() in the mlx_loop_hook():
 *     - Instead of drawing the entire panel at once, it updates each pixel 
 *       individually resulting in a slow rendering effect.
 * - OBSERVATIONS:
 *   - This approach is inefficient and results in a very slow rendering.
 *   - Clean exit can be ignored if occured during the drawing process. 
 */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESC_KEY 65307
#define WIN_X 1024
#define WIN_Y 1024
#define WIN_TITLE "(X:Red - Y:Green) Color Panel"
#define COLOR_BLACK 0xFFFFFF

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

t_data	ft_init_data(void)
{
	t_data	dt;

	dt.mlx_ptr = mlx_init();
	if (!dt.mlx_ptr)
		return (dt);
	dt.win_ptr = mlx_new_window(dt.mlx_ptr, WIN_X, WIN_Y, WIN_TITLE);
	if (!dt.win_ptr)
	{
		return (mlx_destroy_display(dt.mlx_ptr), free(dt.mlx_ptr), \
				dt.mlx_ptr = NULL, dt);
	}
	return (dt);
}

int	free_data(t_data dt)
{
	if (dt.win_ptr)
	{
		mlx_destroy_window(dt.mlx_ptr, dt.win_ptr);
		dt.win_ptr = NULL;
	}
	if (dt.mlx_ptr)
	{
		mlx_destroy_display(dt.mlx_ptr);
		free(dt.mlx_ptr);
		dt.mlx_ptr = NULL;
	}
	return (0);
}

int	handle_key(int keycode, t_data *dt)
{
	if (keycode == ESC_KEY)
		return (mlx_loop_end(dt->mlx_ptr), 1);
	return (0);
}

int	put_color_and_string(t_data *dt, int x, int y, int *fixed_value)
{
	int		r;
	int		g;
	int		b;
	int		color;

	r = x * 255;
	if (r)
		r /= (WIN_X - 1);
	g = y * 255;
	if (g)
		g /= (WIN_Y - 1);
	b = *fixed_value;
	color = (r << 16) | (g << 8) | b;
	mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, color);
	*fixed_value = (*fixed_value + 1) % 256;
	return (0);
}

int	draw_color_panel(t_data *dt)
{
	int	x;
	int	y;
	int	fixed_value;

	if (!dt->mlx_ptr || !dt->win_ptr)
		return (printf("Error: Invalid data pointers\n"), 1);
	fixed_value = 0;
	x = -1;
	while (++x < WIN_X)
	{
		y = -1;
		while (++y < WIN_Y)
			put_color_and_string(dt, x, y, &fixed_value);
	}
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
