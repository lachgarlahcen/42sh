# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 18:30:14 by hastid            #+#    #+#              #
#    Updated: 2020/02/04 02:17:06 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

SRC_NAME = main.c

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	source
OBJ_PATH =	objet

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))



CFLAGS = -Wall -Wextra -Werror

INCLUDE =	-Iinclude \
			-Ilibft/include \
			-Isource/line_editing/include

LIBS =	libft/libft.a \
		source/line_editing/line_editing.a \
		source/tokens_parser/tokens_parser.a

DEPS = include/shell.h

all: $(NAME)

$(NAME): $(OBJ) libft_c line_editing_c tokens_parser_c
	@clear;
	@echo "	\033[1;34mCreating ...									";
	@echo "         					              	         	";
	@echo "    ██╗       ██████╗  ██████╗  ██╗  ██╗                 ";
	@echo "    ██║  ██╗  ╚═══██║  ██════╝  ██║  ██║ 				";
	@echo "    ██║  ██║  ██████║  ██████╗  ███████║ 				";
	@echo "    ███████║  ██╔═══╝  ╚═══██║  ██╔══██║				    ";
	@echo "    ╚═══ ██║  ██████╗  ██████║  ██║  ██║         		";
	@echo "         ╚═╝  ╚═════╝  ╚═════╝  ╚═╝  ╚═╝                 ";
	@echo "				                                            ";
	@echo "\033[1;33m $(NAME)\033[0m                        ";
	@echo "		         Made by : \033[1;91m mizonaise\033[m       ";
	@gcc $(OBJ) $(LIBS) -ltermcap -lreadline  -o $@

libft_c:
	@make -C libft

line_editing_c:
	@make -C source/line_editing

tokens_parser_c:
	@make -C source/tokens_parser

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(DEPS)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@clear;
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) -g $(INCLUDE) -o $@ -c $<

clean:
	@make clean -C libft
	@make clean -C source/line_editing
	@make clean -C source/tokens_parser
	@echo "\033[1;33mRemoving $(NAME)'s objects directory\033[0m"
	@rm -rf $(OBJ_PATH) 2> /dev/null

fclean: clean
	@make fclean -C libft
	@make fclean -C source/line_editing
	@make fclean -C source/tokens_parser
	@echo "\033[1;33mRemoving $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re: fclean all
