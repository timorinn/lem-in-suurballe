/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:10:48 by bford             #+#    #+#             */
/*   Updated: 2019/11/21 21:56:53 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_print_path(t_path *path, char *s)
{
	int j;

	if (!path)
		return ;
	printf("%s", s);
	while (path)
	{
   		j = 0;
		if (path->room)
		{
			while (j < path->len && ++j)
				printf("%d ", path->room[j - 1]->num);
			printf("suur = %d num = %d\n", path->suur, path->num);
		}
        path = path->next;
    }
}