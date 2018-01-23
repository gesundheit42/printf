/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 20:06:14 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:06:54 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_set(t_conversion *a, va_list va, char *format, int *i)
{
	if (format[*i] == '#')
		a->diez = 1;
	else if (format[*i] == '+')
		a->plus = 1;
	else if (format[*i] == '-')
		a->minus = 1;
	else if (format[*i] == '0')
		a->zero = 1;
	else if (format[*i] == ' ')
		a->space = 1;
	else if (format[*i] <= '9' && format[*i] > '0')
		ft_setsize(a, format, i);
	else if (format[*i] == '.' && format[*i + 1] != '*')
		ft_setprecision(a, format, i);
	else if (format[*i] == 'h' || format[*i] == 'l' ||
			format[*i] == 'j' || format[*i] == 'z')
		ft_setflag(a, format, i);
	else if (format[*i] == '.' && format[*i + 1] == '*')
		ft_star(a, va, format, i);
	else if (format[*i] == '*')
		ft_star(a, va, format, i);
}

void	ft_setprecision(t_conversion *a, const char *str, int *i)
{
	int d;

	(*i)++;
	d = *i;
	a->precision = 0;
	while (str[*i] >= '0' && str[*i] <= '9' && str[*i] != '\0')
	{
		a->precision *= 10;
		a->precision += str[*i] - '0';
		(*i)++;
	}
	if (*i - d == 0)
		a->precision = -2;
	(*i)--;
}

void	ft_setflag(t_conversion *a, const char *str, int *i)
{
	if (str[(*i) + 1] == str[*i])
	{
		if (str[*i] == 'h')
			a->flag = 'H';
		else
			a->flag = 'L';
		(*i)++;
	}
	else
		a->flag = str[*i];
}

int		ft_isflag(char c)
{
	if (c == '#' || c == '+' || c == '-' || c == '0'
			|| c == ' ' || (c >= '0' && c <= '9')
			|| c == 'h' | c == 'l' || c == 'j'
			|| c == 'z' || c == '*' || c == '.')
		return (1);
	return (0);
}

void	ft_star(t_conversion *a, va_list va, char *format, int *i)
{
	int	r;

	r = 0;
	if (format[*i] == '.')
	{
		r = va_arg(va, int);
		if (r < 0)
			a->precision = -1;
		else
			a->precision = r;
		(*i)++;
	}
	else
	{
		r = va_arg(va, int);
		if (r < 0)
		{
			a->minus = 1;
			r *= -1;
		}
		a->size = r;
	}
}
