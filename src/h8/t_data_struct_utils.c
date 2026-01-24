/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:54:27 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 06:37:33 by lagrondi         ###   ########.fr       */
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

void	toggle_texture_mode(t_data *dt)
{
	dt->txt_mode = (dt->txt_mode + 1) % 3;
	set_txt_mode_str(dt);
}
