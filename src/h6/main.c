/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:19:14 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/18 16:32:58 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	print_start_infos(t_data dt, const char **str_arr, int bui_delay_ms)
{
	(void)dt;
	(void)str_arr;
	(void)bui_delay_ms;
	printf("\n===================== STARTING INFOS ========================\n");
	printf(" - Time to build images --> %d ms\n", bui_delay_ms);
	printf(" - Window:\n");
	printf("   ├╌╌╌┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄%4d p ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n", (int)dt.win_dim.x);
	printf("   ┌──────────────┲━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓  ┬\n");
	printf("   │ Player infos ┃ 🡴Insert img3d                   ┃  ┆\n");
	printf("   │ FPS          ┃  (%04d, %04d)                   ┃  ┆\n", (int)dt.start3d.x, (int)dt.start3d.y);
	printf("   │ Hit[0] infos ┃                                 ┃  ┆\n");
	printf("   │ .....        ┃                                 ┃  ┆\n");
	printf("   │ Hit[i] infos ┃                                 ┃  ┆\n");
	printf("   │              ┃                                 ┃  ┆\n");
	printf("   │ (%04d, %04d) ┃              %4d               ┃%4d p\n", (int)dt.start2d.x, (int)dt.start2d.y, (int)dt.img_3d_buffer.width, (int)dt.win_dim.y);
	printf("   │ 🡷Insert img2d┃                ╳                ┃  ┆\n");
	printf("   ┢━━━━━━━━━━━━━━┫              %4d               ┃  ┆\n",  (int)dt.img_3d_buffer.height);
	printf("   ┃              ┃                                 ┃  ┆\n") ;
	printf("   ┃    %4d      ┃                                 ┃  ┆\n", (int)dt.img_2d_buffer.width);
	printf("   ┃      ╳       ┃                                 ┃  ┆\n");
	printf("   ┃    %4d      ┃                                 ┃  ┆\n", (int)dt.img_2d_buffer.height);
	printf("   ┃              ┃                                 ┃  ┆\n");
	printf("   ┗━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛  ┴\n");
	printf(" - player start pos=(%.2f, %.2f) dir=%.2f degrees\n", dt.player.pos.x, dt.player.pos.y, dt.player.dir);
	printf(" - FOV=%.2f degrees / FOV_PRE=%.4f degrees\n", FOV, FOV_PRE);
	printf(" - nb of rays X 3d columns width=%d X %d = %d VS %d\n", dt.nb_of_rays, dt.column_width, dt.column_width*dt.nb_of_rays, dt.img_3d_buffer.width);
	printf(" - start left ray at angle=%.2f degrees\n", dt.hits[0].angle.x);
	printf(" - end right ray at angle=%.2f degrees\n", dt.hits[dt.nb_of_rays - 1].angle.x);
	printf(" - elem rotation per ray=%.4f degrees\n", dt.rot_elem);
	printf("\n=============================================================\n");
}

static void	print_end_infos(t_data dt, t_fpos start_fpos,  int duration_ms, int bui_delay_ms)
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
	fpos_print(start_fpos);
	printf("\n  - to   ");
	fpos_print(dt.player.pos);
	printf("\n - Flags =[%s] ", dt.mv_flags);
	printf("\n - FOV=%.2f / FOV_PRE=%.2f --> %d\n", FOV, FOV_PRE, dt.nb_of_rays);
	printf("\n====================================\n\n");
}

int	main(void)
{
	t_fpos			start_fpos;
	t_data			dt;
	struct timeval	prog_start_time;
	struct timeval	prog_end_time;
	struct timeval	start_bui;
	struct timeval	end_bui;
	int				bui_delay_ms;
	int				ms_duration;

	/*
	const char *str_arr[] = {
		"111111111111111111111111111100000111111111111111111111111",
		"100000000000000000000000000000000000000000000000000000001",
		"101111111111111111111111111100000111111111111111111111101",
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
		"101001111000001111000000111100000111111111110111111110001",
		"101001111000001111000000111100000111100011110111111110001",
		"001000000000000000000000000000000000000000000001111000000",
		"00100000000000000000000000N000000000000000000001111000000",
		"001000000000000000000000000000000000000000000001111000000",
		"001001111000001111000000111100000111100011110111111110000",
		"001001111000001111000000111111111111100011110111111110000",
		"001001111000001111000000111100000111100011110111111110000",
		"001000000000000000000000000000000000000000000000000000000",
		"001000000000000000000000000000000000000000000000000001000",
		"111111111111111111111111110011111011111111111111111111111",
		"011111111111111111111111110011111111111100000011111111100",
		"011111111111011111111111110011111111111100000011111111100",
		"011111111111111111111111110011111111111100110011111111100",
		"011111111111111111111111110011111111111100110011111111100",
		"011100011111011111111111110011111111111100110011111111100",
		"011100011111111111111111110011111111111100110011111111100",
		"011111111111111111111111110011111111111100110011111111100",
		"000000000000000000000000000011111111111100000011111111100",
		"001111111111111111111111110011111111111100000011111111100",
		"001111111111111111111111111111111111111111111111111111100",
		"000000000000000000000000000000000000000000000000000000000",
		NULL};
	const char *str_arr[] = {
		"1111111111",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"10N0000001",
		"1111111111",
		NULL};
	const char	*str_arr[] = { \
		"100011111111111", \
		"100001000000001", \
		"100000100000001", \
		"100000010000001", \
		"100000000000101", \
		"1100000N0000011", \
		"000000000000001", \
		"100000000000000", \
		"010000000000001", \
		"001000001000001", \
		"000000000000000", \
		NULL };
	const char	*str_arr[] = { \
		"111", \
		"1S1", \
		"111", \
		NULL };
	const char	*str_arr[] = { \
		"100000011111111111", \
		"100000001000000001", \
		"100000000100000001", \
		"100000000010000001", \
		"100000000000000101", \
		"1100100000N0000011", \
		"000000000000000001", \
		"100000000000000000", \
		"010010000000000001", \
		"001001000001000001", \
		"001001000001000001", \
		"000000000000000000", \
		NULL };
	*/
	const char	*str_arr[] = { \
		"0000000", \
		"0010100", \
		"0100010", \
		"100N001", \
		"0100010", \
		"0010100", \
		"0000000", \
		NULL };
	gettimeofday(&prog_start_time, NULL);
	dt = init_data(str_arr);
	//------------------------------------------------------TODO REMOVE
	set_player(&dt.player, 3.5f, 3.5f, 45.0f);
	//set_player(&dt.player, 3.5f, 3.5f, 3 * 45.0f);
	//set_player(&dt.player, 3.5f, 3.5f, 5 * 45.0f);
	//set_player(&dt.player, 3.5f, 3.5f, 7 * 45.0f);
	//------------------------------------------------------TODO REMOVE
	if (error_detected_after_init_data(&dt))
		return (free_data(&dt), 1);
	gettimeofday(&start_bui, NULL);
	//if (!build_img_text(&dt.img_erase_txt))
	//	return (fprintf(stderr, "Error: build_img_text() failed\n"), free_data(&dt), 1);
	if (!build_img_floor(&dt.img_2d_floor))
		return (fprintf(stderr, "Error: build_img_floor() failed\n"), free_data(&dt), 1);
	if (!build_img_wall(&dt.img_2d_wall))
		return (fprintf(stderr, "Error: build_img_wall() failed\n"), free_data(&dt), 1);
	if (!build_img_grid(&dt.maze, &dt.img_2d_template, &dt.img_2d_floor, &dt.img_2d_wall))
		return (fprintf(stderr, "Error: build_img_grid() failed\n"), free_data(&dt), 1);
	if (!build_img_3d(&dt.img_3d_template))
		return (fprintf(stderr, "Error: build_img_3d() failed\n"), free_data(&dt), 1);
	gettimeofday(&end_bui, NULL);
	bui_delay_ms = diff_time_in_ms(start_bui, end_bui);
	start_fpos = fpos_dup(dt.player.pos);
	update_hit_tpos(&dt);
	print_start_infos(dt, str_arr, bui_delay_ms);
	mlx_loop_hook(dt.mlx_ptr, &main_loop, &dt);
	mlx_hook(dt.win_ptr, 17, 0, &mlx_loop_end, dt.mlx_ptr);
	mlx_hook(dt.win_ptr, 2, (1L << 0), &key_pressed, &dt);
	mlx_hook(dt.win_ptr, 3, (1L << 1), &key_released, &dt);
	mlx_loop(dt.mlx_ptr);
	gettimeofday(&prog_end_time, NULL);
	ms_duration = diff_time_in_ms(prog_start_time, prog_end_time);
	print_end_infos(dt, start_fpos, ms_duration, bui_delay_ms);
	return (free_data(&dt), 0); 
}
