# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hastid <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 22:13:30 by hastid            #+#    #+#              #
#    Updated: 2020/01/17 22:14:02 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = intern_variable.a

FLAG = -Wall -Wextra -Werror

SRC = iv_list.c \
	  intern_variable.c \

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
