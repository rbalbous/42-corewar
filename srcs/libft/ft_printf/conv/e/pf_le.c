/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_le.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 11:44:53 by rbalbous          #+#    #+#             */
/*   Updated: 2018/01/17 19:03:35 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_tolsc(long double *d)
{
	int		count;

	count = 0;
	if ((intmax_t)(*d) == 0)
	{
		while ((intmax_t)(*d) == 0)
		{
			*d = *d * 10;
			count++;
		}
		count *= -1;
	}
	else
	{
		while ((intmax_t)(*d) < -10 || (intmax_t)(*d) > 10)
		{
			*d /= 10;
			count++;
		}
	}
	return (count);
}

static int	pf_lcreate(t_flags *flags, t_var *var, long double d, int count)
{
	int		start;

	start = var->bufindex;
	pf_ftoa(d, flags, var);
	pf_round(&var->buf[var->bufindex - 1], flags, var);
	addchar('e', var);
	if (count < 0)
	{
		addchar('-', var);
		count *= -1;
	}
	else
		addchar('+', var);
	if (count < 10)
		addchar('0', var);
	addstr(ft_itoa(count), var);
	return (0);
}

static int	initialise(t_flags *flags, t_var *var, long double d)
{
	if (!(d == d))
		return (pf_nan(flags, var));
	if (d == INFINITY || d == -INFINITY)
		return (pf_linfinite(d, flags, var));
	flags->len = 1;
	flags->precision += 7 * (!flags->isp);
	flags->fwidth -= 1 + flags->precision + 5
	+ (d < 0 || flags->space || flags->plus);
	flags->fwidth *= (flags->fwidth > 0);
	return (0);
}

int			pf_le(t_flags *flags, t_var *var, va_list ap)
{
	long double		d;
	int				count;

	d = va_arg(ap, long double);
	count = pf_tolsc(&d);
	initialise(flags, var, d);
	pf_spe_le(flags, var, d, count);
	return (1);
}

int			pf_spe_le(t_flags *flags, t_var *var, long double d, int count)
{
	char		width;

	width = ' ' + 16 * flags->zero;
	if (d < 0)
		addchar('-', var);
	else if (flags->plus || flags->space)
		addchar(flags->plus ? '+' : ' ', var);
	if (!flags->minus)
	{
		flags->fwidth = addmchar(width, var, flags->fwidth);
		pf_lcreate(flags, var, d, count);
	}
	else
	{
		pf_lcreate(flags, var, d, count);
		flags->fwidth = addmchar(width, var, flags->fwidth);
	}
	return (0);
}
