/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:38:27 by bford             #+#    #+#             */
/*   Updated: 2019/11/19 17:25:01 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_print_link(t_link *link)
{
	int		i;

	i = 0;
	if (link)
		printf("FT_PRINT_LINK\n");
	else
	{
		printf("NO LINKS!\n");
		return ;
	}
	while (link)
	{
		printf("Link %d | Room_%d\n", i, link->room->num);
		i++;
		link = link->next;
	}
}