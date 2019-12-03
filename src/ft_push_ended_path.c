/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_ended_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:41:07 by bford             #+#    #+#             */
/*   Updated: 2019/12/03 09:29:38 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_path	*ft_clone_path(t_path *buf)
{
	t_path	*path;
	int		i;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(path->room = (t_room **)malloc(sizeof(t_room *) * (buf->len + 1))))
	{
		free(path);
		return (NULL);
	}
	path->len = buf->len;
	i = buf->len;
	path->room[i] = NULL;
	while (--i >= 0)
		path->room[i] = buf->room[i];
	path->suur = 0;
	path->next = NULL;
	return (path);
}

int				ft_push_ended_path(t_path **buf, t_path **path)
{
	t_path	*copy;

	copy = *path;
	if (copy)
	{
		while (copy->next)
			copy = copy->next;
		return ((copy->next = ft_clone_path(*buf)) ? 1 : 0);
	}
	return ((*path = ft_clone_path(*buf)) ? 1 : 0);
}
