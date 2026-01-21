/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:00:58 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/21 03:46:32 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_movement_flags(t_data *dt)
{
	dt->mv_flags[0] = 'q';
	dt->mv_flags[1] = 'w';
	dt->mv_flags[2] = 'e';
	dt->mv_flags[3] = 'a';
	dt->mv_flags[4] = 's';
	dt->mv_flags[5] = 'd';
	dt->mv_flags[6] = '\0';
}

int	key_pressed(int keycode, t_data *dt)
{
	if (keycode == ESC_KEY)
		return (mlx_loop_end(dt->mlx_ptr), 1);
	if (keycode == Q_KEY || keycode == LA_KEY)
		return (dt->mv_flags[0] = 'Q', 1);
	if (keycode == W_KEY)
		return (dt->mv_flags[1] = 'W', 1);
	if (keycode == E_KEY || keycode == RA_KEY)
		return (dt->mv_flags[2] = 'E', 1);
	if (keycode == A_KEY)
		return (dt->mv_flags[3] = 'A', 1);
	if (keycode == S_KEY)
		return (dt->mv_flags[4] = 'S', 1);
	if (keycode == D_KEY)
		return (dt->mv_flags[5] = 'D', 1);
	if (keycode == G_KEY)
		return (toggle_player_mode(&dt->player), 1);
	return (0);
}

int	key_released(int keycode, t_data *dt)
{
	if (keycode == Q_KEY || keycode == LA_KEY)
		return (dt->mv_flags[0] = 'q', 1);
	if (keycode == W_KEY)
		return (dt->mv_flags[1] = 'w', 1);
	if (keycode == E_KEY || keycode == RA_KEY)
		return (dt->mv_flags[2] = 'e', 1);
	if (keycode == A_KEY)
		return (dt->mv_flags[3] = 'a', 1);
	if (keycode == S_KEY)
		return (dt->mv_flags[4] = 's', 1);
	if (keycode == D_KEY)
		return (dt->mv_flags[5] = 'd', 1);
	return (1);
}
