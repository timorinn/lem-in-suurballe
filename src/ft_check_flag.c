/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 13:08:01 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 15:08:08 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_check_flag(int argc, char **argv)
{
	int		i;

	if (argc-- > 1)
	{
		i = 1;
		if (argv[argc][0] != '-')
			return (0);
		while (argv[argc][i])
		{
			if (argv[argc][i] != 'p' && argv[argc][i] != 'c')
				return (0);
			i++;
		}
	}
	return (1);
}
