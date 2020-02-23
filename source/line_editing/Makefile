# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hastid <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 03:07:16 by hastid            #+#    #+#              #
#    Updated: 2020/02/22 22:18:38 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = line_editing.a

SRC_NAME =	alias.c \
			utils.c \
			syntax.c \
			lexical.c \
			history.c \
			syntax_utils.c \
			line_editing.c

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

CFLAGS = -Wall -Werror -Wextra

Include = -I../../include \
		  -I../../libft/include

DEPS = ../../include/line_editing.h

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
	@echo "\033[1;34mRemoving line_editing's objects directory\033[0m"
	@/bin/rm -rf $(OBJ_PATH) 2> /dev/null

fclean: clean
	@echo "\033[1;34mRemovimg $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re: fclean all
