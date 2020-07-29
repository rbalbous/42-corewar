/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:06:39 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/25 15:18:50 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			inst_sub(int pc, t_lstprocess *process)
{
	int	sum;
	int	ret;

	sum = 0;
	if ((ret = check_oc(pc, process->opcode,
	g_memory[(process->pc + 1) % MEM_SIZE])))
		return ((process->pc = (process->pc + ret) % MEM_SIZE));
	sum += process->reg[(int)g_memory[(pc + 2) % MEM_SIZE] - 1];
	sum -= process->reg[(int)g_memory[(pc + 3) % MEM_SIZE] - 1];
	process->reg[(int)g_memory[(pc + 4) % MEM_SIZE] - 1] = sum;
	process->carry = (sum == 0);
	process->pc = (process->pc + 5) % MEM_SIZE;
	return (0);
}
