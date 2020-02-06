NAME = 42
SRC  = main.c options.c tools.c arg_cmp.c
C       = gcc
CFLAGS = 
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : READ_LINE $(OBJ)
		@$(C) $(CFLAGS)  $(OBJ) -o $(NAME) -I test.h libft/libft.a

READ_LINE:
			make -C libft

%.o	: %.c
		$(C) $(CFLAGS) -o $@ -c $<

clean	:
		@make clean -C libft
		@rm -f $(OBJ)

fclean	: clean
		@make fclean -C libft
		@rm -f $(NAME)

re	: fclean all