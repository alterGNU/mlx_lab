/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_img_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:18:44 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/04 18:25:58 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_img	ft_load_image(void *mlx_ptr, const char *filename)
{
	t_img	img;

	img.img_ptr = NULL;
	img.addr = NULL;
	img.width = 0;
	img.height = 0;
	img.bpp = 0;
	img.size_line = 0;
	img.endian = -1;
	if (mlx_ptr && filename)
	{
		img.img_ptr = mlx_xpm_file_to_image(mlx_ptr, (char *)filename, \
			&img.width, &img.height);
		if (img.img_ptr)
			img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, \
				&img.size_line, &img.endian);
	}
	return (img);
}

t_img	ft_create_buffer_image(void *mlx_ptr, int width, int height)
{
	t_img	img;

	img.img_ptr = NULL;
	img.addr = NULL;
	img.width = width;
	img.height = height;
	img.bpp = 0;
	img.size_line = 0;
	img.endian = -1;
	if (mlx_ptr && width > 0 && height > 0)
	{
		img.img_ptr = mlx_new_image(mlx_ptr, width, height);
		if (img.img_ptr)
			img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, \
				&img.size_line, &img.endian);
	}
	return (img);
}

void	free_image(t_img img, void *mlx_ptr)
{
	if (mlx_ptr && img.img_ptr)
		mlx_destroy_image(mlx_ptr, img.img_ptr);
	img.img_ptr = NULL;
	img.addr = NULL;
	img.width = 0;
	img.height = 0;
	img.bpp = 0;
	img.size_line = 0;
	img.endian = -1;
}
