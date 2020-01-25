# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 18:30:14 by hastid            #+#    #+#              #
#    Updated: 2020/01/24 03:05:52 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

FLAG = -Wall -Wextra -Werror

SRC = source/main.c \

LIB = libft/libft.a \
	  source/intern_variable/intern_variable.a \
	  source/lexical_analyser/lexical_analyser.a \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) libft_c  intern_variable_c lexical_analyser_c
	@gcc $(FLAG) $(LIB) -lreadline -ltermcap $(OBJ) -o $(NAME)

libft_c:
	@make -C libft

intern_variable_c:
	@make -C source/intern_variable

lexical_analyser_c:
	@make -C source/lexical_analyser

%.o: %.c
	@gcc $(FLAC) -o $@ -c $<

clean:
	@make clean -C libft
	@make clean -C source/intern_variable
	@make clean -C source/lexical_analyser
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@make fclean -C source/intern_variable
	@make fclean -C source/lexical_analyser
	@rm -f $(NAME)

re: fclean all
