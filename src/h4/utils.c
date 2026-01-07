/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:11:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/06 23:26:46 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	char_in_str(char c, const char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

void	print_str_array(const char **str_arr)
{
	int	i;

	i = 0;
	printf("[");
	while (str_arr[i])
	{
		if (i)
			printf(" ");
		printf("\"%s\", \n", str_arr[i]);
		i++;
	}
	printf("  NULL ]\n");
}

int	diff_time_in_ms(struct timeval start, struct timeval end)
{
	int	sec_diff;
	int	usec_diff;

	sec_diff = end.tv_sec - start.tv_sec;
	usec_diff = end.tv_usec - start.tv_usec;
	return (sec_diff * 1000 + usec_diff / 1000);
}

int	convert_fps_to_frame_delay(int fps)
{
	if (fps <= 0)
		return (0);
	return (1000 / fps);
}

float	radian(float degree)
{
	return (degree * (M_PI / 180.0f));
}
