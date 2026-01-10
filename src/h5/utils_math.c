/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:52:18 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/10 17:22:11 by lagrondi         ###   ########.fr       */
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
 * return ((int)ceilf(FOV / FOV_PRE)) --> IF FOV_PRE is RAY PER DEGREE
 * return ((int)(FOV / FOV_PRE) + 1)  --> IF FOV_PRE is STEP SIZE BETWEEN RAYS
 */
int	get_nb_of_rays(void)
{
	if (FOV_PRE >= FOV)
		return (1);
	return ((int)ceilf(FOV / FOV_PRE));
}
