# ft_paint.c
A program that draw white pixel's directly on a window when left mouse's button pressed
- Commands: 
	- Inside `./mlx_lab/` folder, run:
	```c
	cc -Wall -Wextra -Werror -Imlx ./src/testing_area/ft_paint.c  mlx/libmlx.a -o t0_ft_paint -lXext -lX11 && \
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --undef-value-errors=no ./t0_ft_paint
	```

# pixel_cursor.c
A program that draw black pixel's in a white window where the cursor is
- Commands: 
	- Inside `./mlx_lab/` folder, run:
	```c
	cc -Wall -Wextra -Werror -Imlx ./src/testing_area/pixel_cursor.c  mlx/libmlx.a -o t0_pixcurs -lXext -lX11 && \
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --undef-value-errors=no ./t0_pixcurs
	```
