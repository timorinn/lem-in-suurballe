/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_start_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:18:08 by bford             #+#    #+#             */
/*   Updated: 2019/12/02 16:47:50 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_check_start_end(t_room *room)
{
	int		i;

	i = 0;
	while (room)
	{
		if (room->start)
			i++;
		if (room->end)
			i += 10;
		room = room->next;
	}
	return (i == 11 ? 1 : 0);
}
