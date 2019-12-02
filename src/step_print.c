/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:25:07 by bford             #+#    #+#             */
/*   Updated: 2019/12/02 13:09:50 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		length_path(t_path *l)
{
	int i;

	i = 0;
	while (l)
	{
		l = l->next;
		i++;
	}
	return (i);
}

int		delta_len(t_path *a)
{
	int l1;
	int l2;
	int l;

	l1 = a->len - 1;
	l = 0;
	a = a->next;
	while (a)
	{
		l2 = a->len - 1;
		l = l + l2 - l1;
		a = a->next;
	}
	return (l);
}

t_room	*get_room(t_room *room, int num)
{
	while (room->num != num)
		room = room->next;
	return (room);
}

void step_do_one(t_path *buf, t_room *room, int num, int *ant_num)
{
	t_room	*cur;
	t_room	*cont;
	char	*s;
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;

	cur = buf->room[num];
	//ft_putstr(cur->name);
	//ft_putstr("* ");
	if (cur->end)
		return ;
	step_do_one(buf, room, num + 1, ant_num);
	if (cur->start && buf->step_ants <= 0)
		return ;
	if (cur->ant)
	{
		cont = buf->room[num + 1];
		cur->ant--;
		cont->ant++;
		if (cur->start)
		{
			(*ant_num)++;
			cont->ant_num = *ant_num;
		}
		else
			cont->ant_num = cur->ant_num;
		s4 = ft_itoa(cont->ant_num);
		s1 = ft_strjoin("L", s4);
		s2 = ft_strjoin(cont->name, " ");
		s3 = ft_strjoin("-", s2);
		s = ft_strjoin(s1, s3);
		ft_putstr(s);
		free(s);
		free(s1);
		free(s2);
		free(s3);
		free(s4);
	}
}

void set_step_ants(t_path *path, int x1, int l, int ants)
{
	if (path == NULL)
		return ;
	if (path->next == NULL)
	{
		path->step_ants = ants;
		return ;
	}
	path->step_ants = x1 - (path->len - 1 - l);
	set_step_ants(path->next, x1, l, ants - path->step_ants);
}

t_path	*get_last_path(t_path *answer)
{
	while (answer->next)
		answer = answer->next;
	return (answer);
}

void	path_del_bad(t_path **answer)
{
	t_path	*buf;
	t_path	*tmp;

	if ((*answer)->step_ants <= 0)
	{
		buf = *answer;
		*answer = (*answer)->next;
		free(buf->room);
		free(buf);
	}
	else
	{
		tmp = *answer;
		while (tmp->next->step_ants > 0)
			tmp = tmp->next;
		buf = tmp->next;
		tmp->next = tmp->next->next;
		free(buf->room);
		free(buf);
	}
}

int			bad_path(t_path *path)
{
	while (path)
	{
		if (path->step_ants <= 0)
			return (1);
		path = path->next;
	}
	return (0);
}

void		steps_print(t_path *path, t_room *room)
{
	int x1;
	int ants;
	int total;
	t_path *buf;
	int ant_num;

	ant_num = 0;
	ants = path->room[0]->ant;
	x1 = (ants + delta_len(path) + length_path(path) - 1) / length_path(path);
	path->step_ants = x1;
	set_step_ants(path->next, x1, path->len - 1, ants - x1);
	while (bad_path(path))
	{
		path_del_bad(&path);
		x1 = (ants + delta_len(path) + length_path(path) - 1) / length_path(path);
		path->step_ants = x1;
		set_step_ants(path->next, x1, path->len - 1, ants - x1);
	}
	total = path->len + x1 - 2;
	while (total)
	{
		buf = path;
		while (buf)
		{
			step_do_one(buf, room, 0, &ant_num);
			//usleep(10000);
			buf->step_ants--;
			buf = buf->next;
		}
		ft_putstr("\n");
		total--;
	}
}
