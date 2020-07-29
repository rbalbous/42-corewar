/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:06:15 by rbalbous          #+#    #+#             */
/*   Updated: 2018/07/28 15:43:02 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			inst_lfork(int pc, t_lstprocess *process, t_window *win)
{
	int				pc_fork;
	t_lstprocess	*new;
	char			str[256];

	pc_fork = g_memory[(pc + 1) % MEM_SIZE] << 8
		| g_memory[(pc + 2) % MEM_SIZE];
	pc_fork = (process->pc + (short)pc_fork) % MEM_SIZE;
	new = create_process(process->reg, process->carry
		, pc_fork + MEM_SIZE * (pc_fork < 0), process->player_number);
	new->last_cycle = g_cycle;
	new->live = process->live;
	if (!(g_flags & 0x2))
	{
		ft_bzero(str, 256);
		ft_sprintf(str, "** [%d] Process %d created by player %d at index %d **"
			, g_cycle, new->id, new->player_number, new->pc);
		if (g_flags & 0x1)
			update_msg(win, str, WHITE);
		else
			ft_printf("%s\n", str);
	}
	process->pc = (process->pc + 3) % MEM_SIZE;
	return (0);
}
