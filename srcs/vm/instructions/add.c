/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:02:00 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/13 17:51:14 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			inst_add(int pc, t_lstprocess *process)
{
	int	sum;
	int	ret;

	sum = 0;
	if ((ret = check_oc(pc, process->opcode
		, g_memory[(process->pc + 1) % MEM_SIZE])))
		return ((process->pc = (process->pc + ret) % MEM_SIZE));
	sum += process->reg[(int)g_memory[(pc + 2) % MEM_SIZE] - 1];
	sum += process->reg[(int)g_memory[(pc + 3) % MEM_SIZE] - 1];
	process->reg[(int)g_memory[(pc + 4) % MEM_SIZE] - 1] = sum;
	process->carry = (sum == 0);
	process->pc = (process->pc + 5) % MEM_SIZE;
	return (0);
}
