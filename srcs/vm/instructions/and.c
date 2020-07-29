/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:05:38 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/28 14:28:20 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_int(int to_get)
{
	return (g_memory[(to_get) % MEM_SIZE] << 24
	| g_memory[(to_get + 1) % MEM_SIZE] << 16
	| g_memory[(to_get + 2) % MEM_SIZE] << 8
	| g_memory[(to_get + 3) % MEM_SIZE]);
}

int			get_all_arg(int *pc, t_lstprocess *process, int decal)
{
	int		arg;
	int		value;

	arg = 0;
	value = 0;
	if (((g_memory[(process->pc + 1) % MEM_SIZE] >> decal) & 0x3) == 3)
	{
		value = g_memory[(*pc + 2) % MEM_SIZE] << 8
			| g_memory[(*pc + 3) % MEM_SIZE];
		value = (process->pc + (short)value % IDX_MOD) % MEM_SIZE;
		value += (value < 0) * MEM_SIZE;
		arg = get_int(value);
		*pc = (*pc + 1) % MEM_SIZE;
	}
	else if (((g_memory[(process->pc + 1) % MEM_SIZE] >> decal) & 0x3) == 2)
	{
		arg = get_int(*pc + 2);
		*pc = (*pc + 3) % MEM_SIZE;
	}
	else
		arg = process->reg[(int)g_memory[(*pc + 2) % MEM_SIZE] - 1];
	*pc = (*pc + 1) % MEM_SIZE;
	return (arg);
}

int			inst_and(int pc, t_lstprocess *process)
{
	int		first_arg;
	int		sec_arg;
	int		ret;

	if ((ret = check_oc(pc, process->opcode
		, g_memory[(process->pc + 1) % MEM_SIZE])))
		return ((process->pc = (process->pc + ret) % MEM_SIZE));
	first_arg = get_all_arg(&pc, process, 6);
	sec_arg = get_all_arg(&pc, process, 4);
	pc = (pc + 2) % MEM_SIZE;
	process->reg[(int)g_memory[pc] - 1] = first_arg & sec_arg;
	process->carry = ((first_arg & sec_arg) == 0);
	process->pc = (pc + 1) % MEM_SIZE;
	return (0);
}
