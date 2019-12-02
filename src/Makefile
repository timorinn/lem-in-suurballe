# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bford <bford@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 17:55:08 by bford             #+#    #+#              #
#    Updated: 2019/12/02 16:20:49 by bford            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =		ft_analize_input.c		\
			ft_lstdel_input.c		\
			ft_lstnew_input.c		\
			ft_make_rooms.c			\
			ft_make_room_list.c		\
			ft_init_room_param.c	\
			ft_check_start_end.c	\
			ft_lstnew_room.c		\
			ft_lstnew_link.c		\
			ft_limit_path.c			\
			ft_len_output.c			\
			ft_get_ant.c			\
			step_print.c			\
			ft_del_all.c			\
			ft_lstdel_path.c		\
			ft_path_len.c			\
			ft_find_path.c			\
			ft_get_path.c			\
			ft_push_ended_path.c	\
			ft_null_room.c			\
			ft_analize_path.c		\
			re_malloc_path.c		\
			ft_find_end.c			\
			ft_find_start.c			\
			ft_push_tail.c			\
			ft_conflict.c			\
			ft_repath_first.c		\
			ft_len_room_list.c		\
			ft_flag_and_other.c		\
			ft_check_flag.c			\
			ft_print_path.c			\
			steps_add_one.c 

OBJ =		$(SRC:.c=.o)

HEAD =		lemin.h

NAME =		liblemin.a

all:		$(NAME)

$(NAME):	$(OBJ)
			ar -rcs $(NAME) $(OBJ)

%.o:		%.c $(HEAD)
			gcc -I ./ -Wall -Wextra -Werror -c $< -o $@

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all
