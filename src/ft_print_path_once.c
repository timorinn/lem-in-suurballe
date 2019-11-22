/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_path_once.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:46:08 by bford             #+#    #+#             */
/*   Updated: 2019/11/22 12:48:59 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_print_path_once(t_path *path, char *s)
{
	int j;

	if (!path)
		return ;
	printf("%s", s);
   	j = 0;
	if (path->room)
	{
		while (j < path->len && ++j)
			printf("%d ", path->room[j - 1]->num);
		printf("suur = %d num = %d\n", path->suur, path->num);
	}
}