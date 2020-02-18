# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/30 10:17:50 by aihya             #+#    #+#              #
#    Updated: 2020/02/18 18:07:51 by aihya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = 42sh_bin

SRC_PATH =	src
OBJ_PATH =	obj

binaries_SRC_NAME = hash.c					\
					hash_utils.c			\
					binaries_add_remove.c	\
					binaries_utils.c		\
					binaries_update.c
binaries_OBJ_NAME =	$(binaries_SRC_NAME:.c=.o)
binaries_SRC_PATH = $(addprefix $(SRC_PATH)/,hash_builtin)
binaries_OBJ_PATH = $(addprefix $(OBJ_PATH)/,hash_builtin)

alias_SRC_NAME =	alias.c				\
					alias_utils.c		\
					alias_print_funcs.c
alias_OBJ_NAME =	$(alias_SRC_NAME:.c=.o)
alias_SRC_PATH =	$(addprefix $(SRC_PATH)/,alias_builtin)
alias_OBJ_PATH =	$(addprefix $(OBJ_PATH)/,alias_builtin)

unalias_SRC_NAME =	unalias.c
unalias_OBJ_NAME =	$(unalias_SRC_NAME:.c=.o)
unalias_SRC_PATH =	$(addprefix $(SRC_PATH)/,unalias_builtin)
unalias_OBJ_PATH =	$(addprefix $(OBJ_PATH)/,unalias_builtin)

type_SRC_NAME =	type.c
type_OBJ_NAME =	$(type_SRC_NAME:.c=.o)
type_SRC_PATH =	$(addprefix $(SRC_PATH)/,type_builtin)
type_OBJ_PATH =	$(addprefix $(OBJ_PATH)/,type_builtin)

hashtable_SRC_NAME =	hashtable.c	\
						hashtable_ops.c
hashtable_OBJ_NAME =	$(hashtable_SRC_NAME:.c=.o)
hashtable_SRC_PATH =	$(addprefix $(SRC_PATH)/,hashtable)
hashtable_OBJ_PATH =	$(addprefix $(OBJ_PATH)/,hashtable)

utils_SRC_NAME =	main.c			\
					sort.c			\
					usage.c			\
					path_lookup.c
utils_OBJ_NAME =	$(utils_SRC_NAME:.c=.o)
utils_SRC_PATH =	$(addprefix $(SRC_PATH)/,utils)
utils_OBJ_PATH =	$(addprefix $(OBJ_PATH)/,utils)

expansions_SRC_NAME =	expansions.c
expansions_OBJ_NAME =	$(expansions_SRC_NAME:.c=.o)
expansions_SRC_PATH =	$(addprefix $(SRC_PATH)/,expansions)
expansions_OBJ_PATH =	$(addprefix $(OBJ_PATH)/,expansions)

errors_SRC_NAME = 	errors.c
errors_OBJ_NAME =	$(errors_SRC_NAME:.c=.o)
errors_SRC_PATH =	$(addprefix $(SRC_PATH)/,errors)
errors_OBJ_PATH =	$(addprefix $(OBJ_PATH)/,errors)

SRC =	$(addprefix $(binaries_SRC_PATH)/,$(binaries_SRC_NAME))		\
		$(addprefix $(alias_SRC_PATH)/,$(alias_SRC_NAME))			\
		$(addprefix $(unalias_SRC_PATH)/,$(unalias_SRC_NAME))		\
		$(addprefix $(hashtable_SRC_PATH)/,$(hashtable_SRC_NAME))	\
		$(addprefix $(utils_SRC_PATH)/,$(utils_SRC_NAME))			\
		$(addprefix $(errors_SRC_PATH)/,$(errors_SRC_NAME))			\
		$(addprefix $(type_SRC_PATH)/,$(type_SRC_NAME))				\
		$(addprefix $(expansions_SRC_PATH)/,$(expansions_SRC_NAME))
		
OBJ =	$(addprefix $(binaries_OBJ_PATH)/,$(binaries_OBJ_NAME))		\
		$(addprefix $(alias_OBJ_PATH)/,$(alias_OBJ_NAME))			\
		$(addprefix $(unalias_OBJ_PATH)/,$(unalias_OBJ_NAME))		\
		$(addprefix $(hashtable_OBJ_PATH)/,$(hashtable_OBJ_NAME))	\
		$(addprefix $(utils_OBJ_PATH)/,$(utils_OBJ_NAME))			\
		$(addprefix $(errors_OBJ_PATH)/,$(errors_OBJ_NAME))			\
		$(addprefix $(type_OBJ_PATH)/,$(type_OBJ_NAME))				\
		$(addprefix $(expansions_OBJ_PATH)/,$(expansions_OBJ_NAME))

CFLAGS = -Wall \
		 -Werror \
		 -Wextra

INCLUDE =	-Iinclude \
			-Ilibft/include

LIBS = -Llibft -lft

DEPS = include/sh.h

all : $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@echo "\033[1;34mCreating $(NAME)\033[0m"
	@gcc $(OBJ) $(LIBS) -o $@

$(binaries_OBJ_PATH)/%.o: $(binaries_SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(binaries_OBJ_PATH) 2> /dev/null || true
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(alias_OBJ_PATH)/%.o: $(alias_SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(alias_OBJ_PATH) 2> /dev/null || true
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<
	
$(unalias_OBJ_PATH)/%.o: $(unalias_SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(unalias_OBJ_PATH) 2> /dev/null || true
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<
	
$(type_OBJ_PATH)/%.o: $(type_SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(type_OBJ_PATH) 2> /dev/null || true
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(hashtable_OBJ_PATH)/%.o: $(hashtable_SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(hashtable_OBJ_PATH) 2> /dev/null || true
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(utils_OBJ_PATH)/%.o: $(utils_SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(utils_OBJ_PATH) 2> /dev/null || true
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(errors_OBJ_PATH)/%.o: $(errors_SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(errors_OBJ_PATH) 2> /dev/null || true
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(expansions_OBJ_PATH)/%.o: $(expansions_SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(expansions_OBJ_PATH) 2> /dev/null || true
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean :
	@make -C libft clean
	@echo "\033[1;33mRemoving $(NAME)'s objects directory\033[0m"
	@/bin/rm -rf $(OBJ_PATH) 2> /dev/null

fclean : clean
	@make -C libft fclean
	@echo "\033[1;33mRemoving $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re : fclean all
