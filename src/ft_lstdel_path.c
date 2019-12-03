/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:24:31 by bford             #+#    #+#             */
/*   Updated: 2019/12/03 09:40:12 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_lstdel_path(t_path **path)
{
	t_path	*buf;

	while (*path)
	{
		buf = *path;
		*path = (*path)->next;
		if (buf->room)
			free(buf->room);
		buf->room = NULL;
		free(buf);
		buf = NULL;
	}
	return (1);
}
