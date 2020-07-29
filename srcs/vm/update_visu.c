/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:10:16 by afoures           #+#    #+#             */
/*   Updated: 2018/07/28 15:40:32 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	update_player_info(t_window *win, int nb_players)
{
	char		str[256];
	SDL_Surface	*tmp;

	ft_sprintf(str, "Cycle : %d", g_cycle);
	tmp = TTF_RenderText_Blended(win->ttf_player, str,
								argb_to_sdl(WHITE));
	SDL_FillRect(win->surface, &((SDL_Rect){1203, 142 + (nb_players - 1) * 75
			, win->width - 1203, tmp->h}), GREY);
	put_text(win->surface, tmp, 1213, 142 + (nb_players - 1) * 75);
	SDL_FreeSurface(tmp);
	ft_sprintf(str, "CTD : %d", g_cycle_to_die);
	tmp = TTF_RenderText_Blended(win->ttf_player, str,
								argb_to_sdl(WHITE));
	SDL_FillRect(win->surface, &((SDL_Rect){1468, 142 + (nb_players - 1) * 75
			, win->width - 1468, tmp->h}), GREY);
	put_text(win->surface, tmp, 1478, 142 + (nb_players - 1) * 75);
	SDL_FreeSurface(tmp);
	ft_sprintf(str, "Processes : %d", g_nb_process);
	tmp = TTF_RenderText_Blended(win->ttf_player, str,
								argb_to_sdl(WHITE));
	SDL_FillRect(win->surface, &((SDL_Rect){1468, 117 + (nb_players - 1) * 75
			, win->width - 1468, tmp->h}), GREY);
	put_text(win->surface, tmp, 1478, 117 + (nb_players - 1) * 75);
	SDL_FreeSurface(tmp);
}

void	update_game_info(t_window *win, int nb_players)
{
	char		str[256];
	t_player	*player;
	SDL_Surface	*tmp;

	player = g_players;
	while (player != NULL)
	{
		ft_sprintf(str, "Live in current periode : %d", player->live);
		tmp = TTF_RenderText_Blended(win->ttf_text, str,
									argb_to_sdl(WHITE));
		SDL_FillRect(win->surface, &((SDL_Rect){1266
			, 85 + (nb_players - 1) * 75, win->width - 1266, tmp->h}), GREY);
		put_text(win->surface, tmp, 1413 - 137, 85 + (nb_players - 1) * 75);
		SDL_FreeSurface(tmp);
		ft_sprintf(str, "Last live : %d", player->last_live);
		tmp = TTF_RenderText_Blended(win->ttf_text, str,
									argb_to_sdl(WHITE));
		SDL_FillRect(win->surface, &((SDL_Rect){1266
			, 100 + (nb_players - 1) * 75, win->width - 1266, tmp->h}), GREY);
		put_text(win->surface, tmp, 1413 - 137, 100 + (nb_players - 1) * 75);
		SDL_FreeSurface(tmp);
		player = player->next;
		nb_players--;
	}
}

char	*get_cuted_str(char *str, int *cursor, int len)
{
	char	*cuted_str;
	int		i;
	int		last_word;

	i = LEN_MAX_MSG - 1;
	last_word = len;
	cuted_str = NULL;
	while (len > LEN_MAX_MSG && i >= 0 && str[i])
	{
		if (ft_ispace(str[i]) || str[i] == '-')
		{
			last_word = i + 1;
			break ;
		}
		i--;
	}
	if (last_word > LEN_MAX_MSG)
		last_word = LEN_MAX_MSG;
	*cursor += last_word;
	cuted_str = ft_memacpy(str, last_word);
	return (cuted_str);
}

void	update_msg(t_window *win, char *str, Uint32 color)
{
	SDL_Surface		*tmp;
	int				len;
	int				cursor;
	char			*cuted_str;

	len = ft_strlen(str);
	cursor = 0;
	while (cursor < len)
	{
		cuted_str = get_cuted_str(str + cursor, &cursor, len - cursor);
		SDL_BlitSurface(win->surface
		, &((SDL_Rect){1200, win->text_start + 23, 426, win->text_height - 1})
		, win->surface
		, &((SDL_Rect){1200, win->text_start + 1, 426, win->text_height - 23}));
		tmp = TTF_RenderText_Blended(win->ttf_text, cuted_str,
									argb_to_sdl(color));
		SDL_FillRect(win->surface, &((SDL_Rect){1200, 1088 + 22
				, 426, 22}), GREY);
		put_text(win->surface, tmp, 1205, 1088 + 22);
		free(cuted_str);
		SDL_FreeSurface(tmp);
	}
}

void	update_visu(t_window *win, int nb_players)
{
	draw_memory(win);
	update_game_info(win, nb_players);
	update_player_info(win, nb_players);
	SDL_UpdateWindowSurface(win->window);
}
