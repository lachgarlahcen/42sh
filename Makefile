# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 18:30:14 by hastid            #+#    #+#              #
#    Updated: 2019/12/19 11:16:28 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

FLAG = -Wall -Wextra -Werror

SRC = src/main.c \
	  src/sh_list.c \
	  src/sh_free.c \
	  src/sh_pipe.c \
	  src/sh_check.c \
	  src/sh_split.c \
	  src/sh_token.c \
	  src/sh_error.c \
	  src/sh_etoil.c \
	  src/sh_builcd.c \
	  src/sh_envlist.c \
	  src/sh_environ.c \
	  src/sh_cmdline.c \
	  src/sh_builtin.c \
	  src/sh_execute.c \
	  src/sh_expipes.c \
	  src/sh_filedis.c \
	  src/sh_buil_cd.c \
	  src/sh_argument.c \
	  src/sh_cmdledit.c \
	  src/sh_checkline.c \
	  src/sh_checkerror.c \
	  src/sh_checkexecute.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) libft_c lineediting
	@gcc $(FLAG)  libft/libft.a line_editing/line_editing.a -ltermcap $(OBJ) -o $(NAME)
libft_c:
	@make -C libft
lineediting:
	@make -C line_editing

%.o: %.c
	@gcc $(FLAC) -o $@ -c $<

clean:
	@make clean -C libft
	@make clean -C line_editing
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@make fclean -C line_editing
	@rm -f $(NAME)

re: fclean all

