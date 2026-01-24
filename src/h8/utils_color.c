/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:11:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/20 05:10:52 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	dark_filter_little_end(int color, float darkness_factor)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = (color >> 0) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 16) & 0xFF;
	a = (color >> 24) & 0xFF;
	r = (int)(r * darkness_factor);
	g = (int)(g * darkness_factor);
	b = (int)(b * darkness_factor);
	return ((a << 24) | (b << 16) | (g << 8) | r);
}

int	dark_filter_big_end(int color, float darkness_factor)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = (color >> 0) & 0xFF;
	r = (int)(r * darkness_factor);
	g = (int)(g * darkness_factor);
	b = (int)(b * darkness_factor);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
