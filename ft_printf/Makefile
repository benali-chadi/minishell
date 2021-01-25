# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/08 14:21:38 by cbenali-          #+#    #+#              #
#    Updated: 2019/11/08 23:06:18 by cbenali-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror

NAMELIB = libft.a

NAME = libftprintf.a

SRC = ft_addrtoa.c ft_printaddr.c ft_printhex_bigx.c ft_printstr.c ft_putunnbr.c ft_hextoa.c ft_printchar.c ft_printhex_x.c ft_printstr_mns.c ft_num_int.c ft_printf.c ft_printint.c ft_printun.c num_hex.c ft_printper.c

O = $(SRC:.c=.o)

all : $(NAME)

$(NAMELIB) :
	make -C libft/
	cp libft/$(NAMELIB) .

$(NAME) : $(NAMELIB)
	ar x $(NAMELIB)
	gcc $(FLAGS) -c $(SRC)
	ar rc $(NAME) *.o
	ranlib $(NAME)

clean :
	make clean -C libft/
	rm -f *.o
fclean : clean
	make fclean -C libft/
	rm -f *.a 
re : fclean all
