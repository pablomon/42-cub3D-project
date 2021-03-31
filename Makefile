# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/28 19:15:11 by pmontese          #+#    #+#              #
#    Updated: 2021/03/28 20:06:34 by pmontese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext 					#linux
#CFLAGS = -g -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls 	# used for memory leaks detection
CFLAGS = -Wall -Wextra -Werror # -g -fsanitize = address
NAME = cub3D

SRCS = 	src/bitmap.c \
	src/controls.c \
	src/debug.c \
	src/errors.c \
	src/floor_ceil.c \
	src/get_next_line_utils.c \
	src/get_next_line.c \
	src/ids.c \
	src/init_free.c \
	src/main.c \
	src/map_checks.c \
	src/minimap.c \
	src/miscellaneous.c \
	src/mlx_tools.c \
	src/parse_file.c \
	src/parse_ids.c \
	src/parse_map.c \
	src/render.c \
	src/sprites.c \
	src/walls.c

OBJSRCS = $(SRCS:.c=.o)

$(NAME) : $(OBJSRCS)
	@echo "Libft compilation..."
	@$(MAKE) -C ./libft
	@echo "Cub3D compilation..."
	@$(CC) $(CFLAGS) $(OBJSRCS) -L $(MLX) ./libft/libft.a -o $(NAME)
	@echo "Done !"

all : $(NAME)

test : $(NAME)
	./$(NAME) maps/test.cub
clean :
	rm -rf $(OBJSRCS)
	$(MAKE) clean -C ./libft

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)
	rm -rf screenshot.bmp

re : fclean all

bonus : $(NAME)
