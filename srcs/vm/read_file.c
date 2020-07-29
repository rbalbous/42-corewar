/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:37:42 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/29 18:57:20 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			check_magic_nb(unsigned char *buff)
{
	if (buff[0] != ((COREWAR_EXEC_MAGIC >> 24) & 0xFF)
		|| buff[1] != ((COREWAR_EXEC_MAGIC >> 16) & 0xFF)
		|| buff[2] != ((COREWAR_EXEC_MAGIC >> 8) & 0xFF)
		|| buff[3] != (COREWAR_EXEC_MAGIC & 0xFF))
		print_error("error: file doesn't start with the magic number (%.8p)"
			, COREWAR_EXEC_MAGIC);
	return (0);
}

int			read_file(char *name_file, int number)
{
	int				fd;
	unsigned char	buff[HEADER_SIZE + CHAMP_MAX_SIZE + 1];

	if (check_number(number) != NULL)
		print_error("error: multiple champion with the same number");
	create_player(number);
	if ((fd = open(name_file, O_RDONLY)) < 0)
		print_error("error: open failed");
	if (read(fd, buff, HEADER_SIZE + CHAMP_MAX_SIZE) == -1)
		print_error("error: impossible to read");
	if (check_magic_nb(buff) == -1)
		return (-1);
	if ((g_players->name = ft_strdup((char *)(buff + 4))) == NULL)
		print_error("error: strdup failed (player name)");
	if ((ft_strlen(g_players->name)) > PNL)
		print_error("error: name is too long");
	if ((g_players->size = ((buff[PNL + 8] << 24) | (buff[PNL + 9] << 16)
		| (buff[PNL + 10] << 8) | (buff[PNL + 11]))) > CHAMP_MAX_SIZE)
		print_error("error: champion is too big");
	if ((g_players->comment = ft_strdup((char *)(buff + PNL + 12))) == NULL)
		print_error("error: strdup failed (player comment)");
	if (COMMENT_LENGTH < (ft_strlen(g_players->comment)))
		print_error("error: comment is too long");
	g_players->memory = ft_memacpy(buff + HEADER_SIZE, g_players->size);
	return (0);
}
