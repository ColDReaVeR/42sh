/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 21:21:31 by hestela           #+#    #+#             */
/*   Updated: 2014/02/19 03:26:58 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"

static void		ft_opt1(const char *form, va_list *ap, int *i, int *count);
static void		ft_opt2(const char *form, va_list *ap, int *i, int *count);
static void		ft_opt3(const char *form, va_list *ap, int *i, int *count);
static void		ft_opt4(const char *form, va_list *ap, int *i, int *count);

void			ft_flags1(const char *form, va_list *ap, int *i, int *count)
{
	if (ft_strchr("csndifxXpo", form[*i]))
		ft_opt1(form, ap, i, count);
	else if (ft_strchr("EebutT", form[*i]))
		ft_opt2(form, ap, i, count);
	else if (ft_strchr("lLzh", form[*i]))
		ft_opt3(form, ap, i, count);
	else if (ft_strchr("#", form[*i]))
		ft_opt4(form, ap, i, count);
}

static void		ft_opt1(const char *form, va_list *ap, int *i, int *count)
{
	if (form[*i] == 'c')
		*count += ft_putchar(va_arg(*ap, int));
	else if (form[*i] == 's')
		*count += ft_putstr(va_arg(*ap, char*));
	else if (form[*i] == 'n')
		*va_arg(*ap, int*) = *count;
	else if (form[*i] == 'd' || form[*i] == 'i')
		*count += ft_putnbr(va_arg(*ap, int));
	else if (form[*i] == 'f')
		*count += ft_putfnbr(va_arg(*ap, double), 6);
	else if (form[*i] == 'x')
		*count += ft_putstr(ft_itoh(va_arg(*ap, long)));
	else if (form[*i] == 'X')
		*count += ft_putstr(ft_str_upcase(ft_itoh(va_arg(*ap, long))));
	else if (form[*i] == 'p')
		*count += ft_putadr(va_arg(*ap, void*));
	else if (form[*i] == 'o')
		*count += ft_putnbr(ft_itoo(va_arg(*ap, long)));
	*i += 2;
}

static void		ft_opt2(const char *form, va_list *ap, int *i, int *count)
{
	char		*str;

	if (form[*i] == 'e')
		*count += ft_putstr(ft_dtos(va_arg(*ap, double), 6));
	else if (form[*i] == 'E')
	{
		str = ft_str_upcase(ft_dtos(va_arg(*ap, double), 6));
		*count += ft_putstr(str);
		free(str);
	}
	else if (form[*i] == 'b')
		*count += ft_putnbr(ft_itob(va_arg(*ap, long)));
	else if (form[*i] == 'u')
		*count += ft_putnbr(va_arg(*ap, unsigned int));
	else if (form[*i] == 't')
		*count += ft_put_time(va_arg(*ap, long));
	else if (form[*i] == 'T')
		*count += ft_put_current_time();
	*i += 2;
}

static void		ft_opt3(const char *form, va_list *ap, int *i, int *count)
{
	char		*str;

	str = NULL;
	if (ft_strchr("lzh", form[*i]) && form[*i + 1] == 'o')
		*count += ft_putnbr(ft_itoo(va_arg(*ap, long)));
	else if (form[*i] == 'l' && form[*i + 1] == 'f')
		*count += ft_putfnbr(va_arg(*ap, double), 6);
	else if (form[*i] == 'L' && form[*i + 1] == 'f')
		*count += ft_putfnbr(va_arg(*ap, long double), 6);
	else if (ft_strchr("lzh", form[*i]) && ft_strchr("udi", form[*i + 1]))
		*count += ft_putnbr(va_arg(*ap, long));
	else if (ft_strchr("lzh", form[*i]) && form[*i + 1] == 'x')
		*count += ft_putstr(ft_itoh(va_arg(*ap, long)));
	else if (ft_strchr("lzh", form[*i]) && form[*i + 1] == 'X')
		str = ft_str_upcase(ft_itoh(va_arg(*ap, long)));
	else if (ft_strchr("lzh", form[*i]) && form[*i + 1] == 'n')
		*va_arg(*ap, long*) = *count;
	else if (form[*i] == 'L' && form[*i + 1] == 'e')
		*count += ft_putstr(ft_dtos(va_arg(*ap, long double), 6));
	else if (form[*i] == 'L' && form[*i + 1] == 'E')
		str = ft_str_upcase(ft_dtos(va_arg(*ap, long double), 6));
	if (form[*i + 1] == 'E' || form[*i + 1] == 'X')
		*count += ft_putstr(str);
	*i += 3;
}

static void		ft_opt4(const char *form, va_list *ap, int *i, int *count)
{
	int		index;
	int		j;

	index = 0;
	j = 0;
	(*i)++;
	while (ft_strchr(".+-* 0123456789", form[*i]))
	{
		j++;
		(*i)++;
	}
	if (ft_strchr("zlh", form[*i]))
		index = 1;
	if (form[*i + index] == 'o')
		*count += ft_putchar('0');
	else if (form[*i + index] == 'x')
		*count += ft_putstr("0x");
	else if (form[*i + index] == 'X')
		*count += ft_putstr("0X");
	*i -= j;
	if (ft_strchr("lzhoxX", form[*i]))
		ft_flags1(form, ap, i, count);
	else if (ft_strchr(". + *", form[*i]))
		ft_flags2(form, ap, i, count);
}
