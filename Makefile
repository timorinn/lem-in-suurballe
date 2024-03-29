# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bford <bford@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:37:52 by bford             #+#    #+#              #
#    Updated: 2019/12/02 14:58:56 by bford            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		lem-in

SRC =		main.c

LIBFT = 	./libft

LEMIN =		./src

LIBFTA =	./libft/libft.a

LEMINA =	./src/liblemin.a

OBJ = $(SRC:.c=.o)

.PHONY: 	all clean fclean re

all:		$(NAME)

%.o:		%.c
			gcc -Wall -Werror -Wextra -I $(LIBFT) -I $(LEMIN) -o $@ -c $<

$(NAME):	$(LIBFTA) $(LEMINA) $(OBJ) ./libft/libft.a ./src/liblemin.a
			gcc -Wall -Werror -Wextra -o lem-in $(OBJ) -L ./libft -lft -L ./src -llemin

FORCE:		;

$(LEMINA):	FORCE
			make -C ./src

$(LIBFTA):	FORCE
			make -C ./libft

clean:
			rm -f main.o
			make clean -C ./libft
			make clean -C ./src

fclean:		clean
			rm -f $(NAME)
			make fclean -C ./libft
			make fclean -C ./src

re:			fclean all
