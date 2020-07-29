/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:20:19 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/29 18:02:20 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_infos(int ac, char *av[], int i, int nb_champs)
{
	int		ret;
	int		nb;
	int		curr_nb;

	nb = 0;
	curr_nb = -1;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if ((ret = get_args(av[i])) == -1)
				return (-1);
			else if ((ret == 1 && (i > ac - 2 || g_dump != 0
			|| get_dump_nb(av[++i]) == -1)) || (ret == 2 && (i > ac - 3
			|| nb != 0 || get_number(av[++i], &nb) == -1)))
				print_error("error: parse error");
			continue ;
		}
		if (!(nb_champs = check_file_name(av[i], nb_champs, nb, curr_nb--)))
			return (-1);
		nb = 0;
	}
	if (nb != 0)
		print_error("error: file error");
	return (nb_champs);
}

int		main(int ac, char *av[])
{
	int			nb_champs;
	t_window	win;

	if (ac < 2)
		print_usage();
	if ((nb_champs = check_infos(ac, av, 0, 0)) == -1)
		return (-1);
	init_memory(&win, nb_champs);
	if (g_flags & 0x1)
		init_visu(&win, nb_champs);
	loop(&win, nb_champs);
	free_all();
	return (0);
}
