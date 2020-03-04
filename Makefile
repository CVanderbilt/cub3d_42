# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eherrero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/03 14:32:58 by eherrero          #+#    #+#              #
#    Updated: 2020/03/04 18:54:51 by eherrero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=Cub3D.out

CC=gcc

CFLAGS=-Wall -Wextra -Werror -framework OpenGL -framework AppKit minilibX/libmlx.a

RM=rm -f

LDFLAGS=-L.

LDLIBS=-lft

BMP=srcs/bmp.c

MAP_READER=srcs/errors.c srcs/map_reader_utils.c \
		   srcs/sprites_1.c srcs/sprites_2.c srcs/line_handler_utils.c\
		   srcs/checks_1.c srcs/checks_2.c srcs/line_handler.c

UTILS=srcs/ft_calloc.c srcs/ft_realloc.c srcs/ft_in_set.c srcs/ft_strcmp.c \
	  srcs/ft_atoi.c srcs/ft_atoi_rgb.c srcs/ft_isalnum.c srcs/ft_isdigit.c \
	  srcs/ft_isspace.c srcs/get_next_line.c srcs/get_next_line_utils.c \
	  srcs/ft_putstr.c srcs/ft_strjoin.c srcs/ft_itoa.c

RENDER=srcs/render.c srcs/render_utils.c srcs/texture_selector.c srcs/sprite_paint.c

EVENTS=srcs/player_move.c srcs/shoot.c srcs/sprite_move.c srcs/hooks.c \
	   srcs/extra_maps.c srcs/arrow_map_tiles.c srcs/hud.c \
	   srcs/final_free_1.c srcs/final_free_2.c

MAIN=srcs/cub3d.c srcs/texture_initializer.c srcs/init_textures.c srcs/init_assets.c

SRC=$(MAIN) $(EVENTS) $(RENDER) $(UTILS) $(MAP_READER) $(BMP)

OBJ=$(SRC:.c=.o)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) 

all: $(NAME)

sanitize:
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) -fsanitize=address 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) -rf $(NAME) $(NAME).dSYM

re: fclean all

.PHONY: clean fclean all bonus
