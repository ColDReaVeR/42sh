/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 12:48:18 by hestela           #+#    #+#             */
/*   Updated: 2014/02/21 14:34:25 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <termcap.h>
#include "libft.h"
#include "42sh.h"

static void		ft_print_args(char **av, int i);

int				ft_echo(char **av)
{
	int			end;
	int			i;

	if (av[1])
	{
		i = 1;
		end = 1;
		if (av[i][0] == '-' && av[i][1] == 'n')
		{
			end = 0;
			i++;
		}
		ft_print_args(av, i);
		if (end)
			ft_putchar('\n');
	}
	g_env.prev_status = 0;
	return (0);
}

static void		ft_print_args(char **av, int i)
{
	int			j;

	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] == '"' && av[i][j + 1] == '"')
				|| (av[i][j] == '\'' && av[i][j + 1] == '\''))
			{
				j++;
				ft_putchar(26);
			}
			else
				ft_putchar(av[i][j]);
			j++;
		}
		i++;
		if (av[i])
			ft_putchar(' ');
	}
}
