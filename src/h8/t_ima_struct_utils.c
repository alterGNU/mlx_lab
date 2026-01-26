/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ima_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:18:44 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/26 07:04:01 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_img_valid(t_ima *img)
{
	if (!img)
		return (0);
	if (!img->img_ptr || !img->addr)
		return (0);
	if (img->dim.x <= 0 || img->dim.y <= 0)
		return (0);
	if (img->bpp <= 0 || img->size_line <= 0)
		return (0);
	if (img->endian < 0 || img->endian > 1)
		return (0);
	return (1);
}

// TODO: simplify conditions
void	set_ima_fun_ptrs(t_ima *img)
{
	if (img->bpp == 32)
		img->draw_txt_vlines = &draw_txt_vlines_32;
	else
		img->draw_txt_vlines = &draw_txt_vlines_gen;
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
