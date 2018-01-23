/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 20:32:21 by user01            #+#    #+#             */
/*   Updated: 2018/01/17 21:37:15 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strcpy(char *dest, const char *source)
{
	int i;

	i = 0;
	while (source[i] != '\0')
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *d, const char *s)
{
	char *save;

	save = d;
	while (*d)
		d++;
	while ((*d++ = *s++))
		;
	return (save);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *ptr;

	if (s1 && s2)
	{
		ptr = (char *)malloc(sizeof(char) *
				(ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1));
		if (ptr)
		{
			ft_strcpy(ptr, s1);
			ft_strcat(ptr, s2);
			ptr[ft_strlen((char*)s1) + ft_strlen((char*)s2)] = '\0';
			return (ptr);
		}
	}
	return (0);
}
