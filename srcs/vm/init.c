/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 13:37:44 by afoures           #+#    #+#             */
/*   Updated: 2018/06/27 21:20:21 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	draw_memory(t_window *win)
{
	static t_old	old;
	static int		first = 1;
	static int		all_color[4] = {P1, P2, P3, P4};
	Uint32			color;
	int				i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		color = WHITE;
		if (win->game_color[i] > 0)
			color = all_color[(int)win->game_color[i] - 1];
		if (first || old.mem[i] != g_memory[i]
		|| old.process[i] != win->game_process[i]
		|| old.color[i] != win->game_color[i])
			put_byte(win, (t_point){i % 64, i / 64}, color
				, win->game_process[i]);
	}
	first = 0;
	ft_memcpy(old.mem, g_memory, MEM_SIZE);
	ft_memcpy(old.color, win->game_color, MEM_SIZE);
	ft_memcpy(old.process, win->game_process, MEM_SIZE);
}

void	put_players(t_window *win, int nb_players, int colors[4])
{
	int			line_width;
	int			line_height;
	char		str[256];
	t_player	*player;
	SDL_Surface	*tmp;

	player = g_players;
	while (player != NULL)
	{
		ft_bzero(str, 256);
		ft_sprintf(str, "Player %d : \"%s\"", player->number, player->name);
		if (TTF_SizeText(win->ttf_player, str, &line_width, &line_height))
			print_error("error: bad player text");
		tmp = TTF_RenderText_Blended(win->ttf_player, str,
									argb_to_sdl(colors[nb_players - 1]));
		put_text(win->surface, tmp, 1088 + 125,
				50 + (nb_players - 1) * 75 + line_height / 2);
		SDL_FreeSurface(tmp);
		player = player->next;
		nb_players--;
	}
}

void	init_window(t_window *win, int st)
{
	if (!(win->window = SDL_CreateWindow("Virtual Corewar Arena",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win->width, win->height, SDL_WINDOW_SHOWN)))
		print_error("error: SDL CreateWindow");
	win->surface = SDL_GetWindowSurface(win->window);
	SDL_SetSurfaceAlphaMod(win->surface, 255);
	SDL_SetSurfaceBlendMode(win->surface, SDL_BLENDMODE_NONE);
	SDL_FillRect(win->surface, NULL, GREY);
	put_line(win->surface, (t_point){50, 50}, (t_point){50, 1138}, WHITE);
	put_line(win->surface, (t_point){1138, 50}, (t_point){50, 50}, WHITE);
	put_line(win->surface, (t_point){1138, 50}, (t_point){1138, 1138}, WHITE);
	put_line(win->surface, (t_point){50, 1138}, (t_point){1138, 1138}, WHITE);
	put_line(win->surface, (t_point){1188, st}, (t_point){1638, st}, WHITE);
	put_line(win->surface, (t_point){1188, st}, (t_point){1188, 1138}, WHITE);
	put_line(win->surface, (t_point){1188, 1138}, (t_point){1638, 1138}, WHITE);
	put_line(win->surface, (t_point){1638, st}, (t_point){1638, 1138}, WHITE);
	win->text_height = 1088 - st + 50;
	win->text_start = st;
}

void	init_font(t_window *win)
{
	if (TTF_Init() < 0)
		print_error("error: SDL Init");
	win->ttf_player = NULL;
	win->ttf_player = TTF_OpenFont("Raleway-Regular.ttf", 20);
	win->ttf_text = NULL;
	win->ttf_text = TTF_OpenFont("Raleway-Regular.ttf", 12);
	if (win->ttf_player == NULL || win->ttf_text == NULL)
		print_error("error: loading font");
}

int		init_visu(t_window *win, int nb_players)
{
	win->width = 1688;
	win->height = 1188;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		print_error("error: SDL Init");
	SDL_GL_SetSwapInterval(1);
	init_window(win, nb_players * 75 + 100);
	init_font(win);
	put_players(win, nb_players, (int[4]){P1, P2, P3, P4});
	update_visu(win, nb_players);
	return (0);
}
