/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:10:48 by bford             #+#    #+#             */
/*   Updated: 2019/11/20 17:30:04 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_print_path(t_path *path, char *s)
{
	int j;
	t_path *copy;

	copy = path;
	if (!path)
		return ;
	printf("%s", s);
	while (copy)
	{
   		j = 0;
		if (copy->way)
		{
			while (j < copy->len)
			{
				printf("%d ", copy->way[j]);
				j++;
			}
			printf("suur = %d\n", path->suur);
		}
        copy = copy->next;
    }
}