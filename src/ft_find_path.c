/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:31:45 by bford             #+#    #+#             */
/*   Updated: 2019/12/02 16:22:39 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_do_link(t_path *path)
{
	int		len;
	int		i;
	t_link	*link;

	i = 1;
	while (path)
	{
		i = 0;
		len = path->len;
		while (i < len)
		{
			link = path->room[i]->link;
			path->room[i]->path = path->num;
			while (link)
			{
				if (link->room == path->room[i + 1])
					link->status = 0;
				link = link->next;
			}
			i++;
		}
		path = path->next;
	}
}

static void		ft_clear_link(t_room *room)
{
	t_link	*link;

	while (room)
	{
		link = room->link;
		while (link)
		{
			link->status = 1;
			link = link->next;
		}
		room = room->next;
	}
}

void			ft_find_path(t_room *room, t_path **path, int ant)
{
	int		path_num;
	t_path	*new;

	new = NULL;
	path_num = 0;
	if (!room)
		return ;
	while (ft_get_path(room, path, ft_find_start(room), ft_find_end(room)))
	{
		ft_clear_link(room);
		ft_analize_path(path, path_num++, room);
		ft_do_link(*path);
		if (!new)
			new = re_malloc_path(*path);
		else if (ft_len_output(new, ant, 0) > ft_len_output(*path, ant, 0) &&
		ft_lstdel_path(&new))
			new = re_malloc_path(*path);
		else if (ft_lstdel_path(path) && (*path = new))
			break ;
	}
	if (new != *path)
		ft_lstdel_path(&new);
}
