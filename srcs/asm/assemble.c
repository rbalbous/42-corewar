/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:13:17 by jechoque          #+#    #+#             */
/*   Updated: 2018/06/30 15:16:09 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			g_nb_line = 0;
t_file		*g_file = NULL;

int			read_g_file(char *file_name, t_lsttmp **instructions
					, t_lstlabel **labels)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (print_error("error: open failed"));
	if (read_name_comment(fd, 0, 0) == -1)
	{
		empty_gnl(fd);
		close(fd);
		return (-1);
	}
	if (read_label_inst(fd, instructions, labels) == -1)
	{
		empty_gnl(fd);
		close(fd);
		return (-1);
	}
	if ((close(fd)) < 0)
		return (print_error("error: close failed"));
	return (0);
}

int			dump_champ2(int *tarace, int *row)
{
	int		i;

	i = -1;
	if (*tarace <= 1)
		ft_printf("0x%.4x : ", *row * 16);
	while (*tarace != 3 && ++i < 16)
	{
		if (*tarace == 2)
		{
			ft_printf("*\n");
			*tarace = 3;
			break ;
		}
		if (*row * 16 + i >= HEADER_SIZE + g_file->champ_size)
		{
			return ((!i) ? ft_printf("\n") : ft_printf("\n0x%.4x : \n"
			, *row * 16 + i));
		}
		ft_printf("%.2hhx ", g_file->bytecode[*row * 16 + i]);
	}
	if (*tarace <= 1)
		ft_printf("\n");
	*tarace += (*tarace == 1);
	(*row)++;
	return (0);
}

int			dump_champ(void)
{
	int		i;
	int		row;
	int		tarace;

	row = 0;
	tarace = 0;
	ft_printf(GREY);
	while (1)
	{
		i = -1;
		while (++i < 16)
			if (row * 16 + i >= HEADER_SIZE + g_file->champ_size
				|| g_file->bytecode[row * 16 + i] != 0)
				break ;
		if (i == 16 && tarace < 2)
			tarace = 1;
		else if (i != 16)
			tarace = 0;
		if (dump_champ2(&tarace, &row))
			return (ft_printf(NOC));
	}
	return (ft_printf(NOC));
}

int			write_bytecode(int dump)
{
	int			op;
	int			tmp;
	int			i;

	tmp = g_file->champ_size;
	i = PROG_NAME_LENGTH + 11;
	while (tmp)
	{
		g_file->bytecode[i] = tmp & 0xFF;
		tmp = tmp >> 8;
		i--;
	}
	if (!(op = open(g_file->name, O_CREAT | O_RDWR | O_TRUNC, 0666)))
		return (print_error("error: open"));
	if (!(write(op, g_file->bytecode, HEADER_SIZE + g_file->champ_size)))
		return (print_error("error: write (bytecode)"));
	if (dump)
		dump_champ();
	if ((close(op)) < 0)
		return (print_error("error: close"));
	return (0);
}

int			assemble(char *file_name, int dump)
{
	t_lsttmp	*instructions;
	t_lstlabel	*labels;

	instructions = NULL;
	labels = NULL;
	if (!(g_file = ft_memalloc(sizeof(t_file) + 1)))
		return (print_error("error: malloc failed (file)"));
	g_nb_line = 0;
	if (!(g_file->bytecode = ft_memalloc(sizeof(unsigned char) * (HEADER_SIZE
		+ CHAMP_MAX_SIZE + 1))))
	{
		return (print_error("error: malloc failed (bytecode)")
				| free_all(&instructions, &labels));
	}
	print_custom(STARTING_COMPILATION, file_name);
	if (get_file_name(file_name) == -1
		|| read_g_file(file_name, &instructions, &labels) == -1
		|| write_bytecode(dump) == -1)
		return (free_all(&instructions, &labels));
	if (g_file->champ_size > CHAMP_MAX_SIZE)
		print_custom(W_SIZE, g_file->champ_size, CHAMP_MAX_SIZE);
	print_custom(DONE, HEADER_SIZE + g_file->champ_size);
	return (free_all(&instructions, &labels));
}
