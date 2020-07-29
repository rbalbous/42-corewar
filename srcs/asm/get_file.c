/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:44:30 by jechoque          #+#    #+#             */
/*   Updated: 2018/06/29 19:09:49 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		read_name_comment(int fd, int name, int comment)
{
	char	*line;
	int		ret;

	while ((!name || !comment) && (ret = get_next_line_asm(fd, &line)) > 0)
	{
		g_nb_line++;
		if (ft_strstr(line, NAME_CMD_STRING)
		&& only_space(line, NAME_CMD_STRING[0]))
		{
			if ((name = add_champ_name(&line, fd, name)) == -1)
				return (-1);
		}
		else if (ft_strstr(line, COMMENT_CMD_STRING)
		&& only_space(line, COMMENT_CMD_STRING[0]))
		{
			if ((comment = add_comment(&line, fd, comment)) == -1)
				return (-1);
		}
		else if (!(empty_line(line) || skip_comment(line)))
			return (print_error_free(&line));
		free(line);
	}
	if (ret == 0)
		return (print_error("error: EOF [l.%d]", g_nb_line));
	return ((ret < 0) ? print_error("error: header's read ") : 0);
}

int		get_file_name(char *file_name)
{
	int		len;

	g_file->bytecode[0] = (COREWAR_EXEC_MAGIC >> 24) & 0xFF;
	g_file->bytecode[1] = (COREWAR_EXEC_MAGIC >> 16) & 0xFF;
	g_file->bytecode[2] = (COREWAR_EXEC_MAGIC >> 8) & 0xFF;
	g_file->bytecode[3] = COREWAR_EXEC_MAGIC & 0xFF;
	len = ft_strlen(file_name);
	if (!(g_file->name = malloc(sizeof(char) * (len + 3))))
		return (print_error("error: malloc failed"));
	if (file_name[len - 2] != '.' || file_name[len - 1] != 's')
		return (print_error("error: not a .s g_file"));
	ft_sprintf(g_file->name, "%.*s.cor", len - 2, file_name);
	return (0);
}
