/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 18:46:18 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/29 16:14:55 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			get_ind(char *line, int *line_index)
{
	int		ret;

	ret = 0;
	if (line[*line_index] == LABEL_CHAR)
	{
		if ((ret = is_label(line + *line_index + 1, SEPARATOR_CHAR)) == -1)
			return (-1);
		*line_index += ret;
	}
	if (line[*line_index] == '-')
		(*line_index)++;
	while (line[*line_index] && line[*line_index] != SEPARATOR_CHAR)
	{
		if (ft_ispace(line[*line_index])
		&& (ret = skip_end_comment(line, line_index) <= 0))
			return (ret);
		if (!(line[*line_index] >= '0' && line[*line_index] <= '9'))
			return (-1);
		(*line_index)++;
	}
	return (0);
}

int			get_dir(char *line, int *line_index)
{
	int		i;
	int		ret;

	i = 0;
	(*line_index)++;
	if (line[*line_index] == LABEL_CHAR)
	{
		if ((ret = is_label(line + *line_index + 1, SEPARATOR_CHAR)) == -1)
			return (-1);
		*line_index += ret;
	}
	else
	{
		(*line_index) += (line[*line_index] == '-');
		while (line[*line_index] && line[*line_index] != SEPARATOR_CHAR)
		{
			if (ft_ispace(line[*line_index])
			&& (ret = skip_end_comment(line, line_index) <= 0))
				return (ret);
			if (!(line[*line_index] >= '0' && line[*line_index] <= '9'))
				return (-1);
			(*line_index)++;
		}
	}
	return (0);
}

int			get_register(char *line, int *line_index)
{
	if (!(line[*line_index] >= '0' && line[*line_index] <= '9'))
		return (-1);
	if (line[*line_index] != '1' && line[(*line_index) + 1] != SEPARATOR_CHAR)
	{
		(*line_index)++;
		if (skip_end_comment(line, line_index) < 0)
			return (-1);
		return (0);
	}
	(*line_index)++;
	if (!line[*line_index])
		return (0);
	if ((!(line[*line_index] < '7' && line[*line_index] >= '0'))
	&& !ft_ispace(line[*line_index]) && line[*line_index] != SEPARATOR_CHAR)
		return (-1);
	if (line[*line_index] != SEPARATOR_CHAR)
		(*line_index)++;
	if (skip_end_comment(line, line_index) < 0)
		return (-1);
	return (0);
}

int			check_all(char *line, int *line_index, int inst, int i)
{
	if (line[*line_index] == DIRECT_CHAR)
	{
		if (!(g_op[inst].args[i] & T_DIR)
		|| get_dir(line, line_index) == -1)
			return (print_error(SYNTAX, g_nb_line, line + *line_index));
	}
	else if (line[*line_index] == 'r')
	{
		(*line_index)++;
		if (!(g_op[inst].args[i] & T_REG)
		|| get_register(line, line_index) == -1)
			return (print_error(SYNTAX, g_nb_line, line + *line_index - 1));
	}
	else if (!(g_op[inst].args[i] & T_IND) || get_ind(line, line_index) == -1)
		return (print_error(SYNTAX, g_nb_line, line + *line_index));
	return (0);
}

int			check_valid(char *line, int inst)
{
	int		i;
	int		line_index;

	i = 0;
	line_index = 0;
	while (line[line_index])
	{
		while (line[line_index] && (ft_ispace(line[line_index])
		|| line[line_index] == SEPARATOR_CHAR))
			line_index++;
		if (check_all(line, &line_index, inst, i))
			return (-1);
		if (line[line_index] != 0)
			line_index++;
		i++;
	}
	if (i < g_op[inst].nb_args)
		return (print_error("error: not enough args [l.%d]", g_nb_line));
	if (i > g_op[inst].nb_args)
		return (print_error("error: too many args [l.%d]", g_nb_line));
	if (skip_comment(line + line_index))
		return (1);
	return (print_error("error: bad character after instruction [l.%d] : {%s}"
		, g_nb_line, line + line_index));
}
