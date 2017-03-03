# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chansen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/27 19:26:44 by chansen           #+#    #+#              #
#    Updated: 2017/03/01 20:54:49 by chansen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = ./src/tools.c \
			./src/put_image_pixel.c \
			./src/center.c \
			./src/rotate.c \
			./src/scale.c \
			./src/draw.c \
			./src/read.c \
			./src/main.c \

LIB = -I libft -L libft -lft

MLX = -I minilibx -L minilibx -lmlx

FRAME = -framework OpenGL -framework AppKit

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)

$(NAME):
	make -C ./libft/ re
	make -C ./minilibx/ re
	$(CC) $(CFLAGS) $(LIB) $(MLX) $(FRAME) $(SRC) -o $(NAME)

fclean: clean
	$(RM) $(NAME)

clean:
	make -C ./libft/ clean
	make -C ./minilibx/ clean

re: fclean all
