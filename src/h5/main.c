/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:19:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/10 17:23:56 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


static void	print_start_infos(t_data dt, const char **str_arr, int bui_delay_ms)
{
	printf("\n======== STARTING INFOS ===========\n");
	printf(" - MEM_BLOCK_TYPE = words --> %d ms\n", bui_delay_ms);
	printf(" - String array:\n");
	print_str_array(str_arr);
	printf("\n");
	print_maze(dt.maze);
	printf(" - t_img floor: ");
	print_t_img(dt.img_floor);
	printf(" - t_img wall:  ");
	print_t_img(dt.img_wall);
	printf(" - t_img buff:  ");
	print_t_img(dt.img_buffer);
	printf(" - Tile size: %d x %d pixels\n", TILE_X, TILE_Y);
	printf(" - Window size: %d x %d pixels\n", dt.maze.width * TILE_X, dt.maze.height * TILE_Y);
	printf(" - Start ");
	print_player(dt.player);
	printf("\n - Flags =[%s] ", dt.mv_flags);
	printf("\n - FOV=%.2f / FOV_PRE=%.2f --> %d\n", FOV, FOV_PRE, get_nb_of_rays());
	//printf(" - dt.hit_tpos = ");
	//print_hit_array(dt.hits);
	printf("\n====================================\n\n");
}

static void	print_end_infos(t_data dt, t_pos start_pos,  int duration_ms, int bui_delay_ms)
{
	float	avg_fps;

	avg_fps = (float)dt.img_drawn / duration_ms * 1000.0f;
	printf("\n========== ENDING INFOS ==========\n");
	printf(" - Duration: %.2f seconds\n", duration_ms / 1000.0f);
	printf(" - Total Image: %d images drawn\n", dt.img_drawn);
	printf(" - MEM_BLOCK_TYPE = words\n   --> %d ms\n", bui_delay_ms);
	printf("   --> Average FPS=%.2f vs %d=FPS setted\n", avg_fps, FPS);
	printf(" - Player:\n");
	printf("  - %d steps taken\n", dt.player.step_count);
	printf("  - from ");
	print_pos(start_pos);
	printf("\n  - to   ");
	print_pos(dt.player.pos);
	printf("\n - Flags =[%s] ", dt.mv_flags);
	printf("\n - FOV=%.2f / FOV_PRE=%.2f --> %d\n", FOV, FOV_PRE, get_nb_of_rays());
	//printf(" - dt.hit_tpos = ");
	//print_hit_array(dt.hits);
	printf("\n====================================\n\n");
}

int	main(void)
{
	t_pos			start_pos;
	t_data			dt;
	struct timeval	prog_start_time;
	struct timeval	prog_end_time;
	struct timeval	start_bui;
	struct timeval	end_bui;
	int				bui_delay_ms;
	int				ms_duration;
	/*
	const char *str_arr[] = {
		"111111111111111111111111111111111111111111111111111111111",
		"100000000000000000000000000000000000000000000000000000001",
		"101111111111111111111111111111111111111111111111111111101",
		"101000000000000000000000000000000000000000000000000000001",
		"101001111000001111000000111100000111100011110111111110001",
		"101001111000001111000000111100000111100011110111111110001",
		"101001111000001111000000111100000111100011110111111110001",
		"101000000000000000000000000000000000000000000000000000001",
		"101000000000000000000000000000000000000000000000000000001",
		"101001111000001111000000111100000111100011110111111110001",
		"101001111000001111000000111100000111100011110111111110001",
		"101001111000001111000000111100000111100011110111111110001",
		"101000000000000000000000000000000000000000000000000000001",
		"101000000000000000000000000000000000000000000000000000001",
		"101001111000001111000000111100000111100011110111111110001",
		"101001111000001111000000111100000111100011110111111110001",
		"101001111000001111000000111100000111100011110111111110001",
		"101000000000000000000000000000000000000000000000000000001",
		"10100000000000000000000000N000000000000000000000000000001",
		"101000000000000000000000000000000000000000000000000000001",
		"101001111000001111000000111100000111100011110111111110001",
		"101001111000001111000000111100000111100011110111111110001",
		"101001111000001111000000111100000111100011110111111110001",
		"101000000000000000000000000000000000000000000000000000001",
		"101000000000000000000000000000000000000000000000000001001",
		"111111111111111111111111110011111011111111111111111111111",
		"101000000000000000000000000000000000000000000000000000001",
		"101000000000000000000000001000000000000000000000000001001",
		"101000000000000000000000000000000000000000000000000000001",
		"101000001000000000000000000000000000000000000000000000001",
		"101000000000000000000000000000000000000000000000000001001",
		"101000000000000000010000001000000000000000000000000001001",
		"101000000000000000000000000000000000000000000000000001001",
		"101000001000000000000000000000000000000000000000000001001",
		"101000000000000000000000000000000000001100001000000001001",
		"100000000000000000010000000000000000000000000000000000001",
		"111111111111111111111111111111111111111111111111111111111",
		NULL};
		const char *str_arr[] = {
		"111111111",
		"100000001",
		"101000101",
		"100000001",
		"100000E01",
		"100000001",
		"100010001",
		"100000001",
		"101101101",
		"101101101",
		"100000001",
		"111111111",
		NULL};
	*/
	const char	*str_arr[] = { \
		"00000", \
		"00000", \
		"00E01", \
		"00000", \
		"00000", \
		NULL };
	gettimeofday(&prog_start_time, NULL);
	dt = init_data(str_arr);
	//------------------------------------------------------TODO REMOVE
	set_player(&dt.player, 0.0f, dt.maze.height, 45.0f);
	//set_player(&dt.player, 3.0f, 2.0f, 45.0f);
	//------------------------------------------------------TODO REMOVE
	if (error_detected_after_init_data(&dt))
		return (free_data(&dt), 1);
	if (!build_img_floor(&dt.img_floor))
		return (fprintf(stderr, "Error: build_img_floor() failed\n"), free_data(&dt), 1);
	if (!build_img_wall(&dt.img_wall))
		return (fprintf(stderr, "Error: build_img_wall() failed\n"), free_data(&dt), 1);
	gettimeofday(&start_bui, NULL);
	if (!build_img_grid(&dt.maze, &dt.img_grid, &dt.img_floor, &dt.img_wall))
		return (fprintf(stderr, "Error: build_img_grid() failed\n"), free_data(&dt), 1);
	gettimeofday(&end_bui, NULL);
	bui_delay_ms = diff_time_in_ms(start_bui, end_bui);
	print_start_infos(dt, str_arr, bui_delay_ms);
	start_pos = dup_pos(dt.player.pos);
	update_hit_tpos(&dt);
	mlx_loop_hook(dt.mlx_ptr, &main_loop, &dt);
	mlx_hook(dt.win_ptr, 17, 0, &mlx_loop_end, dt.mlx_ptr);
	mlx_hook(dt.win_ptr, 2, (1L << 0), &key_pressed, &dt);
	mlx_hook(dt.win_ptr, 3, (1L << 1), &key_released, &dt);
	mlx_loop(dt.mlx_ptr);
	gettimeofday(&prog_end_time, NULL);
	ms_duration = diff_time_in_ms(prog_start_time, prog_end_time);
	print_end_infos(dt, start_pos, ms_duration, bui_delay_ms);
	return (free_data(&dt), 0); 
}
