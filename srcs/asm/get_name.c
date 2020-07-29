/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:15:06 by jechoque          #+#    #+#             */
/*   Updated: 2018/06/28 21:13:09 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		add_champ_name2(char **line, int fd, int line_index)
{
	int		index;

	index = 4;
	while ((*line)[++line_index] != '\"')
	{
		if (index > PROG_NAME_LENGTH + 4)
			return (print_error("error: name too long: (%d/%d)", index, PNL));
		while ((*line)[line_index] == 0)
		{
			free(*line);
			if (get_next_line_asm(fd, line) <= 0)
				return (-1);
			g_nb_line++;
			g_file->bytecode[index] = '\n';
			index++;
			line_index = 0;
		}
		if ((*line)[line_index] == '\"')
			break ;
		g_file->bytecode[index] = (*line)[line_index];
		index++;
	}
	if (!skip_comment((*line) + line_index + 1))
		return (print_error("error: there is some shit behind the name"));
	return (1);
}

int		add_champ_name(char **line, int fd, int name)
{
	int		line_index;
	int		i;

	line_index = -1;
	if (name)
		return (print_error("error: invalid name [l.%d]", g_nb_line));
	i = 0;
	while ((*line)[i] != '.')
		i++;
	while ((*line)[++line_index] != '\"')
	{
		if ((*line)[line_index] == 0
		|| (line_index > 4 + i && ft_ispace((*line)[line_index]) == 0))
		{
			print_error("error: name [l.%d] : {%s}", g_nb_line, *line);
			free(*line);
			return (-1);
		}
	}
	return (add_champ_name2(line, fd, line_index));
}
