# =[ VARIABLES ]==============================================================================================
NAME		=	gridMaze_3dRayCastGhost_flagBasedMovs_fps_opti
# -[ MLX ]----------------------------------------------------------------------------------------------------
MLX_DIR		=	../../mlx
MLX_A		=	$(MLX_DIR)/libmlx.a
MLX_URL		=	https://github.com/42Paris/minilibx-linux.git
# -[ FOLDERS ]------------------------------------------------------------------------------------------------
BUILD_DIR	=	./build
# -[ COLORS ]-------------------------------------------------------------------------------------------------
BLACK		=	\033[2;30m
BLUE		=	\033[1;36m
BROWN		=	\033[1;33m
END			=	\033[0m
GREEN		=	\033[1;32m
GREY		=	\033[2;37m
RED			=	\033[1;31m
TC			=	\033[2;47m
YELLOW		=	\033[0;93m
TITLE		=	$(TC)$(NAME): 
# =[ COMMANDES ]==============================================================================================
MKDP		=	mkdir -p
RM			=	rm -rf
CC			=	cc
F_ADD		=	-lX11 -lXext -lm
FLAGS		=	-Wall -Wextra -Werror -I. -I$(MLX_DIR)
#FLAGS		=	-Wall -Wextra -Werror -I. -I$(MLX_DIR) -O2 -fno-builtin -march=native
#FLAGS		=	-Wall -Wextra -Werror -I. -I$(MLX_DIR) -O3 -ffast-math -march=native
# -[ VALGRIND ]-----------------------------------------------------------------------------------------------
VAL			=	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --undef-value-errors=no
# =[ OBJECTS ]================================================================================================
SRC			=	display_infos.c \
				draw_2dimg.c \
				draw_3dimg.c \
				draw_buffer_images.c \
				draw_to_img.c \
				main.c \
				main_loop.c \
				memcpy_utils.c \
				move_flags.c \
				raycast_collision.c \
				t_data_struct.c \
				t_fpos_struct.c \
				t_fpos_utils.c \
				t_hit_struct.c \
				t_img_builders.c \
				t_img_manipulations.c \
				t_img_struct.c \
				t_ipos_struct.c \
				t_ipos_utils.c \
				t_maze_struct.c \
				t_player_struct.c \
				t_pos_conv.c \
				utils_fmath.c \
				utils_imath.c \
				utils.c
OBJ			=	$(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
# =[ RULES ]==================================================================================================
all: $(NAME)

$(NAME): $(MLX_A) $(OBJ) header.h
	@echo "$(GREEN)🔘 $(TITLE)make $(NAME)$(END)"
	@$(CC) $(FLAGS) $(OBJ) $(MLX_A) -o $(NAME) $(F_ADD) && \
	echo "   $(GREEN)⤷ $(END)Create programm :$(GREEN)$(NAME)$(END) using command:" && \
	echo "     $(RED)\`$(END)$(CC) $(FLAGS) $(BUILD_DIR)/*.o $(MLX_A) -o $(NAME) $(F_ADD)$(RED)\`$(END)"

$(MLX_A):
	@if [ ! -d ${MLX_DIR} ];then echo "$(GREEN)🔘 $(TITLE)Clone repo. 'minilibx for linux'$(END)" && git clone $(MLX_URL) $(MLX_DIR) && echo "   $(GREEN)⤷ $(END)using command: $(RED)\`$(BLUE)git clone $(MLX_URL) $(MLX_DIR)$(END)$(RED)\`$(END)"; fi
	@echo "$(GREEN)🔘 $(TITLE)MLX make$(END)"
	@echo "   $(GREEN)⤷ $(END)Create static lib:$(GREEN)$(MLX_A)$(END) using command: $(RED)\`$(BLUE)$(MAKE)$(END) -C $(BROWN)$(MLX_DIR)$(END)$(RED)\`$(END)"
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1

$(BUILD_DIR)/%.o: %.c header.h
	@if [ ! -d $(BUILD_DIR) ];then $(MKDP) $(BUILD_DIR);fi
	@if [ -z "$$(ls -A $(BUILD_DIR) 2>/dev/null)" ];then echo "$(GREEN)🔘 $(TITLE)Create object files$(END)";fi
	@$(CC) $(FLAGS) -c $< -o $@ && printf "   $(GREEN)⤷ $(BROWN)%-38s $(YELLOW)⟹  $(BROWN)%s$(END)\n" "$<" "$@"

c clean:
	@echo "$(GREEN)🔘 $(TITLE)make clean$(END)"
	@$(RM) $(OBJ) && echo "   $(GREEN)⤷ $(END)$(RM) $(OBJ)"

fc fclean:
	@echo "$(GREEN)🔘 $(TITLE)make fclean$(END)"
	@if [ -f $(NAME) ];then $(RM) $(NAME) && echo "   $(GREEN)⤷ $(END)$(RM) $(NAME)";fi
	@if [ -d $(BUILD_DIR) ];then $(RM) $(BUILD_DIR) && echo "   $(GREEN)⤷ $(END)$(RM) $(BUILD_DIR)";fi
	@if [ -d $(DOC_SYMLINK) ];then $(RM) $(DOC_SYMLINK) && echo "   $(GREEN)⤷ $(END)$(RM) $(DOC_SYMLINK)";fi

re: fclean all

v val valgrind: $(NAME)
	@echo "$(GREEN)🔘 $(TITLE)make valgrind$(END)"
	$(VAL) ./$(NAME) $(filter-out $@,$(MAKECMDGOALS))

h help:
	@echo "\033[2;47m 🔘    $(BLACK)|$(GREEN)make commands      $(BLACK)|$(GREY)~(abreviation)$(BLACK)| $(BROWN)make commands definitions/explanations                                      $(BLACK)|$(END)"
	@echo "  $(BLUE)➽ $(RED)\`$$> $(GREEN)make clean$(RED)\`         $(GREY)~(make c)     $(END): $(BROWN)clean all objects files.o....................................................$(END)"
	@echo "  $(BLUE)➽ $(RED)\`$$> $(GREEN)make fclean$(RED)\`        $(GREY)~(make fc)    $(END): $(BROWN)clean all compiled files: objects files.o + binary file .....................$(END)"
	@echo "  $(BLUE)➽ $(RED)\`$$> $(GREEN)make help$(RED)\`          $(GREY)~(make h)     $(END): $(BROWN)display all make active commands.............................................$(END)"
	@echo "  $(BLUE)➽ $(RED)\`$$> $(GREEN)make re$(RED)\` 	                  $(END): $(BROWN)make fclean + make...........................................................$(END)"
	@echo "  $(BLUE)➽ $(RED)\`$$> $(GREEN)make valgrind$(RED)\`      $(GREY)~(make v)     $(END): $(BROWN)execute the binary file with valgrind .......................................$(END)"

.PHONY: all c clean fc fclean re v val valgrind h help
