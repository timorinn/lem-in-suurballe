/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:08:18 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 09:34:01 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_len_output(t_path *answer, int ant, int dop)
{
	t_path	*copy;
	int		max;
	int		paths;

	paths = (dop > 0 ? 1 : 0);
	copy = answer;
	max = -1;
	while (copy && ++paths)
		copy = copy->next;
	copy = answer;
	ant -= paths;
	while (copy)
	{
		max = (max < copy->len - 1 ? copy->len - 1 : max);
		copy = copy->next;
	}
	max = (max > dop - 1 ? max : dop - 1);
	while (answer)
	{
		ant -= (max + 1 - answer->len ? max + 1 - answer->len : 0);
		answer = answer->next;
	}
	ant -= ((dop > 0) && (max + 1 - dop) ? max + 1 - dop : 0);
	ant = (ant < 0 ? 0 : ant);
	return (max + ant / paths + !!(ant % paths));
}
