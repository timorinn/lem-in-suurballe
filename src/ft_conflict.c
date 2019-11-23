/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conflict.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:59:23 by bford             #+#    #+#             */
/*   Updated: 2019/11/23 11:00:24 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room	*ft_find_last_room(t_path *last, t_path *conf)
{
	int		len_last;
	int		len_conf;
	int		i_last;
	int		i_conf;

	i_last = 1;
	len_last = last->len - 1;
	len_conf = conf->len - 1;
	while (i_last < len_last)
	{
		i_conf = 1;
		while (i_conf < len_conf)
		{
			if (last->room[i_last] == conf->room[i_conf])
				return (last->room[i_last]);
			i_conf++;
		}
		i_last++;
	}
	return (NULL);
}

static t_room	*ft_find_first_room(t_path *last, t_path *conf)
{
	int		len_last;
	int		len_conf;
	int		i_last;
	int		i_conf;

	i_conf = 1;
	len_last = last->len - 1;
	len_conf = conf->len - 1;
	while (i_conf < len_conf)
	{
		i_last = 1;
		while (i_last < len_last)
		{
			if (last->room[i_last] == conf->room[i_conf])
				return (last->room[i_last]);
			i_last++;
		}
		i_conf++;
	}
	return (NULL);
}

int				ft_conflict(t_path **path, t_path *last, int num_conf_path)
{
	t_path	*conf;

	conf = *path;
	while (conf->num != num_conf_path)
		conf = conf->next;
	ft_repath_first(conf, last,
	ft_find_first_room(last, conf), ft_find_last_room(last, conf));
	return (0);
}
