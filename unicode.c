/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 21:01:33 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:15:18 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wcharconvert(char *dest, wchar_t ch)
{
	if (ch < 128)
	{
		dest[0] = (char)ch;
		return (1);
	}
	if (ch < 2048)
	{
		dest[0] = (ch >> 6) | 192;
		dest[1] = (ch & 63) | 128;
		return (2);
	}
	if (ch < 65536)
	{
		dest[0] = (ch >> 12) | 224;
		dest[1] = ((ch >> 6) & 63) | 128;
		dest[2] = (ch & 63) | 128;
		return (3);
	}
	dest[0] = (ch >> 18) | 240;
	dest[1] = ((ch >> 12) & 63) | 128;
	dest[2] = ((ch >> 6) & 63) | 128;
	dest[3] = (ch & 63) | 128;
	return (4);
}

int		ft_putwidechar(wchar_t c, int prlen, int strlen)
{
	char	*aux;
	int		d;
	int		j;
	int		len;

	j = -1;
	aux = (char *)malloc(5);
	d = ft_wcharconvert(aux, c);
	while (++j < d)
		ft_putchar(aux[j]);
	free(aux);
	return (d);
}

int		wcharlen(const wchar_t ch)
{
	if (ch < 128)
		return (1);
	if (ch < 2048)
		return (2);
	if (ch < 65536)
		return (3);
	if (ch < 1114112)
		return (4);
	return (0);
}

int		ft_wcharlen(const wchar_t *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		len += wcharlen(str[i]);
		i++;
	}
	return (len);
}

int		lencalc(int precision, wchar_t *str)
{
	int len;
	int	d;
	int	i;

	i = 0;
	if (precision == -2)
		precision = 0;
	len = ft_wcharlen((const wchar_t *)str);
	if (precision < len && precision != -1)
	{
		len = 0;
		while (len < precision)
		{
			d = wcharlen(str[i]);
			if (len + d <= precision)
				len += d;
			else
				break ;
		}
	}
	return (len);
}
