/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaut <varnaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 13:12:20 by varnaut           #+#    #+#             */
/*   Updated: 2018/01/14 16:10:20 by cgorun           ###   ########.fr       */
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

typedef   struct  s_struct
{
    int     precision;
    int     plus;
    int     size;
    int     minus;
    int     zero;
    int     diez;
    int     space;
    char    flag;
}           t_conversion;

char	*ft_itoa_baseu(uint64_t value, int base, int c);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_setsize10(t_conversion *a, va_list va);
char	*ft_setsizeu(t_conversion *a, va_list va, int base, int c);
char	*ft_strcpy(char *dest, const char *source);
int		ft_putoctalong(t_conversion a, va_list va);
int		ft_putwchar(t_conversion a, wchar_t c, int b);
int		ft_putwstr(t_conversion a, wchar_t *str, int j, int i);
int		ft_putspace(t_conversion *a, char *str, int aux, int i);
int     ft_putstrc(t_conversion a, char *str, int j, int i);
int 	ft_strlen(const char *str);
int		ft_putD(t_conversion a, va_list va, int d, char *s);
int		ft_putuuint(t_conversion a, va_list va);
int     ft_putuint(t_conversion a, va_list va);
int     ft_printnbr(t_conversion a, char *str, int j, int i);
int	    ft_putchar(char c);
int     ft_printf(const char *format, ...);
int     ft_putcharc(t_conversion a, char c);
int     ft_putnbr(int n, int var, int size);
int     ft_putstr(char *str);
int     ft_putmem(t_conversion a, va_list va, int c);
int     ft_putocta(t_conversion, va_list va, int d);
int     ft_puthexa(t_conversion a, va_list va, int p, int c);
int		ft_putint(t_conversion a, va_list va, int d, char *s);
char	*ft_itoa_base(uint64_t value, int base, int neg, int c);
int     ft_printp(long int nb);
int     ft_hexa(int nb, int l, int v);
int     ft_octa(int nb, int l, int v);
int     ft_dece(int nb, int l);
int     give(char a, int i);
int     space(int j, int i);

#endif
