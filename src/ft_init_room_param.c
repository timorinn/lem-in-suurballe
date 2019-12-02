/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_room_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:10:23 by bford             #+#    #+#             */
/*   Updated: 2019/12/02 16:13:34 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_params	ft_init_room_param(t_input **input)
{
	t_params	par;

	while (input && (*input)->s[0] == '#')
	{
		if (!ft_strcmp((*input)->s, "##start") ||
		!ft_strcmp((*input)->s, "##end"))
		{
			par.ants = 0;
			return (par);
		}
		*input = (*input)->next;
	}
	if (!input || !ft_isint((*input)->s, 1, 0, 1))
		par.ants = 0;
	else
		par.ants = ft_atoi((*input)->s);
	par.num = 0;
	par.startend = 0;
	par.links = 0;
	return (par);
}
