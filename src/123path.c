/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   123path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:20:12 by bford             #+#    #+#             */
/*   Updated: 2019/11/19 22:59:06 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		*concat_way(t_path **buf, int num);
t_path	*new_lst_path(t_path **buf, int num);
int		push_tail(t_path **start, t_path **buf, int num);
t_path	*pop_path(t_path **start);
int		ended_path(t_path **l, int end);
void	push_bottom_path(t_path **start, t_path **buf);
int		lenfth(t_path *l);
t_link	*get_link(t_room *room, t_path *buf);
int		get_end(t_room *room);
int		no_dublicate(t_path *buf, t_link *buf_child);



int		*concat_way(t_path **buf, int num)
{
	int		*array;
	int		i;

	if (!(array = (int *)malloc(sizeof(int) * (*buf)->len + 1)))
		return (NULL);
	i = 0;
	while (i < (*buf)->len)
	{
		array[i] = (*buf)->way[i];
		i++;
	}
	array[i] = num;
	return (array);
}

t_path	*new_lst_path(t_path **buf, int num)
{
	t_path	*new;

	if (!(new = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(new->way = concat_way(buf, num)))
		return (NULL + ft_lstdel_path(new));
	new->next = NULL;
	new->len = (*buf)->len + 1;
	return (new);
}

int		push_tail(t_path **start, t_path **buf, int num)
{
	t_path	*temp;

	if (*start == NULL && buf == NULL)
	{
		if (!(*start = (t_path *)malloc(sizeof(t_path))))
			return (ft_lstdel_path(*buf));
		if (!((*start)->way = (int *)malloc(sizeof(int))))
			return (ft_lstdel_path(*start) + ft_lstdel_path(*buf));
		(*start)->next = NULL;
		(*start)->len = 1;
		(*start)->way[0] = num;
	}
	else if (*start == NULL && *buf != NULL)
	{
		if (!(*start = new_lst_path(buf, num)))
			return (ft_lstdel_path(*start) + ft_lstdel_path(*buf));
	}
	else
	{
		temp = *start;
		while (temp->next)
			temp = temp->next;
		if (!(temp->next = new_lst_path(buf, num)))
			return (ft_lstdel_path(*start) + ft_lstdel_path(*buf));
	}
	return (1);
}

t_path	*pop_path(t_path **start)
{
	t_path	*l;

	if (*start == NULL)
		return (NULL);
	l = *start;
	*start = (*start)->next;
	return (l);
}

int		ended_path(t_path **l, int end)
{
	return (*l && (*l)->way[(*l)->len - 1] == end ? 1 : 0);
}

void	push_bottom_path(t_path **start, t_path **buf)
{
	t_path *l;

	l = *start;
	if (*start == NULL)
		*start = *buf;
	else
	{
		while (l->next)
			l = l->next;
		l->next = *buf;
	}
}

int lenfth(t_path *l)
{
	int i;

	i = 0;
	while (l)
	{
		i++;
		l = l->next;
	}
	return (i);
}

t_link	*get_link(t_room *room, t_path *buf)
{
	while (buf && room->num != buf->way[buf->len - 1])
		room = room->next;
	if (room->visit)
		return (NULL);
	room->visit = 1;
	return (room->link);
}

int		get_end(t_room *room)
{
	while (room->end == 0)
		room = room->next;
	return (room->num);
}

int		no_dublicate(t_path *buf, t_link *buf_child)
{
	int		i;

	i = 0;
	while (i < buf->len)
	{
		if (buf_child->room->num == buf->way[i])
			return (0);
		i++;
	}
	return (1);
}

int		get_start(t_room *room)
{
	while (room->start == 0)
		room = room->next;
	return (room->num);
}

int	ft_len_path(t_path *itog)
{
	int		len;

	len = 0;
	while (itog && ++len)
		itog = itog->next;
	return (len);
}

static t_room	*get_room(t_room *room, int num)
{
	while (room->num != num)
		room = room->next;
	return (room);
}

void	ft_del_link(t_link **link_list, t_link **link)
{
	t_link	*copy;

	copy = *link_list;
	if (*link == *link_list)
	{
		printf("___ROOM %d___\n", (*link)->room->num);
		copy = (*link)->next;
		free(*link_list);
		*link_list = copy;
		ft_print_link(*link_list);
		return ;
	}
	while ((*link_list)->next != *link)
		*link_list = (*link_list)->next;
	(*link_list)->next = (*link)->next;
	free(*link);
	*link_list = copy;
}

void	ft_null_room(t_room *room, t_path *answer)
{
	//int i;
	t_room	*copy;
	//t_link	*link;
	//t_link	*link_copy;

	//t_room	*ptr;
	answer+=0;

	copy = room;
	while (copy)
	{
		copy->visit = 0;
		copy = copy->next;
	}
	/*
	while (answer)
	{
		i = 1;
		while (i < answer->len)
		{
			link = get_room(room, answer->way[i - 1])->link;
			printf("ROOM_FOR_DEL_%d\n", link->room->num);
			link_copy = link;
			ptr = get_room(room, answer->way[i]);
			if (link)
			{
				while (link_copy && link_copy->room != ptr)
					link_copy = link_copy->next;
				if (link_copy)
					ft_del_link(&link, &link_copy);
			}
			i++;
		}
		answer = answer->next;
	}
	*/
}

void	ft_del_rebra(t_room *room, t_path *buf)
{
	int		i;
	t_link	*link;
	t_link	*link_copy;
	t_room	*ptr;

	i = 0;
	while (i < buf->len)
	{
		link = get_room(room, buf->way[i - 1])->link;
		printf("1_ROOM_FOR_DEL_%d\n", link->room->num);
		link_copy = link;
		ptr = get_room(room, buf->way[i]);
		printf("2_ROOM_FOR_DEL_%d\n", ptr->num);
		if (link)
		{
			while (link_copy && link_copy->room != ptr)
				link_copy = link_copy->next;
			if (link_copy)
				ft_del_link(&link, &link_copy);
		}
		i++;
	}
}

int		get_path(t_room *room, t_path **answer)
{
	t_path	*path;
	t_path  *buf;
	t_link  *buf_child;
	int		end;
	int		start;
	int		ant;

	start = get_start(room);
	ant = ft_get_ant(room);
	end = get_end(room);
	path = NULL;

	push_tail(&path, NULL, start);
	while (path)
	{
		buf = pop_path(&path);
		if (buf && ended_path(&buf, end))
		{
			buf->next = NULL;
			push_bottom_path(answer, &buf);

			printf("Room_and_link_1\n");
			ft_print_room_and_link(room);

			ft_print_path(*answer, "Answer!\n");

			ft_null_room(room, *answer);
			ft_del_rebra(room, buf);

			printf("Room_and_link_2\n");
			ft_print_room_and_link(room);
			return (1);
		}
		if (!buf)
			break;
		buf_child = get_link(room, buf);
	
		printf("BUF_CHILD\n");
		ft_print_link(buf_child);

		while (buf_child)
		{
			if (no_dublicate(buf, buf_child))
			{
				push_tail(&path, &buf, buf_child->room->num);
			}
			buf_child = buf_child->next;
		}
		/*
		if (buf)
		{
			free(buf->way);
			free(buf);
		}
		*/
	}
	return (0);
}
