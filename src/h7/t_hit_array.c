/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hit_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:24:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 06:22:55 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_hit	*create_hit_array(int size)
{
	t_hit	*array;
	int		i;

	array = (t_hit *)ft_calloc(size + 1, sizeof(t_hit));
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
		psf += printf(", dist:%.2f}, ", hit_arr[i].dist.x);
		i++;
	}
	return (psf += printf("NULL]"), psf);
}
