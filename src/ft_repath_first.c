/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repath_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 11:04:28 by bford             #+#    #+#             */
/*   Updated: 2019/11/25 17:16:05 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ft_find_num_room(t_room *findroom, t_room **pathroom)
{
	int		i;

	i = 0;
	while (pathroom[i] != findroom)
		i++;
	return (i);
}

static int	ft_repath_second(t_room **copy, t_path *last, t_room *room_last)
{
	int		last_in_conf;
	int		last_in_last;
	t_room	**last_copy_room;
	int		i;

	i = 0;
	last_in_conf = ft_find_num_room(room_last, copy);
	last_in_last = ft_find_num_room(room_last, last->room);
	last_copy_room = last->room;
	last->len = last_in_last + 1 + (ft_len_room_list(copy) - 1 - last_in_conf);
	last->room = (t_room **)malloc(sizeof(t_room *) * (last->len + 1));
	last->room[last->len] = NULL;
	while (i <= last_in_last && ++i)
		last->room[i - 1] = last_copy_room[i - 1];
	last->room[i - 1]->path = last->num;
	while (copy[last_in_conf] && ++i && ++last_in_conf)
	{
		last->room[i - 1] = copy[last_in_conf];
		if (last->room[i - 1])
			last->room[i - 1]->path = last->num;
	}
	last->suur = 0;
	free(copy);
	free(last_copy_room);
	return (1);
}

int			ft_repath_first(t_path *conf, t_path *last,
t_room *room_first, t_room *room_last)
{
	t_room	**copy;
	int		first_in_conf;
	int		first_in_last;
	int		i;
	int		i_last;

	copy = conf->room;
	first_in_conf = ft_find_num_room(room_first, conf->room);
	first_in_last = ft_find_num_room(room_first, last->room);
	conf->len = first_in_conf + 1 + last->len - first_in_last - 1;
	conf->room = (t_room **)malloc(sizeof(t_room *) * (conf->len + 1));
	conf->room[conf->len] = NULL;
	i_last = first_in_last + 1;
	i = 0;
	while (i <= first_in_conf && ++i)
		conf->room[i - 1] = copy[i - 1];
	while (last->room[i_last] && ++i && ++i_last)
		conf->room[i - 1] = last->room[i_last - 1];
	conf->suur = 0;
	ft_repath_second(copy, last, room_last);
	return (1);
}
