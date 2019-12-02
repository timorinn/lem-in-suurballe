/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:17:03 by bford             #+#    #+#             */
/*   Updated: 2019/12/02 16:22:05 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_print_input(t_input *input)
{
	t_input		*copy;

	copy = input;
	while (copy)
	{
		ft_putendl(copy->s);
		copy = copy->next;
	}
	write(1, "\n", 1);
}

int			main(int argc, char **argv)
{
	t_input		*input;
	t_room		*room;
	t_path		*path;

	path = NULL;
	input = ft_analize_input();
	room = ft_make_rooms(input);
	ft_find_path(room, &path, ft_get_ant(room));
	if (!input || !room || !path || !ft_check_flag(argc, argv))
	{
		return (ft_del_all(input, room) + ft_lstdel_path(&path) +
		ft_putstr("ERROR\n"));
	}
	ft_print_input(input);
	steps_print(path, room);
	ft_flag_and_other(argc, argv, path);
	return (ft_del_all(input, room) + ft_lstdel_path(&path));
}
