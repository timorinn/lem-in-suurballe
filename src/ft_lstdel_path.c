/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:24:31 by bford             #+#    #+#             */
/*   Updated: 2019/11/21 16:54:15 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_lstdel_path(t_path *path)
{
	t_path		*next;
	t_path		*copy;

	copy = path;
	while (path)
	{
		next = path->next;
		if (path->room)
		{
			free(path->room);
			path->room = NULL;
		}
		free(path);
		path = next;
	}
	copy = NULL;
	return (0);
}
