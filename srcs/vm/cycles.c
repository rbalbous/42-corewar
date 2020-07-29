/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 15:44:44 by afoures           #+#    #+#             */
/*   Updated: 2018/07/28 15:43:13 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_inst(int (*inst[17])())
{
	inst[1] = inst_live;
	inst[2] = inst_ld;
	inst[3] = inst_st;
	inst[4] = inst_add;
	inst[5] = inst_sub;
	inst[6] = inst_and;
	inst[7] = inst_or;
	inst[8] = inst_xor;
	inst[9] = inst_zjmp;
	inst[10] = inst_ldi;
	inst[11] = inst_sti;
	inst[12] = inst_fork;
	inst[13] = inst_lld;
	inst[14] = inst_lldi;
	inst[15] = inst_lfork;
	inst[16] = inst_aff;
}

void	reset_live(void)
{
	t_player	*tmp;

	tmp = g_players;
	while (tmp != NULL)
	{
		tmp->live = 0;
		tmp = tmp->next;
	}
	g_nb_live = 0;
}

int		check_turn(t_window *win, t_player *last_player_alive)
{
	static int		last_checked = 0;
	static int		nb_checks = 0;
	char			str[512];

	if (g_cycle - last_checked == g_cycle_to_die || g_cycle_to_die <= 0)
	{
		kill_process(win);
		last_checked = g_cycle;
		g_cycle_to_die -= CYCLE_DELTA * (g_nb_live >= NBR_LIVE
			|| nb_checks >= MAX_CHECKS);
		nb_checks -= nb_checks * (g_nb_live >= NBR_LIVE
			|| nb_checks >= MAX_CHECKS) - 1;
		reset_live();
		if (g_nb_process == 0)
		{
			ft_sprintf(str, "** [%d] Player %d \"%s\" won ! **\n", g_cycle
			, last_player_alive->number, last_player_alive->name);
			if (g_flags & 0x1)
				update_msg(win, str, get_color(win, last_player_alive->number));
			else
				return (ft_printf("%s", str));
		}
	}
	return (0);
}

int		check_dump(t_window *win, int *pause)
{
	char			str[512];

	if (g_dump > 0 && g_cycle >= g_dump)
	{
		ft_sprintf(str, "** [%d] Memory dumped **\n", g_cycle - 1);
		if (g_flags & 0x1)
			update_msg(win, str, RED_MSG);
		else
			ft_printf("%s", str);
		dump_memory();
		g_nb_process = (g_flags & 0x1) ? g_nb_process : 0;
		g_dump = 0;
		*pause = 0x2;
		if (!(g_flags & 0x1))
			return (1);
	}
	return (0);
}

int		loop(t_window *win, int nb_players)
{
	t_player	*last_player_alive;
	static int	(*inst[17])() = {NULL};
	int			pause;

	init_inst(inst);
	last_player_alive = g_players;
	pause = (g_flags & 0x1) * 2;
	while (1)
	{
		if (g_flags & 0x1)
			get_event(win, &pause);
		if (((pause & 0x1) || !pause) && g_nb_process > 0 && g_memory)
		{
			compute_process(inst, win, &last_player_alive);
			if (check_turn(win, last_player_alive) | check_dump(win, &pause))
				break ;
			if (g_flags & 0x1)
				update_visu(win, nb_players);
			g_cycle++;
			pause = (pause & 0x2);
		}
	}
	return (0);
}
