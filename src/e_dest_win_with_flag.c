/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_dest_win_with_flag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 16:02:36 by lagrondi          #+#    #+#             */
/*   Updated: 2025/12/28 20:08:53 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#define WIN_X 800
#define WIN_Y 400
#define WIN_TITLE "Window closable with [X]--> Destroy Window"
#define ESC_KEY 65307

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_should_be_destroyed;
}	t_data;

int		handle_loop(t_data *data);
int		increment_close_win_flag(t_data *data);
int		destroy_display_wrapper(t_data *data);
int		handle_input(int keycode, t_data *data);

/**
 * Displays a window that is closed by calling mlx_destroy_window() function:
 *  - Once the [X] button is clicked --> increment win_should_be_destroyed flag.
 *  - Once the [ESC] key is pressed down. --> increment win_should_be_destroyed flag.
 */
int	main(void)
{
	t_data	data;

	data.win_should_be_destroyed = 0;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_X, WIN_Y, WIN_TITLE);
	if (!data.win_ptr)
		return (destroy_display_wrapper(&data), 2);
	mlx_loop_hook(data.mlx_ptr, &handle_loop, &data);
	mlx_hook(data.win_ptr, 17, 0, &increment_close_win_flag, &data);
	mlx_hook(data.win_ptr, 2, (1L << 0), &handle_input, &data);
	mlx_loop(data.mlx_ptr);
	return (destroy_display_wrapper(&data), 0);
}

int	destroy_display_wrapper(t_data *data)
{
	if (!data || !data->mlx_ptr)
		return (1);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	data->mlx_ptr = NULL;
	return (0);
}

int	increment_close_win_flag(t_data *data)
{
	if (!data || !data->mlx_ptr)
		return (1);
	return (data->win_should_be_destroyed++, 0);
}

int	handle_input(int keycode, t_data *data)
{
	if (!data || !data->mlx_ptr)
		return (1);
	if (keycode == ESC_KEY)
		increment_close_win_flag(data);
	return (0);
}

/**
 * Loop hook that checks if window should be closed and destroys it safely
 * between event iterations, avoiding use-after-free inside mlx_loop.
 */
int	handle_loop(t_data *data)
{
	if (!data || !data->mlx_ptr || !data->win_ptr)
		return (1);
	if (data->win_should_be_destroyed && data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}
