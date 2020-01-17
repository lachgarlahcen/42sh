# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 14:53:50 by llachgar          #+#    #+#              #
#    Updated: 2019/12/10 13:56:04 by llachgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = line_editing.a

FLAG = -Wall -Wextra -Werror

SRC = history.c \
	  keys.c \
	  read_line.c \
	  select_manage.c \
	  tools.c \
	  history_keys.c \
	  save.c \
	  keys2.c \
	  init.c \
	  signals.c \
	  ft_free.c \
	  bonus.c \
	  get_next_line.c 

OBJ = $(SRC:.c=.o)


$(NAME): $(OBJ)
	@ar rc $(NAME)  $(OBJ)

all: $(NAME)

%.o: %.c
	@gcc  $(FLAC)  -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
