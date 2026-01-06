/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_maze_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:17:23 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/06 19:39:28 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	set_init_player(t_play *play, char c, int x, int y)
{
	if (c == 'E')
		set_player(play, x, y, 0.0);
	else if (c == 'N')
		set_player(play, x, y, 90.0);
	else if (c == 'W')
		set_player(play, x, y, 180.0);
	else
		set_player(play, x, y, 270.0);
}

t_maze	set_maze_and_player(const char **str_arr, t_play *player)
{
	t_maze	maze;
	int		mat_tot_len;
	int		x;
	int		y;

	maze.mat = NULL;
	maze.width = strlen(str_arr[0]);
	maze.height = 0;
	while (str_arr[maze.height])
	{
		if ((int)strlen(str_arr[maze.height]) != maze.width)
		{
			fprintf(stderr, "Inconsistent row lengths in maze definition.\n");
			return (maze.width = 0, maze.height = 0, maze);
		}
		maze.height++;
	}
	mat_tot_len = maze.width * maze.height;
	if (mat_tot_len <= 0)
		return (maze);
	maze.mat = malloc(sizeof(int) * mat_tot_len);
	if (!maze.mat)
		return (maze);
	x = -1;
	while (++x < maze.width)
	{
		y = -1;
		while (++y < maze.height)
		{
			if (char_in_str(str_arr[y][x], VALID_MAZE_CHARS))
			{
				if (char_in_str(str_arr[y][x], "NSEW"))
				{
					set_init_player(player, str_arr[y][x], x + 0.5, y + 0.5);
					maze.mat[y * maze.width + x] = 0;
				}
				else
					maze.mat[y * maze.width + x] = str_arr[y][x] - '0';
			}
			else
				return (free(maze.mat), maze.mat = NULL, maze.width = 0, \
					fprintf(stderr, "Invalid char:'%c'.\n", str_arr[y][x]), \
					maze.height = 0, maze);
		}
	}
	return (maze);
}

void	free_maze(t_maze *maze)
{
	if (maze->mat)
		free(maze->mat);
	maze->mat = NULL;
	maze->width = 0;
	maze->height = 0;
}

void	print_maze(t_maze maze)
{
	int	x;
	int	i;
	int	tot_size;

	printf("Maze [%d x %d]:\n", maze.width, maze.height);
	tot_size = maze.width * maze.height;
	if (!maze.mat || tot_size <= 0)
		printf("(empty).\n");
	else
	{
		i = -1;
		while (++i < tot_size)
		{
			x = i % maze.width;
			if (i && x == 0)
				printf("\n");
			printf("%c", maze.mat[i] + '0');
		}
		printf("\n");
	}
	printf("\n");
}
