/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:52:18 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/16 00:10:27 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float	radian(float degree)
{
	return (degree * (M_PI / 180.0f));
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

float	norm_angle(float angle)
{
	float	res;

	res = fmodf(angle, 360.0f);
	if (res < 0)
		res += 360.0f;
	return (res);
}

/**
 * Makes sure that the number of rays is appropriate according to:
 *  - FOV and FOV_PRE
 *  - WIN3D_WIDTH
 */
int	get_nb_of_rays(void)
{
	int	nb_rays;

	if (FOV_PRE <= 0 || FOV_PRE >= FOV)
		return (1);
	nb_rays = (int)(FOV / FOV_PRE);
	if (nb_rays > WIN3D_WIDTH)
		nb_rays = WIN3D_WIDTH;
	return (nb_rays);
}
