/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_add_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:11:06 by bford             #+#    #+#             */
/*   Updated: 2019/12/02 14:23:55 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			length_path(t_path *l)
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

int			delta_len(t_path *a)
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

void		step_display(t_room *cont)
{
	char	*s;
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;

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

void		step_do_one(t_path *buf, t_room *room, int num, int *ant_num)
{
	t_room	*cur;
	t_room	*cont;

	cur = buf->room[num];
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
		step_display(cont);
	}
}
