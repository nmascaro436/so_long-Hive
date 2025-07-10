# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 14:30:09 by nmascaro          #+#    #+#              #
#    Updated: 2025/07/10 11:37:59 by nmascaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = cleanup.c initialize_game.c main.c movement.c path_validation.c \
		read_map.c read_map_utils.c rendering.c validate_map.c
OBJS = $(SRCS:.c=.o)
MLX_DIR = /home/nmascaro/Documents/Studies/so_long/MLX42
MLX_FLAGS = -I$(MLX_DIR)/include
MLX_LIBS = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIBS) $(LIBFT_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_FLAGS) -c $< -o $@
	
clean:
	@rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re libmlx
