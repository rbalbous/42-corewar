/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 15:08:11 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/29 18:15:20 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			dump_memory(void)
{
	int		i;
	int		row;

	row = 0;
	while (row < 64)
	{
		ft_printf("0x%.4x : ", row * 64);
		i = -1;
		while (++i < 64)
			ft_printf("%.2hhx ", g_memory[row * 64 + i]);
		ft_printf("\n");
		row++;
	}
	if (!(g_flags & 0x1))
	{
		free(g_memory);
		g_memory = NULL;
	}
	return (0);
}

void		clean_quit(t_window *win)
{
	SDL_FreeSurface(win->surface);
	SDL_DestroyWindow(win->window);
	SDL_Quit();
	TTF_CloseFont(win->ttf_player);
	TTF_CloseFont(win->ttf_text);
	TTF_Quit();
	free_all();
	exit(0);
}

void		free_all(void)
{
	t_player	*tmp;

	free(g_memory);
	while (g_players != NULL)
	{
		free(g_players->name);
		free(g_players->comment);
		free(g_players->memory);
		tmp = g_players;
		g_players = g_players->next;
		free(tmp);
	}
}
