/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:54:27 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 19:08:15 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// FIX-ME: can not use snprintf function
// ADD: image mode "image" later (replace texture mode)
void	set_txt_mode_str(t_data *dt)
{
	if (dt->txt_mode == 1)
		snprintf(dt->txt_mode_str, sizeof(dt->txt_mode_str), "texture");
	else if (dt->txt_mode == 2)
		snprintf(dt->txt_mode_str, sizeof(dt->txt_mode_str), "image");
	else
		snprintf(dt->txt_mode_str, sizeof(dt->txt_mode_str), "color");
}

void	set_funcalled(t_data *dt)
{
	if (DRAW_FUN_AUTO)
	{
		if (OPTI_MODE)
		{
			if (dt->txt_mode == 1)
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_texture_auto_le32()");
			else if (dt->txt_mode == 2)
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_ima_xpm_auto_le32()");
			else
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_vlines_auto_le32()");
		}
		else
		{
			if (dt->txt_mode == 1)
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_texture_auto()");
			else if (dt->txt_mode == 2)
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_ima_xpm_auto()");
			else
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_vlines_auto()");
		}
	}
	else
	{
		if (OPTI_MODE)
		{
			if (dt->txt_mode == 1)
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_texture_le32()");
			else if (dt->txt_mode == 2)
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_ima_xpm_le32()");
			else
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_vlines_le32()");
		}
		else
		{
			if (dt->txt_mode == 1)
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_texture()");
			else if (dt->txt_mode == 2)
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_ima_xpm()");
			else
				snprintf(dt->funcalled, sizeof(dt->funcalled), "draw3d_obj_vlines()");
		}
	}
}

void	toggle_texture_mode(t_data *dt)
{
	dt->txt_mode = (dt->txt_mode + 1) % 3;
	set_txt_mode_str(dt);
	set_funcalled(dt);
	update_hit_tpos(dt); // NOTE: NEEDED TO AVOIR OFFSET WHEN MOVING WHILE TOGGLING MODE
}
