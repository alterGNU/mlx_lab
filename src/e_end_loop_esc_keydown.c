/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_end_loop_esc_keydown.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 16:02:36 by lagrondi          #+#    #+#             */
/*   Updated: 2025/12/28 17:33:09 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#define ESC 65307

int	escape_pressed(int key_code, void *mlx_ptr);

/**
 * Displays a window that can be closed by pressing down ESCAPE key
 * 
 * Calls mlx_loop_end() to exit the loop, then clean all data.
 */
int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, 800, 400, "Functionnal ESC Key");
	if (!win_ptr)
		return (mlx_destroy_display(mlx_ptr), free(mlx_ptr), mlx_ptr = NULL, 2);
	mlx_hook(win_ptr, 2, (1L << 0), escape_pressed, mlx_ptr);
	mlx_loop(mlx_ptr);
	return (mlx_destroy_window(mlx_ptr, win_ptr), win_ptr = NULL, \
			mlx_destroy_display(mlx_ptr), free(mlx_ptr), mlx_ptr = NULL, 0);
}

int	escape_pressed(int key_code, void *mlx_ptr)
{
	if (key_code == ESC)
		mlx_loop_end(mlx_ptr);
	return (0);
}
