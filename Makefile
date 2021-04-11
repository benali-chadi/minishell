# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/28 16:00:43 by cbenali-          #+#    #+#              #
#    Updated: 2021/04/06 18:13:31 by cbenali-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

NAME = minishell

NAMELIB = libftprintf.a

SRC = mini_shell.c exec_cmd.c \
	fill_cmd.c cmd_utils.c cat_command.c redirection.c\
	echo.c path.c utils.c utils2.c utils3.c to_free.c \
	env.c env_linkedlist.c cmd_linkd_lst.c\
	gnl.c mod_split_red.c mod_split.c mod_split_red_utils.c fill_cmd_2.c env2.c env3.c mod_split_1.c new_clean_command.c cat_command_utils.c $(NAMELIB)

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