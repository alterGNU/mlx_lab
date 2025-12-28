/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_end_loop_destroy_window.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 16:02:36 by lagrondi          #+#    #+#             */
/*   Updated: 2025/12/28 16:39:08 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>

/**
 * Displays a window that can be closed by the destroy window function [X]
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
	mlx_hook(win_ptr, 17, 0, mlx_loop_end, mlx_ptr);
	mlx_loop(mlx_ptr);
	return (mlx_destroy_window(mlx_ptr, win_ptr), win_ptr = NULL, \
			mlx_destroy_display(mlx_ptr), free(mlx_ptr), mlx_ptr = NULL, 0);
}
