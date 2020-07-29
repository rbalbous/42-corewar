/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:06:34 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/28 14:22:27 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_all_arg_sti(int *pc, t_lstprocess *process, int decal)
{
	int		arg;
	int		value;

	value = 0;
	if (((g_memory[(process->pc + 1) % MEM_SIZE] >> decal) & 0x3) == 3)
	{
		value = g_memory[(*pc + 2) % MEM_SIZE] << 8
			| g_memory[(*pc + 3) % MEM_SIZE];
		value = (process->pc + (short)value % IDX_MOD) % MEM_SIZE;
		arg = get_int(value + (value < 0) * MEM_SIZE);
		*pc = (*pc + 2) % MEM_SIZE;
	}
	else if (((g_memory[(process->pc + 1) % MEM_SIZE] >> decal) & 0x3) == 2)
	{
		arg = (short)(g_memory[(*pc + 2) % MEM_SIZE] << 8 |
		g_memory[(*pc + 3) % MEM_SIZE]);
		*pc = (*pc + 2) % MEM_SIZE;
	}
	else
	{
		arg = process->reg[(int)g_memory[(*pc + 2) % MEM_SIZE] - 1];
		*pc = (*pc + 1) % MEM_SIZE;
	}
	return (arg);
}

void		set_mem(int a, t_lstprocess *process)
{
	int		value;

	value = process->reg[(int)g_memory[(process->pc + 2) % MEM_SIZE] - 1];
	g_memory[a % MEM_SIZE] = (value >> 24) & 0xFF;
	g_memory[(a + 1) % MEM_SIZE] = (value >> 16) & 0xFF;
	g_memory[(a + 2) % MEM_SIZE] = (value >> 8) & 0xFF;
	g_memory[(a + 3) % MEM_SIZE] = value & 0xFF;
}

int			inst_sti(int pc, t_lstprocess *process, t_window *win)
{
	int		a;
	int		ret;

	if ((ret = check_oc(pc, process->opcode,
	g_memory[(process->pc + 1) % MEM_SIZE])))
		return ((process->pc = (process->pc + ret) % MEM_SIZE));
	pc = (pc + 1) % MEM_SIZE;
	a = get_all_arg_sti(&pc, process, 4);
	if (((g_memory[(process->pc + 1) % MEM_SIZE] >> 2) & 0x3) == 2)
	{
		a += (short)(g_memory[(pc + 2) % MEM_SIZE] << 8
			| g_memory[(pc + 3) % MEM_SIZE]);
		pc = (pc + 1) % MEM_SIZE;
	}
	else
		a += process->reg[(int)g_memory[(pc + 2) % MEM_SIZE] - 1];
	a = (process->pc + a % IDX_MOD) % MEM_SIZE;
	a += (a < 0) * MEM_SIZE;
	set_mem(a, process);
	if (g_flags & 0x1)
		update_color(win, a % MEM_SIZE, process->player_number);
	process->pc = (pc + 3) % MEM_SIZE;
	return (0);
}
