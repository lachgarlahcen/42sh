# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hastid <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/08 05:06:04 by hastid            #+#    #+#              #
#    Updated: 2020/02/08 05:54:09 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_builtin.a

SRC_NAME = test_builtin.c \
		   tools.c \
		   arg_cmp.c \
		   options.c

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

CFLAGS = -Wall -Werror -Wextra

Include = -Iinclude \
		  -I../../../../libft/include

DEPS = include/test_builtin.h

all: $(NAME)

$(NAME): $(OBJ)
	@clear
	@echo "\033[1;34mCreating $(NAME)\033[0m"
	@ar rc $@ $^

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(DEPS)
	@mkdir $(OBJ_PATH) 2>/dev/null || true
	@clear
	@echo "Compiling \033[1;33m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc  $(CFLAGS) -g $(Include) -o $@ -c $<

clean:
	@echo "\033[1;34mRemoving test_builtin's objects directory\033[0m"
	@/bin/rm -rf $(OBJ_PATH) 2> /dev/null

fclean: clean
	@echo "\033[1;34mRemovimg $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re: fclean all
