/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 05:17:23 by afoures           #+#    #+#             */
/*   Updated: 2018/06/30 15:37:52 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				g_cycle = 0;
t_player		*g_players = NULL;
unsigned char	*g_memory = NULL;
t_lstprocess	*g_process = NULL;
unsigned int	g_nb_process = 0;
int				g_cycle_to_die = CYCLE_TO_DIE;
unsigned int	g_nb_live = 0;
int				g_dump = 0;
int				g_flags = 0;
