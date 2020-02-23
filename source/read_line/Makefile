# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/08 05:13:41 by hastid            #+#    #+#              #
#    Updated: 2020/02/22 15:53:00 by llachgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = read_line.a

FLAG = -Wall -Wextra -Werror

SRC_NAME = read_line.c \
		   init.c \
		   save.c \
		   signals.c \
		   keys2.c \
		   keys.c \
		   select_manage.c \
		   completion.c \
		   path_completion.c \
		   binary_compelation.c \
		   vars_compelation.c \
		   ft_selectmatch.c \
		   history_keys.c \
		   history.c \
		   ft_history_search.c \
		   ft_history_show.c \
		   tools.c \
		   ft_free.c \
		   bonus.c \
		   get_next_line.c \
		   ft_data.c \
		   fc_fc_editor.c \
		   ft_fc.c \
		   ft_fc_list.c \
		   ft_fc_redo.c

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

CFLAGS = -Wall -Werror -Wextra

Include = -I../../include \
		  -I../../libft/include

DEPS = ../../include/read_line.h

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
	@echo "\033[1;34mRemoving intern_variables's objects directory\033[0m"
	@/bin/rm -rf $(OBJ_PATH) 2> /dev/null

fclean: clean
	@echo "\033[1;34mRemovimg $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re: fclean all
