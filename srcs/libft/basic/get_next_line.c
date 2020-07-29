/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:06:02 by rbalbous          #+#    #+#             */
/*   Updated: 2018/06/28 21:10:10 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_strisub(const char *s, unsigned int start, size_t len
					, int *i)
{
	char	*str;

	if (!s)
		return (NULL);
	if ((str = (char*)malloc(sizeof(char) * (len + 1))) == 0)
		return (NULL);
	while (len-- > 0)
	{
		str[*i] = s[start];
		start++;
		(*i)++;
	}
	str[*i] = 0;
	return (str);
}

char			*ft_strljoinfree(char const *s1, char const *s2, int len_s1
					, int len_s2)
{
	char	*str;
	int		i;

	i = 0;
	if ((str = (char*)malloc(sizeof(str) * (len_s1 + len_s2) + 1)) == 0)
		return (NULL);
	ft_strcpy(str, s1);
	while (len_s2 > i)
	{
		str[len_s1 + i] = s2[i];
		i++;
	}
	str[len_s1 + i] = 0;
	free((void*)s1);
	return (str);
}

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

int				get_next_line(const int fd, char **line)
{
	int			ret;
	static int	len = 0;
	char		buf[BUFF_SIZE + 1];
	static char	*store = NULL;
	char		*tmp;

	if (fd < 0 || fd > OPEN_MAX || BUFF_SIZE <= 0 || !line)
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
		if ((tmp = ft_memchr(store + len - ret, '\n', ret)) != NULL)
			return (getendline(store, line, tmp, &len));
	}
	if (ret == -1)
		return (-1);
	return (last_lines(&store, line, &len));
}
