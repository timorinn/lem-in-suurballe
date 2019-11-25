/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:34:35 by bford             #+#    #+#             */
/*   Updated: 2019/11/25 16:31:46 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_buf_up(t_path **buf)
{
	t_path	*copy;

	copy = *buf;
	*buf = (*buf)->next;
	free(copy->room);
	free(copy);
}

static int		ft_no_copies(t_path *buf, t_room *room)
{
	int		i;
	t_room	**buf_room;

	i = buf->len - 1;
	buf_room = buf->room;
	while (i >= 0)
	{
		if (buf_room[i] == room)
			return (0);
		i--;
	}
	return (1);
}

static int		ft_ended_path(t_path *buf, t_room *end)
{
	return (buf && buf->room[buf->len - 1] == end ? 1 : 0);
}

static t_path	*ft_make_buf(t_room *start)
{
	t_path	*buf;

	if (!(buf = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(buf->room = (t_room **)malloc(sizeof(t_room *) * 2)))
	{
		free(buf);
		return (NULL);
	}
	buf->len = 1;
	buf->suur = 0;
	buf->suur_path = -1;
	buf->room[0] = start;
	buf->room[1] = NULL;
	buf->num = 0;
	buf->next = NULL;
	return (buf);
}

int				ft_get_path(t_room *room, t_path **path,
t_room *start, t_room *end)
{
	t_path	*buf;
	t_link	*buf_child;

	buf = ft_make_buf(start);
	while (buf)
	{
		if (ft_ended_path(buf, end))
		{
			ft_push_ended_path(&buf, path);
			ft_lstdel_path(&buf);
			ft_null_room(room);
			return (1);
		}
		buf_child = buf->room[buf->len - 1]->link;
		while (buf_child)
		{
			if (buf_child->status && !(buf_child->room->visit) &&
			ft_no_copies(buf, buf_child->room))
				ft_push_tail(&buf, buf_child);
			buf_child = buf_child->next;
		}
		ft_buf_up(&buf);
	}
	return (0);
}
