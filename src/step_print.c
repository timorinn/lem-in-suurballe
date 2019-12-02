/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:25:07 by bford             #+#    #+#             */
/*   Updated: 2019/12/02 14:22:27 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		set_step_ants(t_path *path, int x1, int l, int ants)
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

void		path_del_bad(t_path **answer)
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

void		steps_do_all(t_path *path, t_room *room, int total)
{
	int		ant_num;
	t_path	*buf;

	ant_num = 0;
	while (total)
	{
		buf = path;
		while (buf)
		{
			step_do_one(buf, room, 0, &ant_num);
			buf->step_ants--;
			buf = buf->next;
		}
		write(1, "\n", 1);
		total--;
	}
}

void		steps_print(t_path *path, t_room *room)
{
	int		x1;
	int		ants;
	int		total;

	ants = path->room[0]->ant;
	x1 = (ants + delta_len(path) + length_path(path) - 1) / length_path(path);
	path->step_ants = x1;
	set_step_ants(path->next, x1, path->len - 1, ants - x1);
	while (bad_path(path))
	{
		path_del_bad(&path);
		x1 = (ants + delta_len(path) + length_path(path) - 1) /
			length_path(path);
		path->step_ants = x1;
		set_step_ants(path->next, x1, path->len - 1, ants - x1);
	}
	total = path->len + x1 - 2;
	steps_do_all(path, room, total);
}
