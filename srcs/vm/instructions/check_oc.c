/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_oc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 21:44:52 by afoures           #+#    #+#             */
/*   Updated: 2018/06/19 15:46:17 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_oc(int pc, int opcode, char octal)
{
	int		i;
	int		shift;
	int		t;
	int		ret;
	int		skip;

	i = -1;
	shift = 8;
	ret = 1;
	skip = 0;
	while (++i < g_op[opcode].nb_args)
	{
		shift -= 2;
		t = (octal >> shift) & 0x3;
		if (t == 1 && (g_memory[(pc + ret + 1) % MEM_SIZE] <= 0
			|| g_memory[(pc + ret + 1) % MEM_SIZE] > 16))
			skip = 1;
		ret += 2 * (t == 3) + (4 - 2 * g_op[opcode].size) * (t == 2) + (t == 1);
		if ((t == 1 && g_op[opcode].args[i] & T_REG) || (t == 2 &&
	g_op[opcode].args[i] & T_DIR) || (t == 3 && g_op[opcode].args[i] & T_IND))
			continue ;
		else
			skip = 1;
	}
	return ((ret + 1) * skip);
}
