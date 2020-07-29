/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 18:36:48 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/29 18:55:13 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	g_max = 1;

int		create_tmp(t_lsttmp **first, char *line, t_addresses address, int c)
{
	t_lsttmp	*new;
	int			i;
	int			j;
	int			len;

	i = 0;
	if (!(new = malloc(sizeof(t_lsttmp) + 1)))
		return (-1);
	len = ft_strlen(LABEL_CHARS);
	while (line[i] && line[i] != c && (j = -1))
	{
		while (LABEL_CHARS[++j])
			if (line[i] == LABEL_CHARS[j])
				break ;
		if (j > len - 1)
			break ;
		i++;
	}
	new->next = *first;
	new->name = ft_strsub(line, 0, i);
	new->address = address;
	*first = new;
	if (i == 0 || !new->name)
		return (print_error("error: empty label"));
	return (0);
}

int		is_instruction(char *line)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (line[i] && ft_ispace(line[i]))
		i++;
	j = 16;
	if (line[i] == 0)
		return (0);
	while (j > 0)
	{
		len = ft_strlen(g_op[j].instruction);
		if (ft_strncmp(line + i, g_op[j].instruction, len) == 0)
		{
			if (check_valid(line + i + len, j) == -1)
				return (-1);
			break ;
		}
		j--;
	}
	return (j);
}

int		create_inst(t_lsttmp **first, char *line, int inst)
{
	char	data[16];
	int		size;
	int		ret;

	while (*line && ft_ispace(*line))
		line++;
	line += ft_strlen(g_op[inst].instruction);
	if (g_file->champ_size > CHAMP_MAX_SIZE * g_max - 50)
	{
		g_max++;
		if (!(g_file->bytecode = realloc(g_file->bytecode, sizeof(unsigned char)
		* (HEADER_SIZE + CHAMP_MAX_SIZE * g_max + 17))))
			return (print_error("error: realloc failed (bytecode)"));
	}
	size = 1 + g_op[inst].octal;
	data[0] = inst;
	ret = add_args(line, data, first, 0);
	if (ret < 0)
		return (print_error("error: bad instruction's argument"));
	size = ret;
	ft_memcpy(g_file->bytecode + g_file->champ_size + PROG_NAME_LENGTH
				+ COMMENT_LENGTH + 16, data, size);
	g_file->champ_size += size;
	return (0);
}

int		read_label_inst_bis(char *line, t_lsttmp **instructions, int sk_lbl)
{
	int		inst_index;

	if ((inst_index = is_instruction(line + sk_lbl)) > 0)
	{
		if (create_inst(instructions, line + sk_lbl, inst_index) == -1)
			return (-1);
	}
	else if (!(empty_line(line + sk_lbl) || skip_comment(line + sk_lbl)))
	{
		if (inst_index != -1)
			print_error("error: invalid line [l.%d]: {%s}", g_nb_line
				, line + sk_lbl);
		free(line);
		return (-1);
	}
	return (0);
}

int		read_label_inst(int fd, t_lsttmp **instructions,
						t_lstlabel **lbls)
{
	char	*line;
	int		ret;
	int		sk_lbl;
	int		ret_lbl;

	g_max = 1;
	while ((ret = get_next_line_asm(fd, &line)) > 0 && ++g_nb_line)
	{
		sk_lbl = 0;
		while ((ret_lbl = is_label(line + sk_lbl, LABEL_CHAR)))
		{
			sk_lbl += ret_lbl;
			if (create_label(lbls, line, g_file->champ_size, LABEL_CHAR) == -1)
				return (-1);
		}
		if (read_label_inst_bis(line, instructions, sk_lbl) < 0)
			return (-1);
		free(line);
	}
	if (ret < 0)
		return (print_error("error: instructions' read"));
	return (compute_label(instructions, lbls));
}
