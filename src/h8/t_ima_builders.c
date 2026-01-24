/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ima_builders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:20:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 04:35:44 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	build_img_text(t_ima *img, int color)
{
	int	x;
	int	y;

	if (!img || !img->addr)
		return (0);
	x = -1;
	while (++x < img->width)
	{
		y = -1;
		while (++y < img->height)
			img->put_pix_to_img(img, x, y, color);
	}
	return (1);
}

int	build_img_floor(t_ima *img)
{
	int	x;
	int	y;

	if (!img || !img->addr)
		return (0);
	x = -1;
	while (++x < img->width)
	{
		y = -1;
		while (++y < img->height)
		{
			if (0 < x && x + 1 < img->width && 0 < y && y + 1 < img->height)
				img->put_pix_to_img(img, x, y, FLOOR2D_COLOR);
			else
				img->put_pix_to_img(img, x, y, WHITE_COLOR);
		}
	}
	return (1);
}

int	build_img_wall(t_ima *img)
{
	int	x;
	int	y;

	if (!img || !img->addr)
		return (0);
	x = -1;
	while (++x < img->width)
	{
		y = -1;
		while (++y < img->height)
		{
			if (0 < x && x + 1 < img->width && 0 < y && y + 1 < img->height)
				img->put_pix_to_img(img, x, y, WALL2D_COLOR);
		}
	}
	return (1);
}

int	build_img_grid(t_maze *maze, t_ima *grid, t_ima *floor, t_ima *wall)
{
	int		i;
	int		len;
	int		x;
	int		y;

	len = maze->width * maze->height;
	if (!maze || !maze->mat || !grid || !grid->addr || !floor || !wall)
		return (0);
	i = -1;
	while (++i < len)
	{
		y = i / maze->width;
		x = i % maze->width;
		if (maze->mat[i] == 1)
			t_ima_insert_rows_by_words(wall, grid, x * TILE_X, y * TILE_Y);
		else
			t_ima_insert_rows_by_words(floor, grid, x * TILE_X, y * TILE_Y);
	}
	return (1);
}

int	build_img_3d(t_ima *img, int ceil_color, int floor_color)
{
	int	x;
	int	y;
	int	horizon;

	horizon = img->height / 2;
	if (!img || !img->addr)
		return (0);
	x = -1;
	while (++x < img->width)
	{
		y = -1;
		while (++y < img->height)
		{
			if (y < horizon)
				img->put_pix_to_img(img, x, y, ceil_color);
			else
				img->put_pix_to_img(img, x, y, floor_color);
		}
	}
	return (1);
}
