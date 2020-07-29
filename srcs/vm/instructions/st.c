/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:06:32 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/28 14:22:22 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		inst_st2(int v, int ppc, t_lstprocess *process, t_window *win)
{
	int		a;

	a = g_memory[(ppc + 3) % MEM_SIZE] << 8
	| g_memory[(ppc + 4) % MEM_SIZE];
	a = (ppc + (short)a % IDX_MOD) % MEM_SIZE;
	g_memory[(a + (a < 0) * MEM_SIZE) % MEM_SIZE] = (v >> 24) & 0xFF;
	g_memory[(a + (a < 0) * MEM_SIZE + 1) % MEM_SIZE] = (v >> 16) & 0xFF;
	g_memory[(a + (a < 0) * MEM_SIZE + 2) % MEM_SIZE] = (v >> 8) & 0xFF;
	g_memory[(a + (a < 0) * MEM_SIZE + 3) % MEM_SIZE] = v & 0xFF;
	if (g_flags & 0x1)
		update_color(win, (a + (a < 0) * MEM_SIZE) % MEM_SIZE,
		process->player_number);
}

int			inst_st(int pc, t_lstprocess *process, t_window *win)
{
	int		v;
	int		ppc;
	int		ret;

	if ((ret = check_oc(pc, process->opcode,
	g_memory[(process->pc + 1) % MEM_SIZE])))
		return ((process->pc = (process->pc + ret) % MEM_SIZE));
	ppc = process->pc;
	v = process->reg[(int)g_memory[(ppc + 2) % MEM_SIZE] - 1];
	if (((g_memory[(ppc + 1) % MEM_SIZE] >> 4) & 0x3) == 3)
	{
		inst_st2(v, ppc, process, win);
		pc = (pc + 1) % MEM_SIZE;
	}
	else
		process->reg[(int)g_memory[(ppc + 3) % MEM_SIZE] - 1] = v;
	process->pc = (pc + 4) % MEM_SIZE;
	return (0);
}
