/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:31:22 by afoures           #+#    #+#             */
/*   Updated: 2018/06/29 21:44:01 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_error(char *error, ...)
{
	va_list	ap;

	va_start(ap, error);
	ft_dprintf(2, RED);
	ft_vdprintf(2, error, ap);
	ft_dprintf(2, NOC);
	ft_dprintf(2, "\n");
	va_end(ap);
	free_all();
	exit(-1);
}

void	print_usage(void)
{
	ft_dprintf(2, "usage: ./corewar [-dump nb -v -q -k] [-n num] champion1 \
	[[-n num] champion2 ...]\n");
	exit(0);
}
