# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/14 13:37:42 by xroca-pe          #+#    #+#              #
#    Updated: 2024/04/03 11:59:02 by xroca-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc 
CFLAGS = -Wall -Werror -Wextra
MXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
RM = rm -f 
INCLUDE = Makefile

SRC = fdf.c \
	  parsing.c \
	  utils.c \
	  get_next_line.c \
	  get_next_line_utils.c \
	  ft_substr.c \
	  ft_split.c \
	  ft_atoi.c \
	  dda.c	\
	  projections.c \
	  colors.c \
	  colors_utils.c \
	  info.c	  

OBJ := $(SRC:.c=.o)

DEPS := $(SRC:.c=.d)

all: dir $(NAME)

$(NAME): $(OBJ) $(INCLUDE) dir
	$(CC) $(CFLAGS) $(MXFLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -MMD -o $@ $<

dir:
	make -C mlx/  

clean:
	make clean -C mlx/
	$(RM) $(OBJ) $(DEPS)
	

fclean: clean
	$(RM) $(NAME) 

re: fclean all

-include ${DEPS}

.PHONY: all clean fclean re 