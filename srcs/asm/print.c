/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:51:06 by afoures           #+#    #+#             */
/*   Updated: 2018/06/29 21:43:19 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_custom(char *s, ...)
{
	va_list	ap;

	va_start(ap, s);
	ft_vprintf(s, ap);
	ft_printf("\n");
	va_end(ap);
}

int		print_error_free(char **line)
{
	print_error("error: header [l.%d] : {%s}", g_nb_line, *line);
	free(*line);
	return (-1);
}

int		print_error(char *error, ...)
{
	va_list	ap;

	va_start(ap, error);
	ft_dprintf(2, RED);
	ft_vdprintf(2, error, ap);
	ft_dprintf(2, NOC);
	ft_dprintf(2, "\n");
	va_end(ap);
	return (-1);
}

void	print_usage(void)
{
	ft_dprintf(2, "usage:	./asm [-d] file.s\n");
	exit(0);
}
