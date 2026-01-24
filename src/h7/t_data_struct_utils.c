/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:54:27 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/23 19:05:41 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// FIX-ME: can not use snprintf function
void	set_txt_mode_str(t_data *dt)
{
	if (WALL_TXT_MODE == 0)
		snprintf(dt->txt_mode_str, sizeof(dt->txt_mode_str), "color");
	else if (WALL_TXT_MODE == 1)
		snprintf(dt->txt_mode_str, sizeof(dt->txt_mode_str), "texture");
	else
		snprintf(dt->txt_mode_str, sizeof(dt->txt_mode_str), "image");
}
