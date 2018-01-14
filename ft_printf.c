#include "ft_printf.h"
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <wchar.h>

int test(char i)
{
	if (i == 'c' || i == 'i' || i == 'd' ||
			i == 'e' || i == 'E' || i == 'f' || i == 'g' || 
			i == 'G' || i == 'o' || i == 's' || i == 'u' || 
			i == 'x' || i == 'X' || i == 'x' || i == 'p' ||
			i == 'n' || i == '%' || i == 'O' || i == 'U' || 
			i == 'C' || i == 'D' || i == 'S')
		return (1);
	return (0);
}

void    ft_setsize(t_conversion *a, const char *str, int *i)
{
	a->size = 0;
	while (str[*i] >= '0' && str[*i] <= '9' && str[*i] != '\0')
	{
		a->size *= 10;
		a->size += str[*i] - '0';
		(*i)++;
	}
	(*i)--;
}

void    ft_setprecision(t_conversion *a, const char *str, int *i)
{
	int d;

	(*i)++;
	d = *i;
	a->precision = 0;
	while (str[*i] >= '0' && str[*i] <= '9' && str[*i] != '\0')
	{
		a->precision *= 10;
		a->precision += str[*i] - '0';
		(*i)++;
	}
	if (*i - d == 0)
		a->precision = -2;
	(*i)--;
}

void    ft_setflag(t_conversion *a, const char *str, int *i)
{
	if (str[(*i) + 1] == str[*i])
	{
		if(str[*i] == 'h')
			a->flag = 'H';
		else
			a->flag = 'L';
		(*i)++;
	}
	else
		a->flag = str[*i];
}

void	ft_setpre(t_conversion *a, const char *format, int *i, int *d)
{
	while (format[*i] != '\0' && (!test(format[*i])))
	{
		if (format[*i] == '#')
			a->diez = 1;
		else if (format[*i] == '+')
			a->plus = 1;
		else if (format[*i] == '-')
			a->minus = 1;
		else if (format[*i] == '0')
			a->zero = 1;
		else if (format[*i] == ' ')
			a->space = 1;
		else if (format[*i] <= '9' && format[*i] > '0')
			ft_setsize(a, format, i);
		else if (format[*i] == '.')
			ft_setprecision(a, format, i);
		else if (format[*i] == 'h' || format[*i] == 'l' || format[*i] == 'j' || format[*i] == 'z')
			ft_setflag(a, format, i);
		else
		{
			*d = 0;
			break;
		}
		(*i)++;
	}
	(*i)--;
}

void ft_print_str(t_conversion a)
{
	printf("precizie = %i\n", a.precision);
	printf("plus = %i\n", a.plus);
	printf("size = %i\n", a.size);
	printf("minus = %i\n", a.minus);
	printf("zero = %i\n", a.zero);
	printf("diez = %i\n", a.diez);
	printf("spatiu = %i\n", a.space);
	printf("flag = %c\n", a.flag);
}

void    ft_setinitial(t_conversion *a)
{
	a->precision = -1;
	a->plus = 0;
	a->size = 0;
	a->minus = 0;
	a->zero = 0;
	a->diez = 0;
	a->space = 0;
	a->flag = 0;
}

int	ft_print(va_list va, t_conversion a, char c)
{
	if (c == 'c')
		return (ft_putcharc(a, va_arg(va, int)));
	if (c == 's')
		return (ft_putstrc(a, va_arg(va, char *), 0, 0));
	if (c == 'd' || c == 'i')
		return (ft_putint(a, va, 0, 0));
	if (c == 'D')
		return (ft_putD(a, va, 0, 0));
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
		return (ft_putocta(a, va, 0));
	if (c == 'p')
		return (ft_putmem(a, va, 32));
	if (c == 'C')
		return (ft_putwchar(a, va_arg(va, wchar_t), 0));
	if (c == 'O')
		return (ft_putoctalong(a, va));
	if (c == 'S')
		return (ft_putwstr(a, va_arg(va, wchar_t *), 0, 0));
	return (0);
}

int	secondary(va_list va, const char *format, int *d, t_conversion a)
{
	d[0] = 0;
	d[1] = 0;
	d[2] = -1;
	while (format[++d[2]] != '\0')
	{
		if (format[d[2]] == '%' && d[3] != 1)
		{
			ft_setinitial(&a);
			d[3] = 1;
		}
		else if (d[3] == 1 && test(format[d[2]]))
		{
			d[3] = 0;
			d[0] += ft_print(va, a, format[d[2]]);
		}
		else if (d[3] == 1)
			ft_setpre(&a, format, &d[2], &d[3]);
		else
		{
			d[1]++;
			ft_putchar(format[d[2]]);
		}
	}
	return (d[1] + d[0]);
}

int ft_printf(const char *format, ...)
{
	int         i;
	va_list     va;
	int         d[4];
	t_conversion  a;

	ft_setinitial(&a);	
	va_start(va, format);
	i = secondary(va, format, d, a);
	va_end(va);
	return (i);
}

// int main(void)
// {
//  clock_t time;
//  time = clock();
//  int i = 2147483647;
//  long l = 2147483647;
//  long long ll = 9223372036854775807;
//  char c = 0;
//  intmax_t im = 9223372036854775807;
//  while ((double)time/CLOCKS_PER_SEC < 15)
//  {
//   time = clock();
//   ft_printf("\n");
//   ft_printf("%%\n");
//   ft_printf("%d\n", 42);
//   ft_printf("%d%d\n", 42, 41);
//   ft_printf("%d%d%d\n", 42, 43, 44);
//   ft_printf("%ld\n", l);
//   ft_printf("%lld\n", ll);
//   ft_printf("%x %X %p %20.15d\n", 505, 505, &ll, 54321);
//   ft_printf("%-10d % d %+d %010d %hhd\n", 3, 3, 3, 1, c);
//   ft_printf("%jd %zd %u %o %#08x\n", im, (size_t)i, i, 40, 42);
//   ft_printf("%x %#X %s%s\n", 1000, 1000, "test", "test2");
//   ft_printf("%s%s%s\n", "test", "test", "test");
//   //ft_printf("%C\n", 15000);
//  }
//  return (0);
// }

int main()
{
	// intmax_t im = 9223372036854775807;
	int d;
	//int i = 2147483647;
	//long l = 2147483647;
	//long long ll = 9223372036854775807;
	//char c = 0;
	//wchar_t C = 4322;
	d = ft_printf("%s %C %d %p %x %% %S", "bonjour ", L'該', 42, &free, 42, L"لحم خنزير");
	printf("c = %d\n", d);
	d =    printf("%.p, %.0p", 0, 0);
	printf("c = %d\n", d);
	return (0);
}
