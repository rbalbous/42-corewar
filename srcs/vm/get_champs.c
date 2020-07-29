/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 10:39:59 by jechoque          #+#    #+#             */
/*   Updated: 2018/06/29 21:20:10 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_file_name(char *champ_name, int nb_champs, int nb, int curr_nb)
{
	int		len;

	len = ft_strlen(champ_name);
	nb_champs++;
	if (ft_strncmp(&champ_name[len - 4], ".cor", 4) != 0)
		return (print_error("error: file extension (not a .cor)"));
	if (nb_champs > MAX_PLAYERS)
		return (print_error("error: too many champions (4 max)"));
	if (nb == 0)
		nb = curr_nb;
	if (read_file(champ_name, nb) == -1)
		return (-1);
	return (nb_champs);
}

int		get_args(char *arg)
{
	if (ft_strcmp(arg + 1, "n") == 0)
		return (2);
	else if (ft_strcmp(arg + 1, "v") == 0)
	{
		g_flags |= 1;
		return (3);
	}
	else if (ft_strcmp(arg + 1, "q") == 0)
	{
		g_flags |= 2;
		return (3);
	}
	else if (ft_strcmp(arg + 1, "k") == 0)
	{
		g_flags |= 4;
		return (3);
	}
	else if (ft_strcmp(arg + 1, "dump") == 0)
		return (1);
	return (print_error("error: argument not recognized"));
}

int		get_dump_nb(char *arg)
{
	int		index;

	index = 0;
	while (arg[index] != 0)
	{
		if (!(arg[index] >= '0' && arg[index] <= '9'))
			return (-1);
		index++;
	}
	g_dump = ft_atoi(arg);
	return (0);
}

int		get_number(char *arg, int *number)
{
	int		index;

	index = 0;
	if (arg[index] == '-')
		index++;
	while (arg[index] != 0)
	{
		if (!(arg[index] >= '0' && arg[index] <= '9'))
			return (-1);
		index++;
	}
	*number = ft_atoi(arg);
	if (*number == 0)
		return (print_error("error: player number cannot be 0"));
	return (0);
}
