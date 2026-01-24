/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ima_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:18:44 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 04:35:54 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	memset_zero_img(t_ima *img)
{
	img->img_ptr = NULL;
	img->addr = NULL;
	img->width = 0;
	img->height = 0;
	img->bpp = 0;
	img->size_line = 0;
	img->endian = 0;
	img->put_pix_to_img = NULL;
	img->draw_vlines = NULL;
	img->dark_filter = NULL;
}

void	set_ima_fun_ptrs(t_ima *img)
{
	if (img->endian == 0)
	{
		img->dark_filter = &dark_filter_little_end;
		if (img->bpp == 32)
		{
			img->put_pix_to_img = &put_pix_to_img_little_end_32;
			img->draw_vlines = &draw_vlines_little_end_32;
		}
		else
		{
			img->put_pix_to_img = &put_pix_to_img_little_end;
			img->draw_vlines = &draw_vlines_generic;
		}
	}
	else
	{
		img->put_pix_to_img = &put_pix_to_img_big_end;
		img->dark_filter = &dark_filter_big_end;
		img->draw_vlines = &draw_vlines_generic;
	}
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
			img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, \
				&img.size_line, &img.endian);
		img.width = width;
		img.height = height;
		set_ima_fun_ptrs(&img);
	}
	return (img);
}

//void	print_t_ima(t_ima img)
//{
//	printf("\n   - img_ptr:   %p", img.img_ptr);
//	printf("\n   - addr:      %p", img.addr);
//	printf("\n   - width:     %d", img.width);
//	printf("\n   - height:    %d", img.height);
//	printf("\n   - bpp:       %d", img.bpp);
//	printf("\n   - size_line: %d", img.size_line);
//	printf("\n   - endian:    %d\n", img.endian);
//}

void	free_image(t_ima img, void *mlx_ptr)
{
	if (mlx_ptr && img.img_ptr)
		mlx_destroy_image(mlx_ptr, img.img_ptr);
	memset_zero_img(&img);
}

int	is_img_valid(t_ima *img)
{
	if (!img)
		return (0);
	if (!img->img_ptr || !img->addr)
		return (0);
	if (img->width <= 0 || img->height <= 0)
		return (0);
	if (img->bpp <= 0 || img->size_line <= 0)
		return (0);
	if (img->endian < 0 || img->endian > 1)
		return (0);
	return (1);
}
