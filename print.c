/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 20:15:16 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:20:12 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print1(va_list va, t_conversion a, char c)
{
	if (c == 'c')
		return (ft_putcharc(a, va_arg(va, int)));
	if (c == 's')
		return (ft_putstrc(a, va_arg(va, char *), 0, 0));
	if (c == 'd' || c == 'i')
		return (ft_putint(a, va, 0, 0));
	if (c == 'D')
		return (ft_putdlong(a, va, 0, 0));
	if (c == 'u')
		return (ft_putuint(a, va));
	if (c == 'U')
		return (ft_putuuint(a, va));
	if (c == 'x')
		return (ft_puthexa(a, va, 0, 32));
	if (c == 'X')
		return (ft_puthexa(a, va, 0, 0));
	if (c == '%')
		return (ft_putcharc(a, '%'));
	if (c == 'o')
		return (ft_putocta(a, va));
	if (c == 'p')
		return (ft_putmem(a, va, 32));
	return (0);
}

int		ft_print(va_list va, t_conversion a, char c, int len)
{
	if (c == 'C')
		return (ft_putwchar(a, va_arg(va, wchar_t), 0));
	if (c == 'O')
		return (ft_putoctalong(a, va));
	if (c == 'S')
		return (ft_putwstr(a, va_arg(va, wchar_t *), 0, 0));
	if (c == 'n')
		return (ft_setn(va, len));
	if (c == 'b')
		return (ft_putbinary(a, va));
	return (ft_print1(va, a, c));
}
