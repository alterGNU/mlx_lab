/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hit_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:24:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/10 12:42:16 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_hit	set_hit(t_hit *hit, float x, float y, float angle)
{
	hit->valid = 1;
	hit->pos = init_pos(x, y);
	hit->angle = angle;
	return (*hit);
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
		set_hit(&array[i], -1.f, -1.f, -1.f);
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
		psf += printf("{");
		psf += print_pos(hit_arr[i].pos);
		psf += printf(", angle: %.2f}", hit_arr[i].angle);
		psf += printf(", ");
		i++;
	}
	return (psf += printf("NULL]"), psf);
}
