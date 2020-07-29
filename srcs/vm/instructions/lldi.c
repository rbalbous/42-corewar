/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:06:25 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/28 14:15:25 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_all_arg_lldi(int *pc, t_lstprocess *process, int decal)
{
	int		arg;
	int		value;

	arg = 0;
	value = 0;
	if (((g_memory[(process->pc + 1) % MEM_SIZE] >> decal) & 0x3) == 3)
	{
		value = g_memory[(*pc + 2) % MEM_SIZE] << 8
			| g_memory[(*pc + 3) % MEM_SIZE];
		value = (process->pc + (short)value) % MEM_SIZE;
		arg = get_int(value + MEM_SIZE * (value < 0));
		*pc = (*pc + 1) % MEM_SIZE;
	}
	else if (((g_memory[(process->pc + 1) % MEM_SIZE] >> decal) & 0x3) == 2)
	{
		arg = (short)(g_memory[(*pc + 2) % MEM_SIZE] << 8 |
		g_memory[(*pc + 3) % MEM_SIZE]);
		*pc = (*pc + 1) % MEM_SIZE;
	}
	else
		arg = process->reg[(int)g_memory[(*pc + 2) % MEM_SIZE] - 1];
	*pc = (*pc + 1) % MEM_SIZE;
	return (arg);
}

int			inst_lldi(int pc, t_lstprocess *process)
{
	int	adress;
	int	value;
	int	reg;

	if ((reg = check_oc(pc, process->opcode
		, g_memory[(process->pc + 1) % MEM_SIZE])))
		return ((process->pc = (process->pc + reg) % MEM_SIZE));
	adress = get_all_arg_lldi(&pc, process, 6);
	reg = 3;
	if (((g_memory[(process->pc + 1) % MEM_SIZE] >> 4) & 0x3) == 2 && reg++)
		adress += (short)(g_memory[(pc + 2) % MEM_SIZE] << 8 |
			g_memory[(pc + 3) % MEM_SIZE]);
	else
		adress += process->reg[(int)g_memory[(pc + 2) % MEM_SIZE] - 1];
	adress = (process->pc + adress) % MEM_SIZE;
	adress += (adress < 0) * MEM_SIZE;
	value = g_memory[(adress) % MEM_SIZE] << 24
		| g_memory[(adress + 1) % MEM_SIZE] << 16
		| g_memory[(adress + 2) % MEM_SIZE] << 8
		| g_memory[(adress + 3) % MEM_SIZE];
	process->reg[(int)g_memory[(pc + reg) % MEM_SIZE] - 1] = value;
	process->carry = !value;
	process->pc = (process->pc + reg + pc - process->pc + 1) % MEM_SIZE;
	return (0);
}
