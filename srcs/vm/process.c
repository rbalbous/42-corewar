/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 05:27:24 by afoures           #+#    #+#             */
/*   Updated: 2018/07/28 15:43:21 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			print_killed_process(t_window *win, t_lstprocess *process)
{
	char		str[256];

	if (!(g_flags & 0x2) && g_flags & 0x4)
	{
		ft_sprintf(str, "** [%d] Process %d was killed (CTD %d) **", g_cycle
			, process->id, g_cycle_to_die);
		if (g_flags & 0x1)
			update_msg(win, str, WHITE);
		else
			ft_printf("%s\n", str);
	}
}

void			kill_process(t_window *win)
{
	t_lstprocess	*process;
	t_lstprocess	*to_del;
	t_lstprocess	*last;

	process = g_process;
	last = NULL;
	while (process != NULL)
	{
		if (process->live == 0 && !(win->game_process[process->pc] = 0))
		{
			print_killed_process(win, process);
			g_nb_process--;
			to_del = process;
			if (last != NULL)
				last->next = process->next;
			else
				g_process = process->next;
			process = process->next;
			free(to_del);
		}
		else if (!(process->live = 0)
			&& (last = process))
			process = process->next;
	}
}

void			compute_process(int (*inst[17])(), t_window *win
	, t_player **last_player_alive)
{
	t_lstprocess	*tmp;

	tmp = g_process;
	while (tmp != NULL)
	{
		win->game_process[tmp->pc] = 0;
		if (tmp->opcode < 1 || tmp->opcode > 16)
			tmp->pc = (tmp->pc + 1) % MEM_SIZE;
		else if ((g_cycle
			- tmp->last_cycle) == g_op[(int)tmp->opcode].nb_cycles)
			inst[(int)tmp->opcode](tmp->pc, tmp, win, last_player_alive);
		tmp = tmp->next;
	}
	tmp = g_process;
	while (tmp != NULL)
	{
		win->game_process[tmp->pc] = 1;
		if (tmp->opcode < 1 || tmp->opcode > 16
		|| (g_cycle - tmp->last_cycle) == g_op[(int)tmp->opcode].nb_cycles)
		{
			tmp->opcode = g_memory[tmp->pc];
			tmp->last_cycle = g_cycle;
		}
		tmp = tmp->next;
	}
}

t_lstprocess	*create_process(int reg[REG_NUMBER], int carry, int pc
	, int player_number)
{
	t_lstprocess	*new;
	int				i;
	static int		id = 0;

	id++;
	if (!(new = ft_memalloc(sizeof(t_lstprocess) + 1)))
		return (NULL);
	new->next = g_process;
	new->pc = pc;
	new->carry = carry;
	new->id = id;
	new->player_number = player_number;
	i = -1;
	while (++i < REG_NUMBER)
		new->reg[i] = reg[i];
	new->opcode = g_memory[new->pc];
	g_process = new;
	g_nb_process++;
	return (g_process);
}

int				create_first_process(void)
{
	t_player		*tmp;
	t_lstprocess	*prev;
	t_lstprocess	*next;
	int				reg[REG_NUMBER];

	tmp = g_players;
	ft_bzero(reg, REG_NUMBER * 4);
	while (tmp != NULL)
	{
		reg[0] = tmp->number;
		create_process(reg, 0, tmp->start, tmp->number);
		tmp = tmp->next;
	}
	prev = NULL;
	while (g_process != NULL)
	{
		next = g_process->next;
		g_process->next = prev;
		prev = g_process;
		if (next == NULL)
			break ;
		g_process = next;
	}
	return (0);
}
