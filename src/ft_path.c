/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:56:47 by bford             #+#    #+#             */
/*   Updated: 2019/11/20 21:16:58 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_no_copies(t_path *buf, int room_num);
void	ft_null_room(t_room *room);
int		ft_find_end(t_room *room);
int		ft_find_start(t_room *room);
t_path	*ft_make_buf(int start);
t_path	*ft_clone_path(t_path *buf);
int		ft_ended_path(t_path **buf, int end);
int		ft_push_ended_path(t_path **buf, t_path **path);
t_link	*ft_get_link(t_room *room, t_path *buf);
int		ft_push_tail(t_path **buf, t_link *buf_child);
void	ft_buf_up(t_path **buf);
void	ft_del_link(t_room *room, t_path *path);
t_room	*ft_get_room(t_room *room, int num);
int		ft_get_path(t_room *room, t_path **path);
void	ft_find_path(t_room *room, t_path **path);

int		ft_no_copies(t_path *buf, int room_num)
{
	int		i;
	int		*way;

	i = buf->len - 1;
	way = buf->way;
	while (i >= 0)
	{
		if (way[i] == room_num)
			return (0);
		i--;
	}
	return (1);
}

void	ft_null_room(t_room *room)
{
	while (room)
	{
		room->visit = 0;
		room = room->next;
	}
}

int		ft_find_end(t_room *room)
{
	while (room->end == 0)
		room = room->next;
	return (room->num);
}

int		ft_find_start(t_room *room)
{
	while (room->start == 0)
		room = room->next;
	return (room->num);
}

t_path	*ft_make_buf(int start)
{
	t_path	*buf;

	if (!(buf = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(buf->way = (int *)malloc(sizeof(int))))
	{
		free(buf);
		return (NULL);
	}
	buf->len = 1;
	buf->suur = 0;
	buf->way[0] = start;
	buf->num = 0;
	buf->next = NULL;
	return (buf);
}

t_path	*ft_clone_path(t_path *buf)
{
	t_path	*path;
	int		i;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(path->way = (int *)malloc(sizeof(int) * buf->len)))
	{
		free(path);
		return (NULL);
	}
	path->len = buf->len;
	i = buf->len;
	while (--i >= 0)
		path->way[i] = buf->way[i];
	path->next = NULL;
	return (path);
}

int		ft_ended_path(t_path **buf, int end)
{
	return (*buf && (*buf)->way[(*buf)->len - 1] == end ? 1 : 0);
}

int		ft_push_ended_path(t_path **buf, t_path **path)
{
	t_path	*copy;

	copy = *path;
	if (copy)
	{
		while (copy->next)
			copy = copy->next;
		copy->next = ft_clone_path(*buf);
		*buf = (*buf)->next;
		return (1);
	}
	*path = ft_clone_path(*buf);
	*buf = (*buf)->next;
	return (1);
}

t_link	*ft_get_link(t_room *room, t_path *buf)
{
	int		room_num;

	room_num = buf->way[buf->len - 1];
	while (room->num != room_num)
		room = room->next;
	if (room->visit)
		return (NULL);
	room->visit = 1;
	return (room->link);
}

int		ft_push_tail(t_path **buf, t_link *buf_child)
{
	t_path	*copy;
	t_room	*roomadd;
	int		i;
	int		room_num;
	int		status;

	copy = *buf;
	roomadd = buf_child->room;
	room_num = roomadd->num;
	
	printf("PushTail Roomadd_num = %d\n", room_num);
	ft_print_path(*buf, "BUF DO PT\n");

/*
	if ((*buf)->suur == 1 && !roomadd->suur)
		return (0);
	else if ((*buf)->suur == 2)
		(*buf)->suur = 0;
*/

	if ((*buf)->suur == 0)
		status = roomadd->suur ? 1 : 0;
	else if ((*buf)->suur == 1 && !roomadd->suur)
		return (0);
	else if ((*buf)->suur == 1 && roomadd->suur)
		status = 2;
//	else if ((*buf)->suur == 2 && roomadd->suur)
//		status = 2;
	else if ((*buf)->suur == 2 && !roomadd->suur)
		status = 0;

	while (copy->next)
		copy = copy->next;
	copy->next = (t_path *)malloc(sizeof(t_path));
	copy->next->way = (int *)malloc(sizeof(int) * ((*buf)->len + 1));
	copy = copy->next;
	copy->len = (*buf)->len + 1;

/*
	if (!(*buf)->suur)
		copy->suur = (roomadd->suur ? 1 : 0);
	else if (roomadd->suur && (*buf)->suur == 1)
		copy->suur = 2;
	else if (roomadd->suur && (*buf)->suur == 2)
		copy->suur = 0;
*/
	//copy->suur = (*buf)->suur;
	copy->suur = status;
	i = (*buf)->len;
	copy->way[i] = room_num;
	while (--i >= 0)
		copy->way[i] = (*buf)->way[i];
	copy->next = NULL;
	ft_print_path(*buf, "BUF AFTER PT\n");
	return (1);
}

void	ft_buf_up(t_path **buf)
{
	t_path	*copy;

	copy = *buf;
	*buf = (*buf)->next;
	free(copy->way);
	free(copy);
}

void	ft_del_connect(t_link **mainlink, t_link **link)
{
	t_link	*copy;

	copy = *mainlink;
	if (*link == *mainlink)
	{
		copy = (*mainlink)->next;
		if (*mainlink)
			free(*mainlink);
		*mainlink = copy;
		//ft_print_link(*mainlink);
		return ;
	}
	while ((*mainlink)->next != *link)
		*mainlink = (*mainlink)->next;
	(*mainlink)->next = (*link)->next;
	if (*link)
		free(*link);
	*mainlink = copy;
}

void	ft_del_link(t_room *room, t_path *path)
{
	int		i;
	t_link	*link;
	t_link	*mainlink;
	t_room	*tmp;
	t_room	*prev;

	i = 1;
	while (path->next)
		path = path->next;
	while (i < path->len)
	{
		prev = ft_get_room(room, path->way[i - 1]);
		prev->suur = 1;
		link = prev->link;
		mainlink = link;
		tmp = ft_get_room(room, path->way[i]);
		if (link)
		{
			while (link->room != tmp)
				link = link->next;
			link->status = 0;
			//ft_del_connect(&mainlink, &link);
		}
		i++;
	}
}

t_room	*ft_get_room(t_room *room, int num)
{
	while (room->num != num)
		room = room->next;
	return (room);
}

int		ft_get_path(t_room *room, t_path **path)
{
	t_path	*buf;
	t_link	*buf_child;
	int		end;
	int		start;

	start = ft_find_start(room);
	end = ft_find_end(room);
	buf = ft_make_buf(start);
	while (buf)
	{
		
		ft_print_path(buf, "Buf\n");
	
		if (ft_ended_path(&buf, end))
		{
			ft_push_ended_path(&buf, path);
			ft_null_room(room);
			ft_del_link(room, *path);
			return (1);
		}
		buf_child = ft_get_link(room, buf);
		while (buf_child)
		{
			if (buf_child->status && ft_no_copies(buf, buf_child->room->num))
				ft_push_tail(&buf, buf_child);
			buf_child = buf_child->next;
		}
		ft_buf_up(&buf);
	}
	return (0);
}

void	ft_find_path(t_room *room, t_path **path)
{
	room->suur = 0;
	ft_get_path(room, path);
	ft_print_path(*path, "RESULT 1 \n");

	room->suur = 0;

	ft_print_room_and_link(room);
	ft_get_path(room, path);
	ft_print_path(*path, "RESULT 2 \n");

	room->suur = 0;

	ft_print_room_and_link(room);
	ft_get_path(room, path);
	ft_print_path(*path, "RESULT 3 \n");
}
