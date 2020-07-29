/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:05:57 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/28 14:20:33 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			inst_ld(int pc, t_lstprocess *process)
{
	int	value;
	int	reg;
	int	ret;

	reg = 6;
	value = 0;
	if ((ret = check_oc(pc, process->opcode,
	g_memory[(process->pc + 1) % MEM_SIZE])))
		return ((process->pc = (process->pc + ret) % MEM_SIZE));
	if (((g_memory[(pc + 1) % MEM_SIZE] >> 6) & 0x3) == 3)
	{
		value = g_memory[(pc + 2) % MEM_SIZE] << 8
			| g_memory[(pc + 3) % MEM_SIZE];
		reg = 4;
		value = (pc + (short)value % IDX_MOD) % MEM_SIZE;
		value = get_int(value + MEM_SIZE * (value < 0));
	}
	else if (((g_memory[(pc + 1) % MEM_SIZE] >> 6) & 0x3) == 2)
		value = get_int(pc + 2);
	process->reg[g_memory[(pc + reg) % MEM_SIZE] - 1] = value;
	process->carry = !value;
	process->pc = (process->pc + reg + 1) % MEM_SIZE;
	return (0);
}
