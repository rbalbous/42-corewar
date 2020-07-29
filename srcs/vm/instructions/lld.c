/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:06:22 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/19 16:06:50 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			inst_lld(int pc, t_lstprocess *process)
{
	int	value;
	int	reg;

	if ((reg = check_oc(pc, process->opcode
		, g_memory[(process->pc + 1) % MEM_SIZE])))
		return ((process->pc = (process->pc + reg) % MEM_SIZE));
	reg = 6;
	value = 0;
	if (((g_memory[(pc + 1) % MEM_SIZE] >> 6) & 0x3) == 3 && (reg -= 2))
	{
		value = pc + (short)(g_memory[(pc + 2) % MEM_SIZE] << 8
			| g_memory[(pc + 3) % MEM_SIZE]) % MEM_SIZE;
		value = g_memory[(value + (value < 0) * MEM_SIZE) % MEM_SIZE] << 24
			| g_memory[(value + (value < 0) * MEM_SIZE + 1) % MEM_SIZE] << 16
			| g_memory[(value + (value < 0) * MEM_SIZE + 2) % MEM_SIZE] << 8
			| g_memory[(value + (value < 0) * MEM_SIZE + 3) % MEM_SIZE];
	}
	else if (((g_memory[(pc + 1) % MEM_SIZE] >> 6) & 0x3) == 2)
		value = g_memory[(pc + 2) % MEM_SIZE] << 24
			| g_memory[(pc + 3) % MEM_SIZE] << 16
			| g_memory[(pc + 4) % MEM_SIZE] << 8
			| g_memory[(pc + 5) % MEM_SIZE];
	process->reg[g_memory[(pc + reg) % MEM_SIZE] - 1] = value;
	process->carry = !value;
	return ((process->pc = (process->pc + reg + 1) % MEM_SIZE));
}
