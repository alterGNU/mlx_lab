/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_texture_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:21:55 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/22 07:35:40 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// NOTE: replace with ft_calloc
t_text	*init_texture(int width, int height)
{
	t_text	*txt;

	if (width <= 0 || height <= 0)
		return (NULL);
	txt = (t_text *)malloc(sizeof(t_text));
	if (!txt)
		return (NULL);
	txt->dim = ipos_new(width, height);
	txt->size = width * height;
	txt->img = (int *)malloc(sizeof(int) * txt->size);
	if (!txt->img)
		return (free(txt), txt = NULL, NULL);
	return (txt);
}

void	free_texture(t_text **txt)
{
	if (txt && *txt)
	{
		if ((*txt)->img)
		{
			free((*txt)->img);
			(*txt)->img = NULL;
		}
		free(*txt);
		*txt = NULL;
	}
}