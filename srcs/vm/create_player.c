/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 15:07:44 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/16 05:18:32 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_player	*check_number(int number)
{
	t_player	*tmp;

	tmp = g_players;
	while (tmp != NULL)
	{
		if (tmp->number == number)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int			create_player(int number)
{
	t_player	*new;

	if (!(new = ft_memalloc(sizeof(t_player) + 1)))
		return (-1);
	new->next = g_players;
	new->number = number;
	new->live = 0;
	g_players = new;
	return (0);
}
