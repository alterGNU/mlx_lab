/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:52:18 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/08 17:07:15 by lagrondi         ###   ########.fr       */
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

	float	norm_angle(float angle)
{
	float	res;

	res = fmodf(angle, 360.0f);
	if (res < 0)
		res += 360.0f;
	return (res);
}
