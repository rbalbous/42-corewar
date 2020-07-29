/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:42:24 by rbalbous          #+#    #+#             */
/*   Updated: 2018/05/03 12:10:08 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_memcpy(void *dest, const void *src, int n)
{
	int		i;

	i = n;
	while (i >= 8)
	{
		*((uintmax_t *)dest) = *((uintmax_t *)src);
		dest = (void *)((uintmax_t *)dest + 1);
		src = (void *)((uintmax_t *)src + 1);
		i -= 8;
	}
	while (i-- > 0)
	{
		*((unsigned char *)dest) = *((unsigned char *)src);
		dest = (void *)((unsigned char *)dest + 1);
		src = (void *)((unsigned char *)src + 1);
	}
	*((char*)dest) = 0;
	return (n);
}
