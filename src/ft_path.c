/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:56:47 by bford             #+#    #+#             */
/*   Updated: 2019/11/21 23:20:17 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_no_copies(t_path *buf, t_room *room);
void	ft_null_room(t_room *room);
t_room	*ft_find_end(t_room *room);
t_room	*ft_find_start(t_room *room);
t_path	*ft_make_buf(t_room *start);
t_path	*ft_clone_path(t_path *buf/*, int path_num*/);
int		ft_ended_path(t_path *buf, t_room *end);
int		ft_push_ended_path(t_path **buf, t_path **path/*, int path_num*/);
t_link	*ft_get_link(t_room *room, t_path *buf);
int		ft_push_tail(t_path **buf, t_link *buf_child);
void	ft_buf_up(t_path **buf);
void	ft_del_link(t_path *path, int path_num);
t_room	*ft_get_room(t_room *room, int num);
int		ft_get_path(t_room *room, t_path **path);
void	ft_find_path(t_room *room, t_path **path);
int		ft_analize_path(t_path **path, int path_num);
int		ft_confclict(t_path **path, t_path *last, int conflict_path);
t_room	*ft_find_first_room(t_path *last, t_path *conf);
t_room	*ft_find_last_room(t_path *last, t_path *conf);
int		ft_repath_first(t_path *conf, t_path *last,
	t_room *room_first, t_room *room_last);
int		ft_find_num_room(t_room *findroom, t_room **pathroom);
int		ft_len_room_list(t_room **list);
void	ft_relink_path(t_path *conf, t_path *last);


int		ft_no_copies(t_path *buf, t_room *room)
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

void	ft_null_room(t_room *room)
{
	while (room && !(room->visit = 0))
		room = room->next;
}

t_room	*ft_find_end(t_room *room)
{
	while (room->end == 0)
		room = room->next;
	return (room);
}

t_room	*ft_find_start(t_room *room)
{
	while (room->start == 0)
		room = room->next;
	return (room);
}

t_path	*ft_make_buf(t_room *start)
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
	buf->room[0] = start;
	buf->room[1] = NULL;
	buf->num = 0;
	buf->next = NULL;
	return (buf);
}

t_path	*ft_clone_path(t_path *buf/*, int path_num*/)
{
	t_path	*path;
	int		i;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(path->room = (t_room **)malloc(sizeof(t_room *) * buf->len + 1)))
	{
		free(path);
		return (NULL);
	}
	path->len = buf->len;
	//path->num = path_num;
	i = buf->len;
	path->room[i] = NULL;
	while (--i >= 0)
		path->room[i] = buf->room[i];
	path->next = NULL;
	return (path);
}

int		ft_ended_path(t_path *buf, t_room *end)
{
	return (buf && buf->room[buf->len - 1] == end ? 1 : 0);
}

int		ft_push_ended_path(t_path **buf, t_path **path/*, int path_num*/)
{
	t_path	*copy;

	copy = *path;
	if (copy)
	{
		while (copy->next)
			copy = copy->next;
		copy->next = ft_clone_path(*buf/*, path_num*/);
		*buf = (*buf)->next;
		return (1);
	}
	*path = ft_clone_path(*buf/*, path_num*/);
	*buf = (*buf)->next;
	return (1);
}

int		ft_push_tail(t_path **buf, t_link *buf_child)
{
	t_path	*copy;
	t_room	*roomadd;
	int		i;
	int		status;

	copy = *buf;
	roomadd = buf_child->room;
	
	//printf("PushTail Roomadd_num = %d\n", room_num);
	//ft_print_path(*buf, "BUF DO PT\n");

	//if ((*buf)->suur == 1 && !roomadd->suur)
	//	return (0);
	//else if ((*buf)->suur == 2)
	//	(*buf)->suur = 0;

	if ((*buf)->suur == 0)
		status = roomadd->suur ? 1 : 0;
	else if ((*buf)->suur == 1 && !roomadd->suur)
		return (0);
	else if ((*buf)->suur == 1 && roomadd->suur)
		status = 2;
	//else if ((*buf)->suur == 2 && roomadd->suur)
	//	status = 2;
	else if ((*buf)->suur == 2 && !roomadd->suur)
		status = 0;

	while (copy->next)
		copy = copy->next;
	copy->next = (t_path *)malloc(sizeof(t_path));
	copy->next->room = (t_room **)malloc(sizeof(t_room *) * ((*buf)->len + 2));
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
	copy->room[i + 1] = NULL;
	copy->room[i] = roomadd;
	while (--i >= 0)
		copy->room[i] = (*buf)->room[i];
	copy->next = NULL;
	//ft_print_path(*buf, "BUF AFTER PT\n");
	return (1);
}

void	ft_buf_up(t_path **buf)
{
	t_path	*copy;

	copy = *buf;
	*buf = (*buf)->next;
	free(copy->room);
	free(copy);
}

void	ft_del_link(t_path *path, int path_num)
{
	int		i;
	int		path_len;
	t_link	*link;
	t_room	*tmp;
	t_room	*prev;

	i = 1;
	while (path->next)
		path = path->next;
	path_len = path->len;
	while (i < path_len)
	{
		prev = path->room[i - 1];
		prev->suur = 1;
		if (i > 1)
			prev->path = path_num;
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
	t_room	*end;
	t_room	*start;

	start = ft_find_start(room);
	end = ft_find_end(room);
	buf = ft_make_buf(start);
	while (buf)
	{
		if (ft_ended_path(buf, end))
		{
			ft_push_ended_path(&buf, path);
			ft_null_room(room);
			return (1);
		}
		buf_child = buf->room[buf->len - 1]->link;
		while (buf_child)
		{
			if (buf_child->status && ft_no_copies(buf, buf_child->room))
				ft_push_tail(&buf, buf_child);
			buf_child = buf_child->next;
		}
		ft_buf_up(&buf);
	}
	return (0);
}

t_room	*ft_find_last_room(t_path *last, t_path *conf)
{
	int		len_last;
	int		len_conf;
	int		i_last;
	int		i_conf;

	i_last = 1;
	len_last = last->len - 1;
	len_conf = conf->len - 1;
	while (i_last < len_last)
	{
		i_conf = 1;
		while (i_conf < len_conf)
		{
			if (last->room[i_last] == conf->room[i_conf])
				return (last->room[i_last]);
			i_conf++;
		}
		i_last++;
	}
	return (NULL);
}

t_room	*ft_find_first_room(t_path *last, t_path *conf)
{
	int		len_last;
	int		len_conf;
	int		i_last;
	int		i_conf;

	i_conf = 1;
	len_last = last->len - 1;
	len_conf = conf->len - 1;
	while (i_conf < len_conf)
	{
		i_last = 1;
		while (i_last < len_last)
		{
			if (last->room[i_last] == conf->room[i_conf])
				return (last->room[i_last]);
			i_last++;
		}
		i_conf++;
	}
	return (NULL);
}

int		ft_len_room_list(t_room **list)
{
	int		i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

int		ft_find_num_room(t_room *findroom, t_room **pathroom)
{
	int		i;

	i = 0;
	while (pathroom[i] != findroom)
		i++;
	return (i);
}

void	ft_relink_path(t_path *conf, t_path *last)
{
	int		conf_len;
	int		last_len;
	int		i;
	t_link	*link;

	i = 1;
	conf_len = conf->len;
	while (i < conf_len)
	{
		link = conf->room[i]->link;
		conf->room[i]->path = conf->num;
		while (link)
		{
			link->status = (link->room == conf->room[i + 1] ? 0 : 1);
			link = link->next;
		}
		i++;
	}
	i = 1;
	last_len = last->len;
	while (i < last_len)
	{
		link = last->room[i]->link;
		last->room[i]->path = last->num;
		while (link)
		{
			link->status = (link->room == last->room[i + 1] ? 0 : 1);
			link = link->next;
		}
		i++;
	}

}

int		ft_repath_second(t_room **copy, t_path *last, t_room *room_last)
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
	while (copy[last_in_conf] &&  ++i && ++last_in_conf)
		last->room[i - 1] = copy[last_in_conf];
	free(copy);
	free(last_copy_room);
	return (1);
}

int		ft_repath_first(t_path *conf, t_path *last,
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
	ft_repath_second(copy, last, room_last);
	ft_relink_path(conf, last);
	return (1);
}

int		ft_conflict(t_path **path, t_path *last, int num_conf_path)
{
	t_path	*conf;

	conf = *path;
	while (conf->num != num_conf_path)
		conf = conf->next;
	ft_repath_first(conf, last,
	ft_find_first_room(last, conf), ft_find_last_room(last, conf));
	return (0);
}

int		ft_analize_path(t_path **path, int path_num)
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
	while (len_copy >= 1)
	{
		if (last->room[len_copy]->path != -1)
		{
			return (ft_conflict(path, last, last->room[len_copy]->path));
		}
		len_copy--;
	}
	ft_del_link(last, last->num);
	return (1);
}

void	ft_clear_link(t_room *room)
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

void	ft_do_link(t_path *path)
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

void	ft_find_path(t_room *room, t_path **path)
{
	int		path_num;
	int		path_len;

	path_num = 0;
	path_len = 0;
	room->suur = 0;

	while (ft_get_path(room, path)/* < ft_limit_path(room)*/)
	{
		//room->suur = 0;
		ft_clear_link(room);
		ft_analize_path(path, path_num++);
		ft_do_link(*path);
		//ft_print_path(*path, "RESULT\n");
		//ft_print_room_and_link(room);
	}
	ft_print_path(*path, "RESULT\n");
	printf("Itog path len = %d\n", ft_path_len(*path));
	/*
	if (ft_path_len(*path) > path_len && ++path_len)
	{
		ft_analize_path(path, path_num++);
		ft_print_path(*path, "RESULT 1 \n");
		ft_print_room_and_link(room);
	}
	//room->suur = 0;
	ft_get_path(room, path);
	if (ft_path_len(*path) > path_len && ++path_len)
	{
		ft_analize_path(path, path_num++);
		ft_print_path(*path, "RESULT 2 \n");
		ft_print_room_and_link(room);
	}
	ft_get_path(room, path);
	if (ft_path_len(*path) > path_len && ++path_len)
	{
		ft_analize_path(path, path_num++);
		ft_print_path(*path, "RESULT 3 \n");
		ft_print_room_and_link(room);
	}
	*/
}
