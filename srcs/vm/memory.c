/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 15:37:35 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/19 18:26:34 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		load_players(t_window *win, int nb_players)
{
	int			i;
	t_player	*tmp;

	i = 1;
	tmp = g_players;
	if (!(g_flags & 0x1))
		ft_printf("Starting the game...\n");
	while (i <= nb_players)
	{
		tmp->start = (nb_players - i) * MEM_SIZE / nb_players;
		win->game_process[tmp->start] = 1;
		ft_memcpy(g_memory + tmp->start, tmp->memory, tmp->size);
		ft_memset(win->game_color + tmp->start, nb_players + 1 - i, tmp->size);
		win->colors[nb_players - i] = tmp->number;
		if (!(g_flags & 0x1))
			ft_printf("-> Introducing player %d \"%s\"\n", tmp->number
				, tmp->name);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int		init_memory(t_window *win, int nb_players)
{
	if (!(g_memory = ft_memalloc(sizeof(char) * (MEM_SIZE + 1))))
		return (-1);
	ft_bzero(win->game_color, MEM_SIZE);
	ft_bzero(win->game_process, MEM_SIZE);
	load_players(win, nb_players);
	create_first_process();
	return (0);
}
