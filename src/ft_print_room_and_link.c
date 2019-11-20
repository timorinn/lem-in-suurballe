/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_room_and_link.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:20:58 by bford             #+#    #+#             */
/*   Updated: 2019/11/20 21:17:38 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_print_room_and_link(t_room *room)
{
	t_link	*link;

	while (room)
	{
		printf("Room %d | visit = %d | suur = %d\n", room->num, room->visit, room->suur);
		link = room->link;
		if (!link)
			printf("No links\n");
		else
		{
			while (link)
			{
				if (link->status)
					printf("%d  ", link->room->num);
				link = link->next;
			}
			printf("\n");
		}
		room = room->next;
	}
}
