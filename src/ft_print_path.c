/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:10:48 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 15:25:46 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_print_color(int *c, char *path_name, int flag)
{
	if (*c == 0 && flag & 10)
		ft_putstr("\033[0;31m");
	else if (*c == 1 && flag & 10)
		ft_putstr("\033[0;32m");
	else if (*c == 2 && flag & 10)
		ft_putstr("\033[0;33m");
	else if (*c == 3 && flag & 10)
		ft_putstr("\033[0;34m");
	else if (*c == 4 && flag & 10)
		ft_putstr("\033[0;35m");
	else if (*c == 5 && flag & 10)
		ft_putstr("\033[0;36m");
	ft_putstr(path_name);
	if (flag & 10)
		ft_putstr("\033[0m");
	if (*c == 5)
		*c = 0;
	else
		(*c)++;
}

void		ft_print_path(t_path *path, int flag)
{
	int		j;
	int		c;

	if (!path)
		return ;
	write(1, "\n", 1);
	while (path)
	{
		j = 0;
		c = 0;
		if (path->room)
		{
			while (j < path->len && ++j)
			{
				ft_print_color(&c, path->room[j - 1]->name, flag);
				if (j < path->len)
					write(1, " -> ", 4);
			}
			write(1, "\n", 1);
		}
		path = path->next;
	}
}
