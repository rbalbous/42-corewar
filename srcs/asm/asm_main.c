/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 19:11:20 by jechoque          #+#    #+#             */
/*   Updated: 2018/06/29 18:21:53 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char *av[])
{
	int		i;
	int		dump;

	i = 1;
	dump = 0;
	if (ac < 2)
		print_usage();
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-d") == 0)
			dump = 1;
		i++;
	}
	i = 0;
	while (++i < ac)
	{
		if (ft_strcmp(av[i], "-d") == 0)
			continue ;
		assemble(av[i], dump);
	}
	return (0);
}
