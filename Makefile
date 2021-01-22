FLAGS = -Wall -Wextra -Werror -g
# -fsanitize=address

NAME = minishell

NAMELIB = libftprintf.a

SRC = mini_shell.c mod_split.c \
	env.c env_linkedlist.c \
	fill_cmd.c cmd_linkd_lst.c exec_cmd.c cmd_utils.c\
	echo.c path.c utils.c utils2.c to_free.c \
	gnl.c $(NAMELIB)
	# gnl/get_next_line.c gnl/get_next_line_utils.c $(NAMELIB)

all : $(NAME)

$(NAME) : $(NAMELIB)
	gcc $(FLAGS) $(SRC) -o $(NAME) 
	# -fsanitize=address
	# -D BUFFER_SIZE=10000 -g

$(NAMELIB) :
	make -C ft_printf/
	mv ft_printf/$(NAMELIB) .

clean :
	make clean -C ft_printf/
	rm -f *.a

fclean : clean
	make fclean -C ft_printf/
	rm -f *.a
	rm -f $(NAME)

re : fclean all