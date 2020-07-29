/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:29:53 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/28 16:41:07 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		only_space(char *line, char end)
{
	int		line_index;

	line_index = 0;
	while (line[line_index] != end)
	{
		if (ft_ispace(line[line_index]) != 1)
			return (0);
		line_index++;
	}
	return (1);
}

int		skip_end_comment(char *line, int *line_index)
{
	int		ret;

	ret = 0;
	if (ft_ispace(line[*line_index])
		&& (ret = skip_comment(line + *line_index) == 1))
	{
		while (line[*line_index])
			(*line_index)++;
		return (0);
	}
	return (0);
}

int		skip_comment(char *line)
{
	int		line_index;

	line_index = 0;
	while (line[line_index] && line[line_index] != '\n')
	{
		if (line[line_index] == COMMENT_CHAR)
			return (1);
		if (ft_ispace(line[line_index]) != 1)
			return (0);
		line_index++;
	}
	return (1);
}

int		empty_line(char *line)
{
	int		line_index;

	line_index = 0;
	while (line[line_index] && line[line_index] != '\n')
	{
		if (ft_ispace(line[line_index]) != 1)
			return (0);
		line_index++;
	}
	return (1);
}

int		empty_gnl(int fd)
{
	char	*line;

	line = NULL;
	(void)fd;
	get_next_line_asm(-4242, &line);
	return (0);
}
