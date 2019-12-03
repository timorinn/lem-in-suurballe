/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analize_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:35:06 by bford             #+#    #+#             */
/*   Updated: 2019/12/03 10:10:06 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_input	*ft_make_list_input(int fd)
{
	t_input		*input;
	t_input		*copy;
	char		*line;
	int			t;

	input = NULL;
	while ((t = get_next_line(fd, &line, 0)) == 1)
	{
		if (!input)
		{
			if ((!(input = ft_lstnew_input(line)) &&
			get_next_line(0, NULL, 1)) ||
			!(copy = input))
				return (NULL);
		}
		else
		{
			if ((!(copy->next = ft_lstnew_input(line)) &&
			get_next_line(0, NULL, 1)) ||
			!(copy = copy->next))
				return (NULL + ft_lstdel_input(input));
		}
	}
	get_next_line(0, NULL, 1);
	return (t != -1 ? input : NULL + ft_lstdel_input(input));
}

t_input			*ft_analize_input(void)
{
	t_input		*input;

	input = ft_make_list_input(0);
	return (input);
}
