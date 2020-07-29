/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:50:38 by home              #+#    #+#             */
/*   Updated: 2018/05/03 14:31:05 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	while (n >= 8)
	{
		*((uintmax_t *)str) = 0;
		str = (void *)((uintmax_t *)str + 1);
		n -= 8;
	}
	while (n-- > 0)
	{
		*((unsigned char *)str) = 0;
		str = (void *)((unsigned char *)str + 1);
	}
}
