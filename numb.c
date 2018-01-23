/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 20:57:45 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:16:25 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putuint(t_conversion a, va_list va)
{
	char	*s;
	int		d;

	s = ft_setsizeu(&a, va, 10, 32);
	d = ft_putspace(&a, s, 0, 0);
	if ((a.precision == 0 || a.precision == -2) && s[0] == '0')
		s[0] = 0;
	return (ft_printnbr(a, s, 0, 0) + d);
}

int		ft_putoctalong(t_conversion a, va_list va)
{
	char		*s;
	uint64_t	aux;

	aux = (unsigned long int)va_arg(va, uint64_t);
	s = ft_itoa_baseu(aux, 8, 0);
	if ((a.precision == 0 || a.precision == -2) && s[0] == '0')
		s[0] = 0;
	if (a.diez == 1 && a.precision <= ft_strlen(s))
		s = ft_strjoin("0", s);
	return (ft_printnbr(a, s, 0, 0));
}

char	*ft_setsizedlong(t_conversion *a, va_list va)
{
	int64_t aux;
	int		neg;

	neg = 0;
	aux = (long int)va_arg(va, int64_t);
	if (a->size > a->precision && a->precision != -1)
		a->zero = 0;
	if (aux < 0)
	{
		neg = 1;
		aux = aux * -1;
	}
	return (ft_itoa_base(aux, 10, neg, 0));
}

int		ft_putdlong(t_conversion a, va_list va, int d, char *s)
{
	s = ft_setsizedlong(&a, va);
	d = ft_putspace(&a, s, 0, 0);
	if (a.space == 1 && a.plus != 1 && s[0] != '-')
		ft_putchar((a.size--) * 0 + ' ' + (d++) * 0);
	if (a.zero == 1 || a.precision >= ft_strlen(s))
	{
		if (a.plus == 1 && s[0] != '-')
		{
			d++;
			ft_putchar((a.size--) * 0 + '+');
		}
		else if (s[0] == '-' && (a.precision >= ft_strlen(s) ||
					(a.size > ft_strlen(s) && a.zero == 1 && a.minus == 0)))
		{
			s[0] = '0';
			d++;
			ft_putchar((a.size--) * 0 + '-');
		}
	}
	else if (a.plus == 1 && s[0] != '-' && a.zero == 0
			&& a.precision < ft_strlen(s))
		s = ft_strjoin("+", s);
	if ((a.precision == 0 || a.precision == -2) && s[0] == '0')
		s[0] = 0;
	return (ft_printnbr(a, s, 0, 0) + d);
}

int		ft_putuuint(t_conversion a, va_list va)
{
	char		*s;
	int			d;
	uint64_t	aux;

	aux = (unsigned long int)va_arg(va, uint64_t);
	s = ft_itoa_baseu(aux, 10, 0);
	d = ft_putspace(&a, s, 0, 0);
	return (ft_printnbr(a, s, 0, 0) + d);
}
