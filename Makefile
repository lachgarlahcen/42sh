# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hastid <marvin@42.fr>                      +#+  +:+       +#+         #
#    By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/11 02:10:20 by hastid            #+#    #+#              #
#    Updated: 2020/02/11 02:10:22 by hastid           ###   ########.fr        #
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
			-Ilibft/include

LIBS =	libft/libft.a \
		source/read_line/read_line.a \
		source/job_control/job_control.a \
		source/line_editing/line_editing.a \
		source/execute_cmdl/execute_cmdl.a \
		source/test_builtin/test_builtin.a \
		source/tokens_parser/tokens_parser.a \
		source/shell_signals/shell_signals.a \
		source/execute_builtin/execute_builtin.a \
		source/intern_variables/intern_variables.a

DEPS = include/shell.h

LIB_C = libft_c \
		read_line_c \
		job_control_c \
		line_editing_c \
		execute_cmdl_c \
		test_builtin_c \
		tokens_parser_c \
		shell_signals_c \
		execute_builtin_c \
		intern_variables_c


all: $(NAME)

$(NAME): $(OBJ) $(LIB_C) 
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
	@echo "		         Made by : \033[1;91m mmizonaise\033[m       ";
	@gcc $(OBJ) $(LIBS) -ltermcap -o $@


libft_c:
	@make -C libft

read_line_c:
	@make -C source/read_line

job_control_c:
	@make -C source/job_control

line_editing_c:
	@make -C source/line_editing

execute_cmdl_c:
	@make -C source/execute_cmdl

test_builtin_c:
	@make -C source/test_builtin

tokens_parser_c:
	@make -C source/tokens_parser

shell_signals_c:
	@make -C source/shell_signals

execute_builtin_c:
	@make -C source/execute_builtin

intern_variables_c:
	@make -C source/intern_variables

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(DEPS)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@clear;
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) -g $(INCLUDE) -o $@ -c $<

clean:
	@make clean -C libft
	@make clean -C source/read_line
	@make clean -C source/job_control
	@make clean -C source/line_editing
	@make clean -C source/execute_cmdl
	@make clean -C source/test_builtin
	@make clean -C source/tokens_parser
	@make clean -C source/shell_signals
	@make clean -C source/execute_builtin
	@make clean -C source/intern_variables
	@echo "\033[1;33mRemoving $(NAME)'s objects directory\033[0m"
	@rm -rf $(OBJ_PATH) 2> /dev/null

fclean: clean
	@make fclean -C libft
	@make fclean -C source/read_line
	@make fclean -C source/job_control
	@make fclean -C source/line_editing
	@make fclean -C source/execute_cmdl
	@make fclean -C source/test_builtin
	@make fclean -C source/tokens_parser
	@make fclean -C source/shell_signals
	@make fclean -C source/execute_builtin
	@make fclean -C source/intern_variables
	@echo "\033[1;33mRemoving $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re: fclean all
