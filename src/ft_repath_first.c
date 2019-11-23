/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repath_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 11:04:28 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 11:17:35 by bford            ###   ########.fr       */
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

static void	ft_relink_path(t_path *path)
{
	int		path_len;
	int		i;
	t_link	*link;

	i = 1;
	path_len = path->len;
	while (i < path_len)
	{
		link = path->room[i]->link;
		path->room[i]->path = path->num;
		while (link)
		{
			link->status = (link->room == path->room[i + 1] ? 0 : 1);
			link = link->next;
		}
		i++;
	}
}

static void	ft_clear_path_path(t_room **copy, t_room **last_copy_room)
{
	int		i;

	i = 0;
	while (copy[i])
	{
		copy[i]->path = -1;
		copy[i]->suur = 0;
		copy[i]->visit = 0;
		i++;
	}
	i = 0;
	while (last_copy_room[i])
	{
		last_copy_room[i]->path = -1;
		last_copy_room[i]->suur = 0;
		last_copy_room[i]->visit = 0;
		i++;
	}
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
	while (copy[last_in_conf] && ++i && ++last_in_conf)
		last->room[i - 1] = copy[last_in_conf];
	last->suur = 0;
	ft_clear_path_path(copy, last_copy_room);
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
	ft_relink_path(conf);
	ft_relink_path(last);
	return (1);
}
