/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaut <varnaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 13:12:20 by varnaut           #+#    #+#             */
/*   Updated: 2018/01/17 21:36:30 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>

typedef struct	s_struct
{
	int			precision;
	int			plus;
	int			size;
	int			minus;
	int			zero;
	int			diez;
	int			space;
	char		flag;
}				t_conversion;

char			*ft_itoa_baseu(uint64_t value, int base, int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_setsize10(t_conversion *a, va_list va, int neg);
char			*ft_setsizeu(t_conversion *a, va_list va, int base, int c);
char			*ft_strcat(char *d, const char *s);
char			*ft_itoa_base(uint64_t value, int base, int neg, int c);
void			ft_setsize(t_conversion *a, const char *str, int *i);
void			ft_setprecision(t_conversion *a, const char *str, int *i);
void			ft_setflag(t_conversion *a, const char *str, int *i);
void			ft_star(t_conversion *a, va_list va, char *format, int *i);
void			ft_set(t_conversion *a, va_list va, char *format, int *i);
int				ft_putstr(char *str);
int				test(char i);
int				ft_isflag(char c);
int				ft_wcharconvert(char *dest, wchar_t ch);
int				ft_putwidechar(wchar_t c, int prlen, int strlen);
int				lencalc(int precision, wchar_t *str);
int				ft_putmem(t_conversion a, va_list va, int c);
int				ft_putbinary(t_conversion a, va_list va);
int				ft_putocta(t_conversion a, va_list va);
int				ft_puthexa(t_conversion a, va_list va, int p, int c);
int				ft_putstrc(t_conversion a, char *str, int j, int i);
int				ft_printnbr(t_conversion a, char *str, int j, int i);
int				ft_putbinary(t_conversion a, va_list va);
int				ft_setn(va_list va, int len);
int				ft_print1(va_list va, t_conversion a, char c);
int				ft_print(va_list va, t_conversion a, char c, int len);
int				ft_setpre(t_conversion *a, va_list va, char *format, int *i);
int				ft_putoctalong(t_conversion a, va_list va);
int				ft_putwchar(t_conversion a, wchar_t c, int b);
int				ft_putwstr(t_conversion a, wchar_t *str, int j, int i);
int				ft_putspace(t_conversion *a, char *str, int aux, int i);
int				ft_putstrc(t_conversion a, char *str, int j, int i);
int				ft_strlen(const char *str);
int				ft_putdlong(t_conversion a, va_list va, int d, char *s);
int				ft_putuuint(t_conversion a, va_list va);
int				ft_putuint(t_conversion a, va_list va);
int				ft_printnbr(t_conversion a, char *str, int j, int i);
int				ft_putchar(char c);
int				ft_printf(const char *format, ...);
int				ft_putcharc(t_conversion a, char c);
int				ft_putnbr(int n, int var, int size);
int				ft_putstr(char *str);
int				ft_putmem(t_conversion a, va_list va, int c);
int				ft_putocta(t_conversion a, va_list va);
int				ft_puthexa(t_conversion a, va_list va, int p, int c);
int				ft_putint(t_conversion a, va_list va, int d, char *s);
int				ft_printp(long int nb);
int				ft_hexa(int nb, int l, int v);
int				ft_octa(int nb, int l, int v);
int				ft_dece(int nb, int l);
int				give(char a, int i);
int				space(int j, int i);

#endif
