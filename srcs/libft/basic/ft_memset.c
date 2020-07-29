/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 19:59:06 by home              #+#    #+#             */
/*   Updated: 2018/05/03 15:47:05 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	uintmax_t		octet;

	octet = c | (c << 8);
	octet |= (octet << 16);
	octet |= (octet << 32);
	while (n >= 8)
	{
		*((uintmax_t *)str) = octet;
		str = (void*)((uintmax_t *)str + 1);
		n -= 8;
	}
	while (n-- > 0)
	{
		*((unsigned char *)str) = c;
		str = (void*)((unsigned char *)str + 1);
	}
	return (str);
}
