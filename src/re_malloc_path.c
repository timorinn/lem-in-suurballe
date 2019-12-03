/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_malloc_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:51:17 by bford             #+#    #+#             */
/*   Updated: 2019/12/03 10:43:44 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path		*re_path_lstnew(t_path *answer)
{
	t_path	*new;
	int		i;

	if (!(new = (t_path *)malloc(sizeof(t_path))) ||
	!(new->room = (t_room **)malloc(sizeof(t_room *) * (answer->len + 1))))
		return (NULL + ft_lstdel_path(&new) - 1);
	new->len = answer->len;
	i = 0;
	while (i < new->len)
	{
		new->room[i] = answer->room[i];
		i++;
	}
	new->suur = 0;
	new->num = answer->num;
	new->room[i] = NULL;
	new->next = NULL;
	return (new);
}

int			re_push_tail(t_path **new, t_path *answer)
{
	t_path	*tmp;

	if (!*new)
	{
		if (!(*new = re_path_lstnew(answer)))
			return (-1);
	}
	else
	{
		tmp = *new;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = re_path_lstnew(answer)))
			return (-1);
	}
	return (1);
}

t_path		*re_malloc_path(t_path *path)
{
	t_path *new;

	new = NULL;
	while (path)
	{
		if (re_push_tail(&new, path) == -1)
			return (NULL + ft_lstdel_path(&new) - 1);
		path = path->next;
	}
	return (new);
}
