# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: xchen <xchen@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/19 10:59:13 by xchen         #+#    #+#                  #
#    Updated: 2022/03/16 17:06:56 by xchen         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minirt
HEADER_DIR = ./src/includes
SRC_DIR = ./src/
SRC_FILE_BASE = main.c \
				image/show_on.c \
				image/init_screen.c \
				image/bmp.c \
				parse/parse_file.c \
				parse/parse_bump.c \
				parse/parse_nbr.c \
				parse/parse_effect.c \
				parse/parse_line.c \
				parse/process_obj.c \
				parse/parse_obj_1.c \
				parse/parse_obj_2.c \
				parse/parse_obj_3.c \
				parse/parse_obj.c \
				parse/function_array.c \
				vector/vector_1.c \
				vector/vector_2.c \
				vector/vector_3.c \
				vector/matrix.c \
				vector/rotation.c \
				intersection/general.c \
				intersection/sphere.c \
				intersection/plane.c \
				intersection/triangle.c \
				intersection/square.c \
				intersection/cylinder_intersect.c \
				intersection/cylinder_cone.c \
				intersection/cube.c \
				intersection/pyramid.c \
				tracing/effect.c \
				tracing/bump.c \
				tracing/surface_color.c \
				tracing/trace.c \
				utils/minilibx_support.c \
				utils/camera_interaction.c \
				utils/get_next_line.c \
				utils/exit.c \
				utils/utils_1.c \
				other_check.c
SRC_FILE_REGULAR = image/draw_img.c
SRC_FILE_BONUS = image/draw_img_bonus.c
OBJ_FILE_BONUS = $(addprefix $(SRC_DIR), $(SRC_FILE_BONUS:%.c=%.o))

ifdef WITH_BONUS
SRC_FILE_ROOT = $(SRC_FILE_BASE) $(SRC_FILE_BONUS)
else
SRC_FILE_ROOT = $(SRC_FILE_BASE) $(SRC_FILE_REGULAR)
endif

SRC_FILE = $(addprefix $(SRC_DIR), $(SRC_FILE_ROOT))
OBJ_FILE = $(SRC_FILE:%.c=%.o)
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.dylib
CFLAGS = -Wall -Werror -Wextra
CFLAGS_SAN = -Wall -Werror -Wextra -g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ_FILE)
	$(MAKE) -C $(MLX_DIR)
	cp $(MLX_LIB) ./libmlx.dylib
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(MLX_DIR) -I $(HEADER_DIR) -c $< -o $@

bonus:
	$(MAKE) WITH_BONUS=1 all

clean:
	rm -f $(OBJ_FILE) $(OBJ_FILE_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f ./libmlx.dylib
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) image.bmp

re: 
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re