#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int ft_putcharc(t_conversion a, char c)
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

int ft_putstr(char *str)
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

int 	ft_putstrc(t_conversion a, char *str, int j, int i)
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
			return(a.size);
		return (len);
	}
	return (a.size);
}

int ft_printnbr(t_conversion a, char *str, int j, int i)
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
		return(a.size);
	return (len);
}

char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (dest[i] != 0)
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

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

char	*ft_setsize10(t_conversion *a, va_list va)
{
	int64_t aux;
	int		neg;

	neg = 0;
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
    if (a->size > a->precision && a->precision != -1 && a->minus == 0 && a->zero == 0)
    {
        if (a->precision > ft_strlen(str) - minus)
            len = a->precision;
        else
            len = -1;
        if (a->size > len && len != -1)
            while ((a->size--) > len + aux + a->space + 2 * a->diez)
            {
                i++;
                ft_putchar(' ');
            }
    }
    return (i);
}

int		ft_putint(t_conversion a, va_list va, int d, char *s)
{
    s = ft_setsize10(&a, va);
    d = ft_putspace(&a, s, 0, 0);
    if (a.zero == 1 || a.precision >= ft_strlen(s))
    {
        if (a.plus == 1 && s[0] != '-')
        {
            d++;
            ft_putchar((a.size--) * 0 + '+');
        }
        else if (s[0] == '-' && (a.precision >= ft_strlen(s) || (a.size > ft_strlen(s)
                                        && a.zero == 1 && a.minus == 0)))
        {
            s[0] = '0';
            d++;
            ft_putchar((a.size--) * 0 + '-');
        }
    }
    if (a.space == 1 && a.plus != 1 && s[0] != '-')
    {
        d++;
        ft_putchar((a.size--) * 0 + ' ');
    }
    else if (a.plus == 1 && s[0] != '-' && a.zero == 0 && a.precision < ft_strlen(s))
        s = ft_strjoin("+", s);
    if ((a.precision == 0 || a.precision == -2) && s[0] == '0')
        s[0] = 0;
    return (ft_printnbr(a, s, 0, 0) + d);
}
