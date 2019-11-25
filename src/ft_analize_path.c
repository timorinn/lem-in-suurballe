/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analize_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:49:16 by bford             #+#    #+#             */
/*   Updated: 2019/11/25 16:59:43 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_del_link(t_path *path)
{
	int		i;
	t_link	*link;
	t_room	*tmp;
	t_room	*prev;
	int		path_len;

	while (path)
	{
		i = 1;
		path_len = path->len;
		while (i < path_len)
		{
			prev = path->room[i - 1];
			prev->suur = 1;
			if (i > 1)
				prev->path = path->num;
			link = prev->link;
			tmp = path->room[i];
			if (link)
			{
				while (link->room != tmp)
					link = link->next;
				link->status = 0;
			}
			i++;
		}
		path = path->next;
	}
}

void		ft_reclear_room_and_link_and_status(t_room *room)
{
	t_link	*link;

	while (room)
	{
		room->path = -1;
		room->suur = 0;
		room->visit = 0;
		link = room->link;
		while (link)
		{
			link->status = 1;
			link = link->next;
		}
		room = room->next;
	}
}

int			ft_is_conflict(t_path *last)
{
	int		len_copy;

	len_copy = last->len - 2;
	while (len_copy >= 1)
	{
		if (last->room[len_copy]->path != -1 && last->room[len_copy]->path != last->num)
			return (1);
		len_copy--;
	}
	return (0);
}

int			ft_conflict_2(t_path *last, t_path **path)
{
	int		last_len;

	last_len = last->len - 2;
	while (last_len >= 1)
	{
		if (last->room[last_len]->path != -1 && last->room[last_len]->path != last->num)
		{
			ft_conflict(path, last, last->room[last_len]->path);
			return (1);
		}
		last_len--;
	}
	return (1);
}

int			ft_analize_path(t_path **path, int path_num, t_room *room)
{
	int		len_copy;
	t_path	*last;

	last = *path;
	while (last->next)
		last = last->next;
	if (!last)
		return (0);
	last->num = path_num;
	len_copy = last->len - 2;

	if (ft_is_conflict(last))
	{
		while (ft_is_conflict(last))
			ft_conflict_2(last, path);
		ft_reclear_room_and_link_and_status(room);
		ft_del_link(*path);
		return (1);
	}
	ft_del_link(last);
	return (1);
}
