/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_malloc_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:51:17 by bford             #+#    #+#             */
/*   Updated: 2019/11/25 18:45:50 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_path	*re_path_lstnew(t_path *answer)
{
	t_path	*new;
	int		i;

	new = (t_path *)malloc(sizeof(t_path));
	new->len = answer->len;
	new->room = (t_room **)malloc(sizeof(t_room *) * (new->len + 1));
	i = 0;
	while (i < new->len)
	{
		new->room[i] = answer->room[i];
		i++;
	}
	//new->suur = answer->suur;
	new->num = answer->num;
	new->room[i] = NULL;
	new->next = NULL;
	return (new);
}

static void		re_push_tail(t_path **new, t_path *answer)
{
	t_path	*tmp;

	if (!*new)
		*new = re_path_lstnew(answer);
	else
	{
		tmp = *new;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = re_path_lstnew(answer);
	}
}

t_path			*re_malloc_path(t_path *path)
{
	t_path *new;

	new = NULL;
	while (path)
	{
		re_push_tail(&new, path);
		path = path->next;
	}
	return (new);
}
