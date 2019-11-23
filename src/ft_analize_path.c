/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analize_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:49:16 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 11:03:32 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_del_link(t_path *path, int path_num, int path_len)
{
	int		i;
	t_link	*link;
	t_room	*tmp;
	t_room	*prev;

	i = 1;
	while (path->next)
		path = path->next;
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

int			ft_analize_path(t_path **path, int path_num)
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
			return (ft_conflict(path, last, last->room[len_copy]->path));
		len_copy--;
	}
	ft_del_link(last, last->num, last->len);
	return (1);
}
