/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_room_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:04:57 by bford             #+#    #+#             */
/*   Updated: 2019/12/02 16:47:17 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ft_check_valid(char **array)
{
	if (ft_array_size((void **)array) != 3 || array[0][0] == 'L' ||
	array[0][0] == '#' || !ft_isint(array[1], 0, 0, 1) ||
	!ft_isint(array[2], 0, 0, 1) || ft_strchr(array[0], '-'))
		return (1);
	return (0);
}

static int	ft_check_final(char **array, t_params *par, t_room *room)
{
	while (room->next)
		room = room->next;
	return ((room->next = ft_lstnew_room(array[0], ft_atoi(array[1]),
	ft_atoi(array[2]), par)) ? 1 : 0);
}

t_room		*ft_make_room_list(char *s, t_room *room, t_params *par)
{
	t_room	*copy;
	char	**array;

	copy = room;
	if (!(array = ft_strsplit(s, ' ')))
		return (NULL);
	if (ft_array_size((void **)array) == 1 && ((*par).links = 1))
	{
		return ((*par).startend == 22 ? ft_delstr_arr(array) + room :
		NULL + ft_delstr_arr(array) + ft_del_all(NULL, room));
	}
	if (ft_check_valid(array))
		return (NULL + ft_delstr_arr(array) + ft_del_all(NULL, room));
	if (!room)
	{
		return ((room = ft_lstnew_room(array[0], ft_atoi(array[1]),
		ft_atoi(array[2]), par)) ? room + ft_delstr_arr(array) :
		ft_delstr_arr(array) + NULL);
	}
	while (copy->next)
		if (!ft_strcmp(copy->name, array[0]) || !(copy = copy->next))
			return (ft_del_all(NULL, room) + ft_delstr_arr(array) + NULL);
	return (ft_strcmp(copy->name, array[0]) && ft_check_final(array, par, room)
	? room + ft_delstr_arr(array) :
	NULL + ft_delstr_arr(array) + ft_del_all(NULL, room));
}
