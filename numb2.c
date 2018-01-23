/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numb2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 20:59:50 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:18:18 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define NEEDZERO a.precision >= ft_strlen(s) || a.zero == 1
#define NOPRECISION a.precision == 0 || a.precision == -2

int		ft_putmem(t_conversion a, va_list va, int c)
{
	if (!a.flag)
		a.flag = 'L';
	a.diez = 1;
	return (ft_puthexa(a, va, 1, c));
}

int		ft_putbinary(t_conversion a, va_list va)
{
	char	*s;

	s = ft_setsizeu(&a, va, 2, 32);
	if ((a.precision == 0 || a.precision == -2) && s[0] == '0')
		s[0] = 0;
	return (ft_printnbr(a, s, 0, 0));
}

int		ft_putocta(t_conversion a, va_list va)
{
	char	*s;

	s = ft_setsizeu(&a, va, 8, 32);
	if (s[0] == '0' && a.diez == 1 && a.precision != 0 && a.precision != -2)
	{
		a.size--;
		a.diez = 0;
	}
	if ((a.precision == 0 || a.precision == -2) && s[0] == '0')
		s[0] = 0;
	if (a.diez == 1 && a.precision <= ft_strlen(s))
		s = ft_strjoin("0", s);
	return (ft_printnbr(a, s, 0, 0));
}

int		ft_puthexa(t_conversion a, va_list va, int p, int c)
{
	char	*s;
	int		d;

	s = ft_setsizeu(&a, va, 16, c);
	d = ft_putspace(&a, s, 0, 0);
	if (NEEDZERO || (p == 1 && (NEEDZERO || NOPRECISION)))
	{
		if (a.diez == 1 && (s[0] != '0' || p == 1))
		{
			d = d + 2;
			ft_putchar((a.size--) * 0 + '0');
			ft_putchar((a.size--) * 0 + 'X' + c);
		}
	}
	else if (a.diez == 1 && s[0] != '0' && c == 32)
		s = ft_strjoin("0x", s);
	else if (p == 1)
		s = ft_strjoin("0x", s);
	else if (a.diez == 1 && s[0] != '0')
		s = ft_strjoin("0X", s);
	if ((a.precision == 0 || a.precision == -2) && s[0] == '0')
		s[0] = 0;
	return (ft_printnbr(a, s, 0, 0) + d);
}
