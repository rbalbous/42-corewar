/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 17:50:27 by raf               #+#    #+#             */
/*   Updated: 2018/05/03 12:02:59 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n >= 8)
	{
		*((uintmax_t *)dest) = *((uintmax_t *)src);
		dest = (void *)((uintmax_t *)dest + 1);
		src = (void *)((uintmax_t *)src + 1);
		n -= 8;
	}
	while (n-- > 0)
	{
		*((unsigned char *)dest) = *((unsigned char *)src);
		dest = (void *)((unsigned char *)dest + 1);
		src = (void *)((unsigned char *)src + 1);
	}
	return (dest);
}
