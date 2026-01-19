/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pix_to_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:13:33 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/19 19:41:38 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * TODO-LIST: reorganise, optimize and factorize pixel writing functions.
 * -[x] use t_ipos struct. for position argument.
 * -[x] write two separate functions for little and big endian.
 * -[] add optimized version for bpp=32 only.
 *
 */

/**
 * NOTE: 
 * - while loop to handle any bpp (bits per pixel) value. (64,32,24,16...)
 * - void instead of int cause we will not check returns value on failure
 * NOT-OPTI:
 *  - while loop added overhead for bpp=32, could be optimized.
 */
void	put_pix_to_img_little_end(t_img *img, int x, int y, int color)
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
 * NOTE: 
 * - void instead of int cause we will not check returns value on failure
 * - while loop to handle any bpp (bits per pixel) value. (64,32,24,16...)
 * NOT-OPTI:
 * - while loop added overhead for bpp=32, could be optimized.
 */
void	put_pix_to_img_big_end(t_img *img, int x, int y, int color)
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
