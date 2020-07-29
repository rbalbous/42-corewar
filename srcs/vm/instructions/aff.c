/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:02:03 by rbalbous          #+#    #+#             */
/*   Updated: 2018/07/28 15:43:21 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			inst_aff(int pc, t_lstprocess *process, t_window *win)
{
	int		ret;
	char	str[256];

	if ((ret = check_oc(pc, process->opcode
		, g_memory[(process->pc + 1) % MEM_SIZE])))
		return ((process->pc = (process->pc + ret) % MEM_SIZE));
	if (!(g_flags & 0x2))
	{
		ft_bzero(str, 256);
		ft_sprintf(str, "** [%d] Aff: %c **", g_cycle, process->reg[g_memory[(pc
			+ 2) % MEM_SIZE] - 1]);
		if (g_flags & 0x1)
			update_msg(win, str, WHITE);
		else
			ft_printf("%s\n", str);
	}
	process->pc = (process->pc + 3) % MEM_SIZE;
	return (0);
}
