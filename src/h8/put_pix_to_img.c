/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pix_to_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:33 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 04:34:35 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * NOTE: 
 * - & 0xFF is a bitwise AND mask to extract only the least significant byte.
 * - while loop to handle any bpp (bits per pixel) value. (64,32,24,16...)
 * - void instead of int cause we will not check returns value on failure
 */
void	put_pix_to_img_little_end(t_ima *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (0 <= x && x < img->width && 0 <= y && y < img->height)
	{
		pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
		i = img->bpp - 8;
		while (i >= 0)
		{
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

/**
 * OPTI: optimized version for bpp=32 only.
 * NOTE: *(int *)(img->addr + (y * img->size_line + x * 4)) = color;
 * is faster than the 4 setting line:
 *  pixel = img->addr + (y * img->size_line + x * 4);
 *  pixel[0] = (color >> 0) & 0xFF;
 *  pixel[1] = (color >> 8) & 0xFF;
 *  pixel[2] = (color >> 16) & 0xFF;
 *  pixel[3] = (color >> 24) & 0xFF;
 */
void	put_pix_to_img_little_end_32(t_ima *img, int x, int y, int color)
{
	if (0 <= x && x < img->width && 0 <= y && y < img->height)
		*(int *)(img->addr + (y * img->size_line + x * 4)) = color;
}

/**
 * NOTE: 
 * - & 0xFF is a bitwise AND mask to extract only the least significant byte.
 * - void instead of int cause we will not check returns value on failure
 * - while loop to handle any bpp (bits per pixel) value. (64,32,24,16...)
 */
void	put_pix_to_img_big_end(t_ima *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (0 <= x && x < img->width && 0 <= y && y < img->height)
	{
		pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
		i = img->bpp - 8;
		while (i >= 0)
		{
			*pixel++ = (color >> i) & 0xFF;
			i -= 8;
		}
	}
}

/**
 * OPTI: optimized version for bpp=32 only.
 */
void	put_pix_to_img_big_end_32(t_ima *img, int x, int y, int color)
{
	char	*pixel;

	if (0 <= x && x < img->width && 0 <= y && y < img->height)
	{
		pixel = img->addr + (y * img->size_line + x * 4);
		pixel[0] = (color >> 24) & 0xFF;
		pixel[1] = (color >> 16) & 0xFF;
		pixel[2] = (color >> 8) & 0xFF;
		pixel[3] = (color >> 0) & 0xFF;
	}
}
