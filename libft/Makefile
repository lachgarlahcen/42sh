# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hastid <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/07 19:31:36 by hastid            #+#    #+#              #
#    Updated: 2020/02/20 04:18:40 by hastid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_NAME = ft_isalpha.c \
		   ft_lstadd.c \
		   ft_lstlen.c \
		   ft_memchr.c \
		   ft_memset.c \
		   ft_putendl_fd.c \
		   ft_strcat.c \
		   ft_strdel.c \
		   ft_strjoin.c \
		   ft_strncat.c \
		   ft_strnstr.c \
		   ft_strtrim.c \
		   ft_isascii.c \
		   ft_isblank.c \
		   ft_lstaddend.c \
		   ft_lstmap.c \
		   ft_memcmp.c \
		   ft_nbrlen.c \
		   ft_putnbr.c \
		   ft_strchr.c \
		   ft_strdup.c \
		   ft_strlcat.c \
		   ft_strncmp.c \
		   ft_strrchr.c \
		   ft_tolower.c \
		   ft_atoi.c \
		   ft_isdigit.c \
		   ft_lstdel.c \
		   ft_lstnew.c \
		   ft_memcpy.c \
		   ft_putchar.c \
		   ft_putnbr_fd.c \
		   ft_strclr.c \
		   ft_strequ.c \
		   ft_strlen.c \
		   ft_strncpy.c \
		   ft_strsplit.c \
		   ft_toupper.c \
		   ft_bzero.c \
		   ft_isprint.c \
		   ft_lstdelone.c \
		   ft_memalloc.c \
		   ft_memdel.c \
		   ft_putchar_fd.c \
		   ft_putstr.c \
		   ft_strcmp.c \
		   ft_striter.c \
		   ft_strmap.c \
		   ft_strnequ.c \
		   ft_strstr.c \
		   ft_isalnum.c \
		   ft_itoa.c \
		   ft_lstiter.c \
		   ft_memccpy.c \
		   ft_memmove.c \
		   ft_putendl.c \
		   ft_putstr_fd.c \
		   ft_strcpy.c \
		   ft_striteri.c \
		   ft_strmapi.c \
		   ft_strnew.c \
		   ft_strsub.c \
		   ft_printf.c \
		   ot_funct.c \
		   pr_csp.c \
		   pr_dioux.c \
		   pr_printf.c \
		   ft_putstr_ret.c \
		   ft_putchar_ret.c \
		   ft_chain_free.c \
		   ft_chain_size.c \
		   ft_strappend.c \
		   ft_strojoin.c


OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

CFLAGS = -Wall -Werror -Wextra

DEPS = include/libft.h

all : $(NAME)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(DEPS)
	@mkdir $(OBJ_PATH) 2>/dev/null || true
	@clear
	@echo "Compiling \033[1;33m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) -I include -o $@ -c $<

$(NAME) : $(OBJ)
	@echo "\033[1;34mCreating $(NAME)\033[0m"
	@ar rc $@ $^
	@ranlib $@

clean:
	@echo "\033[1;34mRemoving libft's objects directory\033[0m"
	@/bin/rm -rf $(OBJ_PATH) 2> /dev/null

fclean: clean
	@echo "\033[1;34mRemovimg $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re: fclean all
