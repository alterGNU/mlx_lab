/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_basic_init_free_window.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 16:02:36 by lagrondi          #+#    #+#             */
/*   Updated: 2025/12/28 12:24:10 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "stdlib.h"

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, 800, 400, "Test Window");
	if (!win_ptr)
		return (mlx_destroy_display(mlx_ptr), free(mlx_ptr), mlx_ptr = NULL, 2);
	return (mlx_destroy_window(mlx_ptr, win_ptr), win_ptr = NULL, \
			mlx_destroy_display(mlx_ptr), free(mlx_ptr), mlx_ptr = NULL, 0);
}
