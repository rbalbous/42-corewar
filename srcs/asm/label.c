/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:50:39 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/28 18:50:08 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			create_label(t_lstlabel **first, char *line, int address, int c)
{
	t_lstlabel	*new;
	int			i;
	int			len;

	i = 0;
	while (line[i] && ft_ispace(line[i]))
		i++;
	if (!(new = malloc(sizeof(t_lstlabel) + 1)))
		return (-1);
	new->next = *first;
	len = ft_strchr(line, c) - line;
	new->name = ft_strsub(line, i, len - i);
	if (existing_label(first, new->name))
	{
		print_error("error: label {%s} already exist", new->name);
		free(new->name);
		free(new);
		return (-1);
	}
	new->address = address;
	*first = new;
	if (len == 0)
		return (print_error("label error : empty label"));
	return (0);
}

int			is_label2(int c, char *line, int i)
{
	if (c != LABEL_CHAR)
	{
		if (skip_comment(line + i))
			while (line[i])
				i++;
		return (i + 1);
	}
	return ((line[i] == c) * (i + 1));
}

int			is_label(char *line, int c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (line[i] && ft_ispace(line[i]))
		i++;
	len = ft_strlen(LABEL_CHARS);
	if (!line[i])
		return (0);
	while (line[i] && line[i] != c && (j = -1))
	{
		while (LABEL_CHARS[++j])
			if (line[i] == LABEL_CHARS[j])
				break ;
		if (c != LABEL_CHAR && ft_ispace(line[i]))
			break ;
		if (j > len - 1)
			return (0);
		i++;
	}
	return (is_label2(c, line, i));
}

int			compute_label(t_lsttmp **instructions, t_lstlabel **labels)
{
	t_lsttmp	*tmp;
	t_lstlabel	*this;
	int			where;
	int			what;
	int			i;

	tmp = *instructions;
	while (tmp != NULL)
	{
		if ((this = existing_label(labels, tmp->name)) == NULL)
			return (print_error("error: label {%s} doesn't exist", tmp->name));
		where = tmp->address.address + PROG_NAME_LENGTH
			+ COMMENT_LENGTH + 16;
		what = this->address - tmp->address.instruction_address;
		i = tmp->address.size - 1;
		while (i >= 0)
		{
			g_file->bytecode[where + i--] = what & 0xFF;
			what = what >> 8;
		}
		tmp = tmp->next;
	}
	return (0);
}

t_lstlabel	*existing_label(t_lstlabel **labels, char *str)
{
	t_lstlabel *tmp;

	tmp = *labels;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
