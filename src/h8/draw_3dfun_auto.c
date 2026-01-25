/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dfun_auto.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/25 05:43:23 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// OPTI: better than everyone else...25FPS for 1024 rays
void	draw3d_obj_vlines_auto(t_ima *img, t_hit *hit, int col_width)
{
	int		i;
	int		j;
	t_ipos	y_inter;
	float	line_height;
	float	line_offset;

	y_inter = ipos_new(0, 0);
	i = 0;
	while (hit[i].valid)
	{
		line_height = hit[i].dim.y * img->dim.y / hit[i].dist.y;
		if (line_height > img->dim.y)
			line_height = img->dim.y;
		line_offset = (img->dim.y - line_height) / 2.0f;
		y_inter = ipos_new(line_offset, line_height + line_offset);
		if (y_inter.x < 0)
			y_inter.x = 0;
		if (y_inter.y > img->dim.y - 1)
			y_inter.y = img->dim.y - 1;
		j = 0;
		while (j < col_width)
			img->draw_vlines(img, i * col_width + j++, y_inter, hit[i].type.y);
		i++;
	}
}

// NOTE: suprisingly slower than draw3d_obj_vlines_auto()...lost ~3FPS
void	draw3d_obj_vlines_auto_le32(t_ima *img, t_hit *hit, int col_width)
{
	int		i;
	int		j;
	t_ipos	y_inter;
	float	line_height;
	float	line_offset;
	int		x;
	int		y;
	char	*pixel;

	y_inter = ipos_new(0, 0);
	i = 0;
	while (hit[i].valid)
	{
		line_height = hit[i].dim.y * img->dim.y / hit[i].dist.y;
		if (line_height > img->dim.y)
			line_height = img->dim.y;
		line_offset = (img->dim.y - line_height) / 2.0f;
		y_inter = ipos_new(line_offset, line_height + line_offset);
		if (y_inter.x < 0)
			y_inter.x = 0;
		if (y_inter.y > img->dim.y - 1)
			y_inter.y = img->dim.y - 1;
		j = -1;
		while (++j < col_width)
		{
			x = i * col_width + j;
			if (x < 0 || x >= img->dim.x)
				continue ;
			pixel = img->addr + (y_inter.x * img->size_line + x * 4);
			y = y_inter.x;
			while (y <= y_inter.y)
			{
				*(int *)pixel = hit[i].type.y;
				pixel += img->size_line;
				y++;
			}
		}
		i++;
	}
}

void	draw3d_obj_texture_auto(t_ima *img, t_hit *hit, int col_width)
{
	int		i;				// loop over hits (y axis)
	int		j;				// repeat column depending on col_width (x axis)
	t_text	*txt;			// cast->easier access to texture struct
	float	line_height;	// dst image line height-->used to compute y_inter,ty_step
	float	line_offset;	// dst image line offset-->where to start drawing line-->use to compute y_inter
	t_ipos	y_inter;		// dst image y start & y stop
	float	ty_step;		// y step on texture pixel column-->size of jump to next pixel in texture column
	float	ty_offset;		// y offset on texture pixel column-->where to start in texture
	int		index_text;		// src texture pixel index
	t_fpos	txt_pix;		// src texture pixel coord.
	int		color;			// color fetched from texture

	i = 0;
	while (hit[i].valid)
	{
		txt = hit[i].texture;
		line_height = hit[i].dim.y * img->dim.y / hit[i].dist.y;
		ty_step = (float)txt->dim.y / line_height;
		ty_offset = 0.f;
		if (line_height > img->dim.y)
		{
			ty_offset = (line_height - (float)img->dim.y) / 2.0f;
			line_height = (float)img->dim.y;
		}
		line_offset = (img->dim.y - line_height) / 2.0f;
		// compute y start & y stop in dst image
		y_inter.x = ft_imax(line_offset, 0);
		y_inter.y = ft_imin(line_height + line_offset, img->dim.y - 1);
		if (y_inter.x >= y_inter.y)
		{
			i++;
			continue ;
		}
		// compute texture x coord. & initial y coord. in texture
		if (hit[i].type.x % 2)
		{
			txt_pix.x = (float)(hit[i].pos.x - (int)hit[i].pos.x) * (float)txt->dim.x;
			if (hit[i].angle.x > 180.f)
				txt_pix.x = (float)txt->dim.x - txt_pix.x;
		}
		else
		{
			txt_pix.x = (float)(hit[i].pos.y - (int)hit[i].pos.y) * (float)txt->dim.x;
			if (90 < hit[i].angle.x && hit[i].angle.x < 270.f)
				txt_pix.x = (float)txt->dim.x - txt_pix.x;
		}
		txt_pix.y = ty_offset * ty_step;
		while (y_inter.x < y_inter.y)
		{
			index_text = (int)(txt_pix.y) * txt->dim.x + (int)(txt_pix.x);
			color = txt->img[ft_imax(0, ft_imin(index_text, txt->size - 1))];
			j = 0;
			while (j < col_width)
				img->put_pix_to_img(img, i * col_width + j++, y_inter.x, color);
			txt_pix.y += ty_step;
			y_inter.x++;
		}
		i++;
	}
}

void	draw3d_obj_texture_auto_le32(t_ima *img, t_hit *hit, int col_width)
{
	int		i;				// loop over hits (y axis)
	int		j;				// repeat column depending on col_width (x axis)
	t_text	*txt;			// cast->easier access to texture struct
	float	line_height;	// dst image line height-->used to compute y_inter,ty_step
	float	line_offset;	// dst image line offset-->where to start drawing line-->use to compute y_inter
	t_ipos	y_inter;		// dst image y start & y stop
	float	ty_step;		// y step on texture pixel column-->size of jump to next pixel in texture column
	float	ty_offset;		// y offset on texture pixel column-->where to start in texture
	int		index_text;		// src texture pixel index
	t_fpos	txt_pix;		// src texture pixel coord.
	int		color;			// color fetched from texture

	i = 0;
	while (hit[i].valid)
	{
		txt = hit[i].texture;
		line_height = hit[i].dim.y * img->dim.y / hit[i].dist.y;
		ty_step = (float)txt->dim.y / line_height;
		ty_offset = 0.f;
		if (line_height > img->dim.y)
		{
			ty_offset = (line_height - (float)img->dim.y) / 2.0f;
			line_height = img->dim.y;
		}
		line_offset = (img->dim.y - line_height) / 2.0f;
		// compute y start & y stop in dst image
		y_inter.x = ft_imax(line_offset, 0);
		y_inter.y = ft_imin(line_height + line_offset, img->dim.y - 1);
		if (y_inter.x >= y_inter.y)
		{
			i++;
			continue ;
		}
		// compute texture x coord. & initial y coord. in texture
		if (hit[i].type.x % 2)
		{
			txt_pix.x = (float)(hit[i].pos.x - (int)hit[i].pos.x) * (float)txt->dim.x;
			if (hit[i].angle.x > 180.f)
				txt_pix.x = (float)txt->dim.x - txt_pix.x;
		}
		else
		{
			txt_pix.x = (float)(hit[i].pos.y - (int)hit[i].pos.y) * (float)txt->dim.x;
			if (90 < hit[i].angle.x && hit[i].angle.x < 270.f)
				txt_pix.x = (float)txt->dim.x - txt_pix.x;
		}
		txt_pix.y = ty_offset * ty_step;
		while (y_inter.x < y_inter.y)
		{
			index_text = (int)(txt_pix.y) * txt->dim.x + (int)(txt_pix.x);
			color = txt->img[ft_imax(0, ft_imin(index_text, txt->size - 1))];
			j = -1;
			while (++j < col_width)
				((int *)(img->addr + y_inter.x * img->size_line))[i * col_width + j] = color;
			txt_pix.y += ty_step;
			y_inter.x++;
		}
		i++;
	}
}

void	draw3d_obj_ima_xpm_auto(t_ima *img, t_hit *hit, int col_width)
{
	int		i;
	int		j;
	int		y;
	t_ipos	y_inter;
	float	line_height;
	float	line_offset;
	float	ty_step;
	float	ty_offset;
	t_fpos	txt_pix;
	t_ima	*xpm;
	int		color;
	int		bytes_per_px;
	int		src_x;
	int		src_y;

	i = 0;
	while (hit[i].valid)
	{
		// precompute-----------------------------------------------------------------
		xpm = hit[i].ima_xpm;
		line_height = hit[i].dim.y * img->dim.y / hit[i].dist.y;
		ty_step = (float)xpm->dim.y / line_height;
		ty_offset = 0.f;
		if (line_height > img->dim.y)
		{
			ty_offset = (line_height - (float)img->dim.y) / 2.f;
			line_height = img->dim.y;
		}
		line_offset = (img->dim.y - line_height) / 2.0f;
		y_inter = ipos_new(line_offset, line_height + line_offset);
		y_inter.x = ft_imax(y_inter.x, 0);
		y_inter.y = ft_imin(y_inter.y, img->dim.y - 1);
		txt_pix.y = ty_offset * ty_step;
		if (hit[i].type.x % 2)
		{
			txt_pix.x = (float)(hit[i].pos.x - (int)hit[i].pos.x) * (float)xpm->dim.x;
			if (hit[i].angle.x > 180.f)
				txt_pix.x = (float)xpm->dim.x - txt_pix.x;
		}
		else
		{
			txt_pix.x = (float)(hit[i].pos.y - (int)hit[i].pos.y) * (float)xpm->dim.x;
			if (90 < hit[i].angle.x && hit[i].angle.x < 270.f)
				txt_pix.x = (float)xpm->dim.x - txt_pix.x;
		}
		// ------------------------------------------------------------------------------------------
		bytes_per_px = xpm->bpp / 8;
		y = y_inter.x;
		while (y < y_inter.y)
		{
			src_y = ft_imax(0, ft_imin((int)txt_pix.y, xpm->dim.y - 1));
			src_x = ft_imax(0, ft_imin((int)txt_pix.x, xpm->dim.x - 1));
			color = *(int *)(xpm->addr + (src_y * xpm->size_line + src_x * bytes_per_px));
			//color = *(int *)(xpm->addr + (txt_pix.y * xpm->size_line + txt_pix.x * bytes_per_px));
			j = 0;
			while (j < col_width)
				img->put_pix_to_img(img, i * col_width + j++, y, color);
			txt_pix.y += ty_step;
			y++;
		}
		i++;
	}
}

void	draw3d_obj_ima_xpm_auto_le32(t_ima *img, t_hit *hit, int col_width)
{
	int		i;
	int		y;
	t_ipos	y_inter;
	float	line_height;
	float	line_offset;
	float	ty_step;		// y step on texture pixel column-->size of jump to next pixel in texture column
	float	ty_offset;		// y offset on texture pixel column-->where to start in texture
	t_fpos	txt_pix;
	t_ima		*xpm;
	int		color;
	int		bytes_per_px;
	int		src_x;
	int		src_y;
	int		dst_stride;
	int		src_stride;

	i = 0;
	while (hit[i].valid)
	{
		// precompute-----------------------------------------------------------------
		xpm = hit[i].ima_xpm;
		line_height = hit[i].dim.y * img->dim.y / hit[i].dist.y;
		ty_step = (float)xpm->dim.y / line_height;
		ty_offset = 0.f;
		if (line_height > img->dim.y)
		{
			ty_offset = (line_height - (float)img->dim.y) / 2.f;
			line_height = img->dim.y;
		}
		line_offset = (img->dim.y - line_height) / 2.0f;
		y_inter = ipos_new(line_offset, line_height + line_offset);
		y_inter.x = ft_imax(y_inter.x, 0);
		y_inter.y = ft_imin(y_inter.y, img->dim.y - 1);
		txt_pix.y = ty_offset * ty_step;
		if (hit[i].type.x % 2)
		{
			txt_pix.x = (float)(hit[i].pos.x - (int)hit[i].pos.x) * (float)xpm->dim.x;
			if (hit[i].angle.x > 180.f)
				txt_pix.x = (float)xpm->dim.x - txt_pix.x;
		}
		else
		{
			txt_pix.x = (float)(hit[i].pos.y - (int)hit[i].pos.y) * (float)xpm->dim.x;
			if (90 < hit[i].angle.x && hit[i].angle.x < 270.f)
				txt_pix.x = (float)xpm->dim.x - txt_pix.x;
		}
		// ------------------------------------------------------------------------------------------
		bytes_per_px = xpm->bpp / 8;
		dst_stride = img->size_line;
		src_stride = xpm->size_line;
		src_x = ft_imax(0, ft_imin((int)txt_pix.x, xpm->dim.x - 1));
		y = y_inter.x;
		char *dst_row = img->addr + y * dst_stride + i * col_width * 4;
		while (y < y_inter.y)
		{
			src_y = ft_imax(0, ft_imin((int)txt_pix.y, xpm->dim.y - 1));
			color = *(int *)(xpm->addr + src_y * src_stride + src_x * bytes_per_px);
			int *dest = (int *)dst_row;
			for (int j = 0; j < col_width; ++j)
				dest[j] = color;
			txt_pix.y += ty_step;
			y++;
			dst_row += dst_stride;
		}
		i++;
	}
}
