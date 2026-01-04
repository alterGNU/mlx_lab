/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:11:46 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/04 20:50:30 by lagrondi         ###   ########.fr       */
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

int	mlx_xpm_cpy_src_in_dst(t_img *src, t_img *dst, int dst_x, int dst_y)
{
	int	x;
	int	y;
	int	bpp;
	int	src_pix;

	if (!dst || !src || !dst->addr || !src->addr || dst_x < 0 || dst_y < 0)
		return (printf("Invalid arguments\n"), 1);
	if (dst_x + src->width > dst->width || dst_y + src->height > dst->height)
		return (printf("Source image exceeds destination bounds\n"), 1);
	if (src->bpp != dst->bpp)
		return (printf("Different bpp not supported\n"), 1);
	bpp = dst->bpp / 8;
	x = -1;
	while (++x < src->height)
	{
		y = -1;
		while (++y < src->width)
		{
			src_pix = *(int *)(src->addr + (x * src->size_line + y * bpp));
			*(int *)(dst->addr + ((dst_y + x) * \
				dst->size_line + (dst_x + y) * bpp)) = src_pix;
		}	
	}
	return (0);
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
