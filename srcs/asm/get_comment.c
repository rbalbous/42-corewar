/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:16:15 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/29 20:40:26 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		add_comment2(char **line, int fd, int line_index)
{
	int		index;

	index = PROG_NAME_LENGTH + 11;
	while ((*line)[++line_index] != '\"' && ++index)
	{
		if (index > CL + PNL + 12
		&& print_error("error: comment too long (%d/%d)", index - PNL - 12, CL))
			return (-1);
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
	}
	if (!skip_comment((*line) + line_index + 1))
		return (print_error("error: there is some shit behind the comment"));
	return (1);
}

int		add_comment(char **line, int fd, int comment)
{
	int		line_index;
	int		i;

	line_index = -1;
	if (comment)
		return (print_error("error: invalid comment [l.%d]", g_nb_line));
	i = 0;
	while ((*line)[i] != '.')
		i++;
	while ((*line)[++line_index] != '\"')
	{
		if ((*line)[line_index] == 0
		|| (line_index > 7 + i && ft_ispace((*line)[line_index]) == 0))
		{
			print_error("error: comment [l.%d] : {%s}", g_nb_line, *line);
			free(*line);
			return (-1);
		}
	}
	return (add_comment2(line, fd, line_index));
}
