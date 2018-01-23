/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 20:41:50 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:15:07 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strlen(const char *str)
{
	int len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

int		give(char a, int i)
{
	if (a == '+')
	{
		if (i >= 0)
			return (ft_putchar('+'));
		if (i < 0)
			return (1);
	}
	else
	{
		if (i < 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

int		ft_putwstr(t_conversion a, wchar_t *str, int j, int i)
{
	int	len;
	int	prlen;

	prlen = 0;
	if (a.precision != 0)
	{
		if (!str)
			str = L"(null)";
		i = a.size;
		len = lencalc(a.precision, str);
		if (a.precision == -2)
			len = 0;
		while (((i--) - len) > 0 && a.minus == 0)
			ft_putchar(' ' + a.zero * 16);
		while (str[j] != 0 && prlen < len)
			prlen += ft_putwidechar(str[j++], prlen, len);
		while (((i--) - len) > 0 && a.minus == 1)
			ft_putchar(' ' + a.zero * 16);
		if (a.size < len)
			return (len);
	}
	return (a.size);
}

int		ft_putwchar(t_conversion a, wchar_t c, int b)
{
	char	*aux;
	int		d;
	int		j;
	int		i;

	if (b == 1)
		c = (char)c;
	j = -1;
	aux = (char *)malloc(5);
	i = a.size;
	if (a.minus == 0)
		while ((--i) > 0)
			ft_putchar(' ' + a.zero * 16);
	d = ft_wcharconvert(aux, c);
	while (++j < d)
		ft_putchar(aux[j]);
	if (a.minus == 1)
		while ((--i) > 0)
			ft_putchar(' ' + a.zero * 16);
	free(aux);
	if (a.size == 0)
		return (d);
	return (a.size + d);
}
