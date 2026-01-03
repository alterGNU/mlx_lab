/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pixBypix_randcolor_slow.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:54:43 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/03 16:22:49 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Display a random color image using mlx_pixel_put() in mlx_loop_hook()
 * -> draws pixel by pixel directly on window (slow version).
 * 
 * - IMPLEMENTATION:
 *   - Clean exit on [ESC] key or window close (using mlx_loop_end())
 *   - Use mlx_pixel_put() in the mlx_loop_hook():
 *     - Instead of drawing the entire panel at once, it updates each pixel 
 *       individually resulting in a slow rendering effect.
 * - OBSERVATIONS:
 *   - This approach is inefficient and results in a very slow rendering.
 *   - Events can be ignored if occured during the drawing process. 
 */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESC_KEY 65307
#define WIN_X 1024
#define WIN_Y 1024
#define WIN_TITLE "Random Color Panel (SLOW)"
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
			mlx_pixel_put(dt->mlx_ptr, dt->win_ptr, x, y, color);
	}
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
