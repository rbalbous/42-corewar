/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:06:42 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/19 15:53:40 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			inst_xor(int pc, t_lstprocess *process)
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
	process->reg[(int)g_memory[pc] - 1] = first_arg ^ sec_arg;
	process->carry = ((first_arg ^ sec_arg) == 0);
	process->pc = (pc + 1) % MEM_SIZE;
	return (0);
}
