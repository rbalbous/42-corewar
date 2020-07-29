/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:06:19 by rbalbous          #+#    #+#             */
/*   Updated: 2018/07/28 15:43:21 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			inst_live(int pc, t_lstprocess *process, t_window *win
			, t_player **last_player_alive)
{
	t_player	*player;
	char		str[512];

	process->live++;
	g_nb_live++;
	if ((player = check_number((g_memory[(pc + 1) % MEM_SIZE] << 24
		| g_memory[(pc + 2) % MEM_SIZE] << 16
		| g_memory[(pc + 3) % MEM_SIZE] << 8
		| g_memory[(pc + 4) % MEM_SIZE]))) == NULL)
		return ((process->pc = (process->pc + 5) % MEM_SIZE));
	*last_player_alive = player;
	player->live++;
	player->last_live = g_cycle;
	process->pc = (process->pc + 5) % MEM_SIZE;
	if (!(g_flags & 0x2))
	{
		ft_bzero(str, 512);
		ft_sprintf(str, "** [%d] A process shows that player %d \"%s\"\
		is alive and well **\n", g_cycle, player->number, player->name);
		if (g_flags & 0x1)
			update_msg(win, str, WHITE);
		else
			ft_printf("%s", str);
	}
	return (1);
}
