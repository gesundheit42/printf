/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 20:05:07 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:34:37 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		test(char i)
{
	if (i == 'c' || i == 'i' || i == 'd' ||
			i == 'e' || i == 'E' || i == 'f' || i == 'g' ||
			i == 'G' || i == 'o' || i == 's' || i == 'u' ||
			i == 'x' || i == 'X' || i == 'x' || i == 'p' ||
			i == 'n' || i == '%' || i == 'O' || i == 'U' ||
			i == 'C' || i == 'D' || i == 'S' || i == 'n' || i == 'b')
		return (1);
	return (0);
}

void	ft_setinitial(t_conversion *a)
{
	a->precision = -1;
	a->plus = 0;
	a->size = 0;
	a->minus = 0;
	a->zero = 0;
	a->diez = 0;
	a->space = 0;
	a->flag = 0;
}

int		secondary(va_list va, char *format, int *d, t_conversion a)
{
	d[0] = 0;
	d[1] = 0;
	d[2] = -1;
	while (format[++d[2]] != '\0')
	{
		if (format[d[2]] == '%' && d[3] != 1)
		{
			ft_setinitial(&a);
			d[3] = 1;
		}
		else if (d[3] == 1 && test(format[d[2]]))
		{
			d[3] = 0;
			d[0] += ft_print(va, a, format[d[2]], d[1] + d[0]);
		}
		else if (d[3] == 1)
			d[3] = ft_setpre(&a, va, format, &d[2]);
		else
		{
			d[1]++;
			ft_putchar(format[d[2]]);
		}
	}
	return (d[1] + d[0]);
}

int		ft_printf(const char *format, ...)
{
	int				i;
	va_list			va;
	int				d[4];
	t_conversion	a;

	ft_setinitial(&a);
	va_start(va, format);
	i = secondary(va, (char *)format, d, a);
	va_end(va);
	return (i);
}
