/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pos_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:24:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/08 21:46:32 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_pos	**create_pos_array(int size)
{
	t_pos	**pos_arr;
	int		i;

	pos_arr = (t_pos **)calloc(size + 1, sizeof(t_pos *));
	if (!pos_arr)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		pos_arr[i] = (t_pos *)malloc(sizeof(t_pos));
		if (!pos_arr[i])
			return (free_pos_array(&pos_arr), NULL);
		*pos_arr[i] = init_pos(0.0f, 0.0f);
	}
	return (pos_arr);
}

void	free_pos_array(t_pos ***pos_arr)
{
	int	i;

	if (!pos_arr || !*pos_arr)
		return ;
	i = -1;
	while ((*pos_arr)[++i])
	{
		free((*pos_arr)[i]);
		(*pos_arr)[i] = NULL;
	}
	free(*pos_arr);
	*pos_arr = NULL;
}

int	print_pos_array(t_pos **pos_arr)
{
	int	i;
	int	psf;

	psf = printf("pos_arr:");
	if (!pos_arr)
		return (psf += printf("NULL\n"), psf);
	psf += printf("[");
	i = 0;
	while (pos_arr[i])
	{
		psf += print_pos(*pos_arr[i]);
		psf += printf(", ");
		i++;
	}
	return (psf += printf("NULL]"), psf);
}
