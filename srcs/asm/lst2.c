/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 15:33:48 by afoures           #+#    #+#             */
/*   Updated: 2018/06/29 16:05:23 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		add_reg(char **line, char *data, t_args *args)
{
	int		type;

	(*line)++;
	data[args->size++] = ft_atoi(*line);
	type = REG_CODE << args->skip;
	args->skip -= 2;
	while (**line && **line != SEPARATOR_CHAR)
		(*line)++;
	return (type);
}

int		add_dir(char **line, char data[16], t_args *args)
{
	int		tmp;
	int		nb;
	int		type;

	type = DIR_CODE << args->skip;
	args->skip -= 2;
	if (g_op[(int)data[0]].size)
		nb = (short)ft_atoi(*line);
	else
		nb = ft_atoi(*line);
	tmp = 4 - 2 * g_op[(int)data[0]].size;
	while (tmp)
	{
		data[args->size - 1 + tmp--] = nb & 0xFF;
		nb = nb >> 8;
	}
	args->size += 4 - 2 * g_op[(int)data[0]].size;
	while (**line && **line != SEPARATOR_CHAR)
		(*line)++;
	return (type);
}

int		add_ind(char **line, char data[16], t_args *args)
{
	int		type;
	int		tmp;
	int		nb;

	type = IND_CODE << args->skip;
	args->skip -= 2;
	nb = (short)ft_atoi(*line);
	tmp = 2;
	while (tmp)
	{
		data[args->size - 1 + tmp--] = nb & 0xFF;
		nb = nb >> 8;
	}
	args->size += 2;
	while (**line && **line != SEPARATOR_CHAR)
		(*line)++;
	return (type);
}

int		add_label(t_lsttmp **first, t_args *args, int type)
{
	create_tmp(first, args->line + 1, (t_addresses){g_file->champ_size
		, g_file->champ_size + args->size, 4 - 2 * (g_op[args->data].size
		|| type == IND_CODE)}
		, (args->i != g_op[args->data].nb_args - 1) ? SEPARATOR_CHAR : '\0');
	args->size += 4 - 2 * (g_op[args->data].size || type == IND_CODE);
	while (*(args->line) && *(args->line) != SEPARATOR_CHAR)
		args->line++;
	args->line++;
	type = type << args->skip;
	args->skip -= 2;
	return (type);
}

int		add_args(char *line, char *data, t_lsttmp **first, char type)
{
	t_args	args;

	args = (t_args){line, 1 + g_op[(int)data[0]].octal, 6, data[0], -1};
	while (++args.i < g_op[(int)data[0]].nb_args)
	{
		while (*(args.line) && ft_ispace(*(args.line)))
			args.line++;
		if (*(args.line) == 'r')
			type |= add_reg(&(args.line), data, &args);
		else if (*(args.line) == DIRECT_CHAR && ++args.line)
		{
			if (*(args.line) == LABEL_CHAR
				&& (type |= add_label(first, &args, DIR_CODE)))
				continue ;
			type |= add_dir(&(args.line), data, &args);
		}
		else if (*(args.line) == LABEL_CHAR
			&& (type |= add_label(first, &args, IND_CODE)))
			continue ;
		else
			type |= add_ind(&(args.line), data, &args);
		args.line += (*(args.line) != 0);
	}
	data[1] = (g_op[(int)data[0]].octal) ? type : data[1];
	return (args.size);
}
