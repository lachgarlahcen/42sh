# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hastid <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 22:13:30 by hastid            #+#    #+#              #
#    Updated: 2020/01/24 03:07:25 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexical_analyser.a

FLAG = -Wall -Wextra -Werror

SRC = sh_environ.c \
	  line_editing.c \
	  lexical_check.c \
	  lexical_alias.c \
	  lexical_parser.c \
	  syntax_analyser.c \
	  lexical_analyser.c \

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
