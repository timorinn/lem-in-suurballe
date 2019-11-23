/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_and_other.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 13:00:46 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 15:24:15 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_flag_and_other(int argc, char **argv, t_path *path)
{
	int		i;
	int		flag;

	flag = 0;
	if (argc-- > 1)
	{
		i = 1;
		while (argv[argc][i])
		{
			if (argv[argc][i] == 'p' && (flag % 10) == 0)
				flag++;
			if (argv[argc][i] == 'c' && (flag & 10) == 0)
				flag += 10;
			i++;
		}
	}
	if (flag % 10)
		ft_print_path(path, flag);
	return (1);
}
