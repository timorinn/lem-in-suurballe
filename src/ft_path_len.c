/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bford <bford@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:53:27 by bford             #+#    #+#             */
/*   Updated: 2019/11/22 12:40:57 by bford            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_path_len(t_path *itog)
{
	int		len;

	len = 0;
	while (itog && ++len)
		itog = itog->next;
	return (len);
}
