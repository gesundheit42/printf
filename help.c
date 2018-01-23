/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 20:18:21 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:06:42 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define FLAGZERO a->minus == 0 && a->zero == 0

char	*ft_setsizeu(t_conversion *a, va_list va, int base, int c)
{
	uint64_t aux;

	if (a->flag == 'H')
		aux = (unsigned char)va_arg(va, uint32_t);
	else if (a->flag == 'h')
		aux = (unsigned short int)va_arg(va, uint32_t);
	else if (a->flag == 'l')
		aux = (unsigned long int)va_arg(va, uint64_t);
	else if (a->flag == 'L')
		aux = (unsigned long long int)va_arg(va, uint64_t);
	else if (a->flag == 'j')
		aux = (unsigned long long int)va_arg(va, int64_t);
	else if (a->flag == 'z')
		aux = (size_t)va_arg(va, uint64_t);
	else
		aux = (unsigned int)va_arg(va, uint32_t);
	if (a->size > a->precision && a->precision != -1)
		a->zero = 0;
	return (ft_itoa_baseu(aux, base, c));
}

char	*ft_setsize10(t_conversion *a, va_list va, int neg)
{
	int64_t aux;

	if (a->flag == 'H')
		aux = (char)va_arg(va, int32_t);
	else if (a->flag == 'h')
		aux = (short int)va_arg(va, int32_t);
	else if (a->flag == 'l')
		aux = (long int)va_arg(va, int64_t);
	else if (a->flag == 'L')
		aux = (long long int)va_arg(va, int64_t);
	else if (a->flag == 'j')
		aux = (long long int)va_arg(va, int64_t);
	else if (a->flag == 'z')
		aux = (size_t)va_arg(va, int64_t);
	else
		aux = (int)va_arg(va, int32_t);
	if (a->size > a->precision && a->precision != -1)
		a->zero = 0;
	if (aux < 0)
	{
		neg = 1;
		aux = aux * -1;
	}
	return (ft_itoa_base(aux, 10, neg, 0));
}

int		ft_putspace(t_conversion *a, char *str, int aux, int i)
{
	int len;
	int	minus;

	minus = 0;
	if (str[0] == '-')
		minus = 1;
	if (a->plus == 1 || str[0] == '-')
		aux = 1;
	if (aux == 1)
		a->space = 0;
	if (a->size > a->precision && a->precision != -1 && FLAGZERO)
	{
		if (a->precision > ft_strlen(str) - minus)
			len = a->precision;
		else
			len = -1;
		if (a->size > len && len != -1)
			while ((a->size) > len + aux + a->space + 2 * a->diez)
			{
				a->size--;
				i++;
				ft_putchar(' ');
			}
	}
	return (i);
}

int		ft_putint(t_conversion a, va_list va, int d, char *s)
{
	s = ft_setsize10(&a, va, 0);
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
