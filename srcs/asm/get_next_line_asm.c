/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_asm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 20:06:16 by afoures           #+#    #+#             */
/*   Updated: 2018/06/29 18:08:51 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		last_lines(char **store, char **line, int *len)
{
	if (*len)
	{
		if ((*line = ft_strsub(*store, 0, *len)) == 0)
			return (-1);
		*len = 0;
		return (1);
	}
	ft_strdel(store);
	return (0);
}

static int		getendline(char *store, char **line, char *tmp, int *len)
{
	int		tmp_len;

	tmp_len = 0;
	if ((*line = ft_strisub(store, 0, tmp - store, &tmp_len)) == NULL)
		return (-1);
	ft_strcpy(store, tmp + 1);
	*len -= tmp_len + 1;
	return (1);
}

int				reset_buffer(char **store, int *len)
{
	*len = 0;
	free(*store);
	*store = NULL;
	return (0);
}

int				get_next_line_asm(const int fd, char **line)
{
	int			ret;
	static int	len = 0;
	char		buf[BUFF_SIZE + 1];
	static char	*store = NULL;
	char		*tmp;

	if (fd == -4242)
		return (reset_buffer(&store, &len));
	if (BUFF_SIZE <= 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	if (store == NULL)
		if ((store = ft_memalloc(10)) == NULL)
			return (-1);
	if ((tmp = ft_memchr(store, '\n', len)) != NULL)
		return (getendline(store, line, tmp, &len));
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0;
		if ((store = ft_strljoinfree(store, buf, len, ret)) == NULL)
			return (-1);
		len += ret;
		if ((tmp = ft_memchr(store, '\n', len)) != NULL)
			return (getendline(store, line, tmp, &len));
	}
	return ((ret == -1) * -1 || last_lines(&store, line, &len));
}
