/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:06:45 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/28 14:21:42 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			inst_zjmp(int pc, t_lstprocess *process)
{
	int	pc_jump;

	pc_jump = (short)(g_memory[(pc + 1) % MEM_SIZE] << 8
		| g_memory[(pc + 2) % MEM_SIZE]);
	pc_jump = (process->pc + (short)pc_jump % IDX_MOD) % MEM_SIZE;
	pc_jump += (pc_jump < 0) * MEM_SIZE;
	if (process->carry == 1)
		process->pc = pc_jump % MEM_SIZE;
	else
		process->pc = (process->pc + 3) % MEM_SIZE;
	return (0);
}
