/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 20:12:11 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:33:32 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_setsize(t_conversion *a, const char *str, int *i)
{
	a->size = 0;
	while (str[*i] >= '0' && str[*i] <= '9' && str[*i] != '\0')
	{
		a->size *= 10;
		a->size += str[*i] - '0';
		(*i)++;
	}
	(*i)--;
}

int		ft_setn(va_list va, int len)
{
	int	*d;

	d = va_arg(va, int *);
	*d = len;
	return (0);
}

int		ft_setpre(t_conversion *a, va_list va, char *format, int *i)
{
	while (format[*i] != '\0' && (!test(format[*i])))
	{
		if (ft_isflag(format[*i]))
			ft_set(a, va, format, i);
		else
		{
			(*i)--;
			return (0);
		}
		(*i)++;
	}
	(*i)--;
	return (1);
}
