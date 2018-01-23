/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 21:10:06 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:12:46 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

uint64_t	ft_pow(int nb, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

char		*ft_itoa_base(uint64_t value, int base, int neg, int c)
{
	int		i;
	char	*nbr;

	i = 1;
	while (ft_pow(base, i) - 1 < value)
		i++;
	nbr = (char*)malloc(sizeof(nbr) * i);
	nbr[i + neg] = '\0';
	while (i-- > 0)
	{
		if (value % base > 9)
			nbr[i + neg] = (value % base) + 'A' - 10 + c;
		else
			nbr[i + neg] = (value % base) + '0';
		value = value / base;
	}
	if (neg)
		nbr[0] = '-';
	return (nbr);
}

int			ft_sizeu(uint64_t value)
{
	int	i;

	i = 0;
	if (value == 0)
		i = 1;
	while (value > 0)
	{
		i++;
		value = value / 10;
	}
	return (i);
}

char		*ft_itoa_baseu(uint64_t value, int base, int c)
{
	char	*nbr;
	int		i;

	i = 1;
	if (base == 10)
		i = ft_sizeu(value);
	else
		while (ft_pow(base, i) - 1 < value)
			i++;
	nbr = (char*)malloc(sizeof(nbr) * i);
	nbr[i] = '\0';
	while (i-- > 0)
	{
		if (value % base > 9)
			nbr[i] = (value % base) + 'A' - 10 + c;
		else
			nbr[i] = (value % base) + '0';
		value = value / base;
	}
	return (nbr);
}
