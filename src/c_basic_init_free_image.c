/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_basic_init_free_image.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 16:02:36 by lagrondi          #+#    #+#             */
/*   Updated: 2025/12/28 12:26:17 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "stdlib.h"

int	main(void)
{
	void	*mlx_ptr;
	void	*img_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	img_ptr = mlx_new_image(mlx_ptr, 1920, 1080);
	if (!img_ptr)
		return (mlx_destroy_display(mlx_ptr), free(mlx_ptr), mlx_ptr = NULL, 2);
	return (mlx_destroy_image(mlx_ptr, img_ptr), img_ptr = NULL, \
			mlx_destroy_display(mlx_ptr), free(mlx_ptr), mlx_ptr = NULL, 0);
}
