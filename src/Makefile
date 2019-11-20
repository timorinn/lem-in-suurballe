# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bford <bford@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 17:55:08 by bford             #+#    #+#              #
#    Updated: 2019/11/19 22:59:55 by bford            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =		ft_analize_input.c		\
			ft_lstdel_input.c		\
			ft_lstnew_input.c		\
			ft_make_rooms.c			\
			ft_del_dead_end.c		\
			ft_lstnew_room.c		\
			ft_lstnew_link.c		\
			ft_limit_path.c			\
			ft_len_output.c			\
			ft_get_ant.c			\
			ft_sort_paths.c			\
			step_print.c			\
			ft_path.c				\
			ft_del_all.c			\
			ft_lstdel_path.c		\
			\
			ft_print_path.c			\
			ft_print_link.c			\
			ft_print_room_and_link.c

OBJ =		$(SRC:.c=.o)

HEAD =		lemin.h

NAME =		liblemin.a

all:		$(NAME)

$(NAME):	$(OBJ)
			ar -rcs $(NAME) $(OBJ)

%.o:		%.c $(HEAD)
			gcc -I $(HEAD) -Wall -Wextra -Werror -c $< -o $@

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all
