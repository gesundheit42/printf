#include "ft_printf.h"
#define	needzero a.precision >= ft_strlen(s) || a.zero == 1
#define noprecision a.precision == 0 || a.precision == -2

int	    ft_strlen(const char *str)
{
	int len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

int give(char a, int i)
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

int     ft_putuint(t_conversion a, va_list va)
{
	char    *s;
	int     d;

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

char	*ft_setsizeD(t_conversion *a, va_list va)
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

int		ft_putD(t_conversion a, va_list va, int d, char *s)
{
	s = ft_setsizeD(&a, va);
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
int     ft_putuuint(t_conversion a, va_list va)
{
	char    	*s;
	int     	d;
	uint64_t	aux;

	aux = (unsigned long int)va_arg(va, uint64_t);
	s = ft_itoa_baseu(aux, 10, 0);
	d = ft_putspace(&a, s, 0, 0);
	return (ft_printnbr(a, s, 0, 0) + d);
}

int     ft_putmem(t_conversion a, va_list va, int c)
{
	if (!a.flag)
		a.flag = 'L';
	a.diez = 1;
	return (ft_puthexa(a, va, 1, c));
}

int     ft_putocta(t_conversion a, va_list va, int d)
{
	char    *s;

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
	return (ft_printnbr(a, s, 0, 0) + d);
}

int     ft_puthexa(t_conversion a, va_list va, int p, int c)
{
	char    *s;
	int		d;

	s = ft_setsizeu(&a, va, 16, c);
	d = ft_putspace(&a, s, 0, 0);
	if (needzero || (p == 1 && (needzero || noprecision)))
	{
		if (a.diez == 1 && (s[0] != '0' || p == 1))
		{
			d = d + 2;
			ft_putchar((a.size--) * 0 + '0');
			ft_putchar((a.size--) * 0 + 'X' + c);
		}
	}
	else if (a.diez == 1 && s[0] != '0' && c == 32 )
		s = ft_strjoin("0x", s);
	else if (p == 1)
		s = ft_strjoin("0x", s);
	else if (a.diez == 1 && s[0] != '0')
		s = ft_strjoin("0X", s);
	if ((a.precision == 0 || a.precision == -2) && s[0] == '0')
		s[0] = 0;
	return (ft_printnbr(a, s, 0, 0) + d);
}

int ft_wcharconvert(char *dest, wchar_t ch)
{
	if (ch < 128) 
	{
		dest[0] = (char)ch;
		return (1);
	}
	if (ch < 2048) 
	{
		dest[0] = (ch>>6) | 192;
		dest[1] = (ch & 63) | 128;
		return (2);
	}
	if (ch < 65536) 
	{
		dest[0] = (ch>>12) | 224;
		dest[1] = ((ch>>6) & 63) | 128;
		dest[2] = (ch & 63) | 128;
		return (3);
	}
	if (ch < 1114112) 
	{
		dest[0] = (ch>>18) | 240;
		dest[1] = ((ch>>12) & 63) | 128;
		dest[2] = ((ch>>6) & 63) | 128;
		dest[3] = (ch & 63) | 128;
		return (4);
	}
	return 0;
}

void	ft_putwidechar(wchar_t c)
{
	char	*aux;
	int		d;
	int		j;

	j = -1;
	aux = (char *)malloc(5);
	d = ft_wcharconvert(aux, c);
	while (++j < d)
		ft_putchar(aux[j]);
	free(aux);
}

int		ft_wcharlen(wchar_t *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int		ft_putwstr(t_conversion a, wchar_t *str, int j, int i)
{
	int	len;

	if (a.precision != 0)
	{
		if (!str)
			str = L"(null)";
		i = a.size;
		len = ft_wcharlen(str);
		if (a.precision < len && a.precision != -1)
			len = a.precision;
		if (a.precision == -2)
			len = 0;
		if (a.minus == 0)
			while (((i--) - len) > 0)
				ft_putchar(' ' + a.zero * 16);
		while (j < len)
			ft_putwidechar(str[j++]);
		if (a.minus == 1)
			while (((i--) - len) > 0)
				ft_putchar(' ' + a.zero * 16);
		if (a.size >= len)
			return(a.size);
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
	while(++j < d)
		ft_putchar(aux[j]);
	if (a.minus == 1)
		while ((--i) > 0)
			ft_putchar(' ' + a.zero * 16);
	free(aux);
	if (a.size == 0)
		return (1);
	return (a.size);
}
