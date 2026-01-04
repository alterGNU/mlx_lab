/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:19:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/04 20:51:55 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * FEATURES:
 * Movable player represented by a red dot (bresenham red circle) using [AWSD]:
 * - Grid-Based-movement: no-orientation param.
 * - Ghost-mode: no-collision detection.
 * - Drawing optimization flag to draw only when needed (FAILURE:busy-spin-loop)
 * OBJECTIFS:
 *  - being able to move a player in the maze (red dot silly player).
 *  - draw only when needed: _(~optimization->less mallocs when player static)_
 *    - at start.
 *    - when player's position changes.
 * IMPLEMENTATION:
 *  - Add a t_play struct with a t_pos member, an int color and radius.
 *  - Add Keyboard hook: _(while being pressed)_
 *    - `[W]` -> step forward
 *    - `[S]` -> step backward.
 *    - `[D]` -> step on the right.
 *    - `[A]` -> step on the left.
 * - OBSERVATIONS:
 *  - Everything works as intended, except for the flag optimization...
 *  - Unfortunately, using a simple int flag to indicate whether to redraw create
 *    a to speed loop increasing significantly the memory allocations usage.
 */

#include "header.h"

static void	print_start_infos(t_data dt, const char **str_arr)
{
	printf("\n======== STARTING INFOS ===========\n");
	printf(" - String array:\n");
	print_str_array(str_arr);
	printf("\n");
	print_maze(dt.maze);
	printf(" - Tile size: %d x %d pixels\n", TILE_X, TILE_Y);
	printf(" - Window size: %d x %d pixels\n", dt.maze.width * TILE_X, \
		dt.maze.height * TILE_Y);
	printf(" - Start ");
	print_player(dt.player);
	printf("\n====================================\n\n");
}

static void	print_end_infos(t_data dt, t_pos start_pos, \
	struct timeval start, struct timeval end)
{
	float	avg_fps;
	float	ms_duration;

	ms_duration = diff_time_in_ms(start, end);
	avg_fps = (float)dt.img_drawn / ms_duration * 1000.0f;
	printf("\n========== ENDING INFOS ==========\n");
	printf(" - Duration: %.2f seconds\n", ms_duration / 1000.0f);
	printf(" - Total Image: %d images drawn\n", dt.img_drawn);
	printf(" - Average FPS=%.2f vs %d=FPS setted\n", avg_fps, FPS);
	printf(" - Player:\n");
	printf("  - %d steps taken\n", dt.player.step_count);
	printf("  - from ");
	print_pos(start_pos);
	printf("\n  - to   ");
	print_pos(dt.player.pos);
	printf("\n====================================\n\n");
}

int	main(void)
{
	t_pos			start_pos;
	t_data			dt;
	struct timeval	start_time;
	struct timeval	end_time;

	const char	*str_arr[] = { \
		"1111111111", \
		"1000000001", \
		"1011111101", \
		"1000000101", \
		"1111010101", \
		"1000010001", \
		"1011110101", \
		"10000000P1", \
		"1111111111", \
		NULL };
	gettimeofday(&start_time, NULL);
	dt = init_data(str_arr);
	if (error_detected_after_init_data(&dt))
		return (free_data(&dt), 1);
	print_start_infos(dt, str_arr);
	start_pos = dup_pos(dt.player.pos);
	mlx_loop_hook(dt.mlx_ptr, &draw_buffer_image, &dt);
	mlx_hook(dt.win_ptr, 17, 0, &mlx_loop_end, dt.mlx_ptr);
	mlx_hook(dt.win_ptr, 2, (1L << 0), &handle_key, &dt);
	mlx_loop(dt.mlx_ptr);
	gettimeofday(&end_time, NULL);
	print_end_infos(dt, start_pos, start_time, end_time);
	return (free_data(&dt), 0);
}
