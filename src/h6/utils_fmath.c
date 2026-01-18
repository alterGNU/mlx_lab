/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fmath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:52:18 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 11:30:18 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float	ft_fmax(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	ft_fmin(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_fabs(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

float	radian(float degree)
{
	return (degree * (M_PI / 180.0f));
}

float	norm_angle(float angle)
{
	float	res;

	res = fmodf(angle, 360.0f);
	if (res < 0)
		res += 360.0f;
	return (res);
}
