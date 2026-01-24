/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dbuff_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:25:51 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 06:41:12 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	draw_buffer_3dimg(t_data *dt)
{
	t_ima	img_3d_temp;

	if (dt->maze.mat[(int)dt->player.pos.y * dt->maze.width + (int)dt->player.pos.x] == 0)
		img_3d_temp = dt->img_3d_out_temp;
	else
		img_3d_temp = dt->img_3d_ins_temp;
	if (!dup_t_ima_by_words(&img_3d_temp, &dt->img_3d_buffer))
		return (fprintf(stderr, "Error: dup_t_ima_by_words() failed\n"), free_data(dt), 1);
	if (DRAW_FUN_AUTO)
	{
		if (OPTI_MODE)
		{
			if (dt->txt_mode == 0)
				draw3d_obj_vlines_auto_le32(&dt->img_3d_buffer, dt->hits, dt->column_width);
			else if (dt->txt_mode == 1)
				draw3d_obj_texture_auto_le32(&dt->img_3d_buffer, dt->hits, dt->column_width);
			//else
			//	draw3d_obj_ima_xpm_auto_le32(&dt->img_3d_buffer, dt->hits, dt->column_width);
		}
		else
		{
			if (dt->txt_mode == 0)
				draw3d_obj_vlines_auto(&dt->img_3d_buffer, dt->hits, dt->column_width);
			else if (dt->txt_mode == 1)
				draw3d_obj_texture_auto(&dt->img_3d_buffer, dt->hits, dt->column_width);
			else
				draw3d_obj_ima_xpm_auto(&dt->img_3d_buffer, dt->hits, dt->column_width);
		}
	}
	else
	{
		if (OPTI_MODE)
		{
			if (dt->txt_mode == 0)
				draw3d_obj_vlines_le32(&dt->img_3d_buffer, dt->hits, dt->column_width);
			else if (dt->txt_mode == 1)
				draw3d_obj_texture_le32(&dt->img_3d_buffer, dt->hits, dt->column_width);
			//else
			//	draw3d_obj_ima_xpm_le32(&dt->img_3d_buffer, dt->hits, dt->column_width);
		}
		else
		{
			if (dt->txt_mode == 0)
				draw3d_obj_vlines(&dt->img_3d_buffer, dt->hits, dt->column_width);
			else if (dt->txt_mode == 1)
				draw3d_obj_texture(&dt->img_3d_buffer, dt->hits, dt->column_width);
			//else
			//	draw3d_obj_ima_xpm(&dt->img_3d_buffer, dt->hits, dt->column_width);
		}
	}
	return (0);
}
