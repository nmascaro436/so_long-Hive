# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 14:30:09 by nmascaro          #+#    #+#              #
#    Updated: 2025/07/25 09:39:57 by nmascaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = cleanup.c initialize_game.c main.c movement.c path_validation.c \
		read_map.c read_map_utils.c rendering.c validate_map.c \
		rendering_optimization.c
OBJS = $(SRCS:.c=.o)
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -I$(MLX_DIR)/include
MLX_LINK_FLAGS = $(MLX_LIB) -ldl -lglfw -pthread -lm

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@cmake -B $(MLX_DIR)/build $(MLX_DIR)
	@cmake --build $(MLX_DIR)/build

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LINK_FLAGS) $(LIBFT_LIB) -o $(NAME)
	@echo "so_long executable created"

%.o: %.c
	@$(CC) $(CFLAGS) $(MLX_FLAGS) -c $< -o $@
	
clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
