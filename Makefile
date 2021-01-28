FLAGS = -Wall -Wextra -Werror -g

NAME = minishell

NAMELIB = libftprintf.a

SRC = mini_shell.c exec_cmd.c \
	fill_cmd.c cmd_utils.c cat_command.c redirection.c\
	echo.c path.c utils.c utils2.c to_free.c \
	env.c env_linkedlist.c cmd_linkd_lst.c\
	gnl.c mod_split_red.c mod_split.c $(NAMELIB)

all : $(NAME)

$(NAME) : $(NAMELIB)
	gcc $(FLAGS) $(SRC) -o $(NAME)

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