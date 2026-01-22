/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hit_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:24:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/22 09:04:47 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_hit	init_hit(void)
{
	t_hit	hit;

	hit.valid = 1;
	hit.type = ipos_new(0, -1);
	hit.pos = fpos_new(-1.f, -1.f);
	hit.dim = fpos_new(0.f, 0.f);
	hit.angle = fpos_new(-1.f, -1.f);
	hit.tan_angle = 0.f;
	hit.distance = 0.f;
	hit.dist_corr = 0.f;
	hit.texture = NULL;
	return (hit);
}

t_hit	*create_hit_array(int size)
{
	t_hit	*array;
	int		i;

	array = (t_hit *)calloc(size + 1, sizeof(t_hit));
	if (!array)
		return (NULL);
	i = -1;
	while (++i <= size)
		array[i] = init_hit();
	array[size].valid = 0;
	return (array);
}

void	free_hit_array(t_hit **hit_arr)
{
	if (!hit_arr || !*hit_arr)
		return ;
	free(*hit_arr);
	*hit_arr = NULL;
}

int	print_hit_array(t_hit *hit_arr)
{
	int	i;
	int	psf;

	if (!hit_arr)
		return (printf("NULL\n"));
	psf = printf("[");
	i = 0;
	while (hit_arr[i].valid)
	{
		psf += printf("{pos");
		psf += fpos_print(hit_arr[i].pos);
		psf += printf(", ang");
		psf += fpos_print(hit_arr[i].angle);
		psf += printf(", dist:%.2f}, ", hit_arr[i].distance);
		i++;
	}
	return (psf += printf("NULL]"), psf);
}

//void	set_hit_type(t_hit *hit, int type, int color, float height)
//{
//	hit->type.x = type;
//	hit->type.y = color;
//	hit->dim.x = 1.0f;
//	hit->dim.y = height;
//}

void	set_hit_type(const t_data *dt, t_hit *hit, int type)
{
	hit->type.x = type;
	hit->dim.x = 1.0f;
	hit->dim.y = 1.f;
	if (type < 0)
	{
		hit->dim.y = 0.8f;
		if (type % 2)
			hit->texture = dt->txt_v;
		else
			hit->texture = dt->txt_h;
	}
	if (type == NOW)
		hit->texture = dt->txt_north;
	if (type == SOW)
		hit->texture = dt->txt_south;
	if (type == EOW)
		hit->texture = dt->txt_east;
	if (type == WOW)
		hit->texture = dt->txt_west;
}
