/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 19:13:28 by hestela           #+#    #+#             */
/*   Updated: 2014/02/17 19:19:50 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

static int		ft_get_cur_pos(int *x);

void			ft_check_position(void)
{
	int			x;

	ft_get_cur_pos(&x);
	if (x > 1)
	{
		ft_putstr(F_GREEN);
		ft_putstr(C_REV);
		ft_putchar('%');
		ft_putstr(C_RESET);
		ft_putchar('\n');
	}
}

static int		ft_get_cur_pos(int *x)
{
	int			y;
	int			ret;
	char		buf[12];

	y = 0;
	*x = 0;
	ft_putstr_fd("\033[6n", 0);
	ft_putstr(C_RESET);
	ret = read(1, buf, 12);
	buf[ret] = '\0';
	if (buf[0] != 27)
		return (1);
	if (buf[1] != '[')
		return (2);
	ret = 2;
	while (buf[ret] >= '0' && buf[ret] <= '9')
		y = ((10 * (y)) + (buf[ret++] - '0'));
	if (buf[ret++] != ';')
		return (3);
	while (ret < 12 && buf[ret] >= '0' && buf[ret] <= '9')
		*x = ((10 * (*x)) + (buf[ret++] - '0'));
	if (buf[ret] != 'R')
		return (4);
	return (0);
}
