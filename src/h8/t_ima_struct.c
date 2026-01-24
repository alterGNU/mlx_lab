/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ima_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:18:44 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 07:04:51 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	memset_zero_img(t_ima *img)
{
	img->id[0] = '\0';
	img->id[1] = '\0';
	img->id[2] = '\0';
	img->path = NULL;
	img->img_ptr = NULL;
	img->addr = NULL;
	img->dim.x = 0;
	img->dim.y = 0;
	img->bpp = 0;
	img->size_line = 0;
	img->endian = 0;
	img->put_pix_to_img = NULL;
	img->draw_vlines = NULL;
	img->dark_filter = NULL;
}

t_ima	create_image(void *mlx_ptr, int width, int height)
{
	t_ima	img;

	memset_zero_img(&img);
	img.endian = -1;
	if (mlx_ptr && width > 0 && height > 0)
	{
		img.img_ptr = mlx_new_image(mlx_ptr, width, height);
		if (img.img_ptr)
		{
			img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, \
				&img.size_line, &img.endian);
			set_ima_fun_ptrs(&img);
		}
		img.dim.x = width;
		img.dim.y = height;
	}
	return (img);
}

// NOTE: can be malloc too...do not forget to adapt panic button.
t_ima	*open_image(t_data *dt, const char *path)
{
	t_ima	*img;

	if (!path)
		return (NULL);
	img = (t_ima *)malloc(sizeof(t_ima));
	if (!img)
		return (NULL);
	memset_zero_img(img);
	img->path = ft_strdup((char *)path);
	if (!img->path)
		return (ft_free((void **)&img->path), ft_free((void **)&img), NULL);
	img->endian = -1;
	if (dt->mlx_ptr)
	{
		img->img_ptr = mlx_xpm_file_to_image(dt->mlx_ptr, img->path, \
			&img->dim.x, &img->dim.y);
		if (!img->img_ptr)
			return (ft_free((void **)&img->path), ft_free((void **)&img), NULL);
		img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, \
			&img->endian);
		set_ima_fun_ptrs(img);
	}
	return (img);
}

void	set_wall_image(t_data *dt, const char *id, const char *path)
{
	if (ft_strncmp(id, "NO", 3) == 0)
		dt->ima_north = open_image(dt, path);
	else if (ft_strncmp(id, "SO", 3) == 0)
		dt->ima_south = open_image(dt, path);
	else if (ft_strncmp(id, "EA", 3) == 0)
		dt->ima_east = open_image(dt, path);
	else if (ft_strncmp(id, "WE", 3) == 0)
		dt->ima_west = open_image(dt, path);
	else if (ft_strncmp(id, "VI", 3) == 0)
		dt->ima_vins = open_image(dt, path);
	else if (ft_strncmp(id, "HI", 3) == 0)
		dt->ima_hins = open_image(dt, path);
}

void	free_image(t_ima img, void *mlx_ptr)
{
	if (mlx_ptr && img.img_ptr)
	{
		if (img.path)
		{
			free(img.path);
			img.path = NULL;
		}
		mlx_destroy_image(mlx_ptr, img.img_ptr);
	}
	memset_zero_img(&img);
}
