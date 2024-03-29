/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ant.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:45:14 by bford             #+#    #+#             */
/*   Updated: 2019/12/02 16:22:16 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_get_ant(t_room *room)
{
	if (!room)
		return (0);
	while (!(room->start))
		room = room->next;
	return (room->ant);
}
