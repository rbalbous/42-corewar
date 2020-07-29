/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:27:13 by afoures           #+#    #+#             */
/*   Updated: 2018/06/25 19:20:24 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_index_color(t_window *win, int number)
{
	int				j;

	j = -1;
	while (++j < 4)
		if (win->colors[j] == number)
			break ;
	return (j);
}

Uint32	get_color(t_window *win, int number)
{
	int			index;
	static int	all_color[4] = {P1, P2, P3, P4};

	if ((index = get_index_color(win, number)) < 4)
		return (all_color[index]);
	return (WHITE);
}

void	update_color(t_window *win, int pc, int number)
{
	int		mod;

	if (pc + 4 >= MEM_SIZE)
	{
		mod = pc + 4 - MEM_SIZE;
		ft_memset(win->game_color + pc, get_index_color(win, number) + 1
			, 4 - mod);
		ft_memset(win->game_color, get_index_color(win, number) + 1, mod);
	}
	else
		ft_memset(win->game_color + pc, get_index_color(win, number) + 1, 4);
}
