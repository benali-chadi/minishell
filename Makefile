FLAGS = -Wall -Wextra -Werror

NAME = minishell

NAMELIB = libft.a

SRC = mini_shell.c mod_split.c env.c fill_cmd.c linkedlist.c utils.c gnl/get_next_line.c gnl/get_next_line_utils.c $(NAMELIB)

all : $(NAME)

$(NAME) : $(NAMELIB)
	gcc $(FLAGS) $(SRC) -o $(NAME) -D BUFFER_SIZE=10000

$(NAMELIB) :
	make -C libft/
	mv libft/$(NAMELIB) .

clean :
	make clean -C libft/
	rm -f *.a

fclean : clean
	make fclean -C libft/
	rm -f *.a
	rm -f $(NAME)

re : fclean all