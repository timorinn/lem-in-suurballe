/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_tail.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:56:02 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 11:39:49 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ft_init_status(int buf_suur, int room_suur, int *status)
{
	if (buf_suur == 0)
		*status = room_suur ? 1 : 0;
	else if (buf_suur == 1 && !room_suur)
		return (0);
	else if (buf_suur == 1 && room_suur)
		*status = 2;
	else if (buf_suur == 2 && !room_suur)
		*status = 0;
	else
		*status = 0;
	return (1);
}

int			ft_push_tail(t_path **buf, t_link *buf_child)
{
	t_path	*copy;
	t_room	*roomadd;
	int		i;
	int		status;

	copy = *buf;
	roomadd = buf_child->room;
	roomadd->visit = 1;
	if (!ft_init_status((*buf)->suur, roomadd->suur, &status))
		return (0);
	while (copy->next)
		copy = copy->next;
	copy->next = (t_path *)malloc(sizeof(t_path));
	copy->next->room = (t_room **)malloc(sizeof(t_room *) * ((*buf)->len + 2));
	copy = copy->next;
	copy->len = (*buf)->len + 1;
	copy->suur = status;
	i = (*buf)->len;
	copy->room[i + 1] = NULL;
	copy->room[i] = roomadd;
	while (--i >= 0)
		copy->room[i] = (*buf)->room[i];
	copy->next = NULL;
	return (1);
}
