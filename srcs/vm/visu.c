/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 13:31:51 by afoures           #+#    #+#             */
/*   Updated: 2018/07/28 15:42:38 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	put_byte(t_window *win, t_point p, Uint32 color, int process)
{
	int			size;
	SDL_Surface	*tmp;
	char		str[10];

	size = 16;
	ft_bzero(str, 10);
	ft_sprintf(str, "%.2x", g_memory[p.x + p.y * 64]);
	tmp = TTF_RenderText_Blended(win->ttf_text, str,
								argb_to_sdl(color));
	SDL_FillRect(win->surface, &((SDL_Rect){51 + p.x * 17, 51 + p.y * 17
								, 15, 15}), process ? L_GREY : GREY);
	put_text(win->surface, tmp, 50 + p.x * 17 + 1,
			50 + p.y * 17 + 1);
	SDL_FreeSurface(tmp);
}

void	aff_help(t_window *win, int *pause)
{
	char	str[256];

	*pause = 0x2;
	ft_sprintf(str, "---------- HELP MENU ----------");
	update_msg(win, str, WHITE);
	ft_sprintf(str, "Space : play/pause the game");
	update_msg(win, str, WHITE);
	ft_sprintf(str, "Right arrow : when paused, move 1 cycle forward");
	update_msg(win, str, WHITE);
	ft_sprintf(str, "D : dump the memory at the actual cycle");
	update_msg(win, str, WHITE);
	ft_sprintf(str, "-----------------------------------");
	update_msg(win, str, WHITE);
	SDL_UpdateWindowSurface(win->window);
}

void	process_event(t_window *win, int *pause)
{
	char	str[256];

	if (win->event.key.keysym.sym == SDLK_SPACE)
	{
		*pause = ((*pause & 0x2) == 0) * 2;
		if (*pause & 0x2)
		{
			ft_sprintf(str, "** [%d] USER PAUSED THE GAME **", g_cycle - 1);
			update_msg(win, str, WHITE);
			SDL_UpdateWindowSurface(win->window);
		}
	}
	if (win->event.key.keysym.sym == SDLK_RIGHT && (*pause & 0x2))
		*pause |= 1;
	if (win->event.key.keysym.sym == SDLK_d)
	{
		ft_sprintf(str, "** [%d] Memory dumped **\n", g_cycle);
		update_msg(win, str, 0xFF0000);
		dump_memory();
		SDL_UpdateWindowSurface(win->window);
	}
	if (win->event.key.keysym.sym == SDLK_h)
		aff_help(win, pause);
}

void	get_event(t_window *win, int *pause)
{
	while (SDL_PollEvent(&win->event))
	{
		if (win->event.type == SDL_QUIT || (win->event.key.type == SDL_KEYDOWN
				&& win->event.key.keysym.sym == SDLK_ESCAPE))
			clean_quit(win);
		if (win->event.key.type == SDL_KEYDOWN)
			process_event(win, pause);
	}
}
