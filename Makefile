# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhurt <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/21 15:33:03 by lhurt             #+#    #+#              #
#    Updated: 2016/10/21 15:33:05 by lhurt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc

FLAG =		-Wall -Wextra -Werror -o

LX =		-lmlx

MINLX =		./minilibx

INC =		-I $(MINLX)

LIB =		-L $(MINLX)

OPENGL =	-framework OpenGl

APPKIT =	-framework AppKit

LIBFT =		libft

COMP =		make -C $(LIBFT) re

COMPC =		make -C $(LIBFT) clean

COMPF =		make -C $(LIBFT) fclean

NAME =		fdf

SRCS =		$(LIBFT)/libft.a \
			main.c	\
			mlxfunc.c \
			matfunc.c \
			matfunc1.c \
			hookfunc.c \
			hookfunc1.c \
			basicfunc.c \
			basicfunc1.c \
			extrafunc.c \
			line_algo.c \
			rotfunc.c \

all: 	$(NAME)

$(NAME):
		@$(COMP)
		@$(CC) $(INC) $(LIB) $(LX) $(OPENGL) $(APPKIT) $(FLAG) $(NAME) $(SRCS)
		@echo "$(NAME) & $(LIBFT).a: has been created."

clean:
		@$(COMPC)
		@echo "$(LIBFT) has been cleaned."

fclean:	clean
		@$(COMPF)
		@/bin/rm -f $(NAME)
		@echo "$(NAME) & $(LIBFT).a: has been erased."

re: 	fclean all

.PHONY: all clean fclean re
