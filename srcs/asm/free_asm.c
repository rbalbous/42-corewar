/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:27:58 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/28 16:41:01 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		free_all(t_lsttmp **instructions, t_lstlabel **labels)
{
	t_lsttmp	*tmp1;
	t_lstlabel	*tmp2;

	while (*instructions)
	{
		tmp1 = *instructions;
		free((*instructions)->name);
		*instructions = (*instructions)->next;
		free(tmp1);
	}
	while (*labels)
	{
		tmp2 = *labels;
		free((*labels)->name);
		*labels = (*labels)->next;
		free(tmp2);
	}
	free(g_file->name);
	free(g_file->bytecode);
	free(g_file);
	g_file = NULL;
	return (0);
}
