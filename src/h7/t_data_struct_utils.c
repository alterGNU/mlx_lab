/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:54:27 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 06:29:26 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_txt_mode_str(t_data *dt)
{
	if (dt->txt_mode == 0)
		snprintf(dt->txt_mode_str, sizeof(dt->txt_mode_str), "color");
	else
		snprintf(dt->txt_mode_str, sizeof(dt->txt_mode_str), "texture");
	//	snprintf(dt->txt_mode_str, sizeof(dt->txt_mode_str), "image");
}

void	toggle_texture_mode(t_data *dt)
{
	dt->txt_mode = (dt->txt_mode + 1) % 2;
	set_txt_mode_str(dt);
}
