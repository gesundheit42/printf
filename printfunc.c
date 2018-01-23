/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfunc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 20:30:30 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:42:03 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_putcharc(t_conversion a, char c)
{
	int i;

	i = a.size;
	if (a.minus == 0)
		while ((--i) > 0)
			ft_putchar(' ' + a.zero * 16);
	write(1, &c, 1);
	if (a.minus == 1)
		while ((--i) > 0)
			ft_putchar(' ' + a.zero * 16);
	if (a.size == 0)
		return (1);
	return (a.size);
}

int		ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int		ft_putstrc(t_conversion a, char *str, int j, int i)
{
	int	len;

	if (a.precision != 0)
	{
		if (!str)
			str = "(null)";
		i = a.size;
		len = ft_strlen((const char *)str);
		if (a.precision < len && a.precision != -1)
			len = a.precision;
		if (a.precision == -2)
			len = 0;
		if (a.minus == 0)
			while (((i--) - len) > 0)
				ft_putchar(' ' + a.zero * 16);
		while (j < len)
			write(1, &str[j++], 1);
		if (a.minus == 1)
			while (((i--) - len) > 0)
				ft_putchar(' ' + a.zero * 16);
		if (a.size >= len)
			return (a.size);
		return (len);
	}
	return (a.size);
}

int		ft_printnbr(t_conversion a, char *str, int j, int i)
{
	int	len;
	int	d;
	int	l;

	i = a.size;
	len = ft_strlen((const char *)str);
	d = len;
	if (a.precision >= len)
		len = a.precision;
	d = len - d;
	l = d;
	if (a.minus == 0)
		while (((i--) - len) > 0)
			ft_putchar(' ' + a.zero * 16);
	while (d--)
		ft_putchar('0');
	while ((len - l++) > 0)
		write(1, &str[j++], 1);
	if (a.minus == 1)
		while (((i--) - len) > 0)
			ft_putchar(' ');
	free(str);
	if (a.size >= len)
		return (a.size);
	return (len);
}
