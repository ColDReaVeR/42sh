/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 11:57:50 by hestela           #+#    #+#             */
/*   Updated: 2014/02/23 23:26:40 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <termcap.h>
#include "libft.h"
#include "42sh.h"

static void		ft_refresh(char *line, char *cpy, int position);

void			ft_del_char(char *line, int position)
{
	char		cpy[ARG_MAX];
	int			a;
	int			b;

	a = 0;
	b = 0;
	while (line[b])
	{
		if (b == position - 1)
			b++;
		else
			cpy[a++] = line[b++];
	}
	cpy[a] = '\0';
	ft_strcpy(line, cpy);
}


void			ft_add_char(char *line, int position, char c)
{
	char		cpy[ARG_MAX];
	int			a;
	int			b;
	int			bool;

	bool = 0;
	a = 0;
	b = 0;
	ft_strcpy(cpy, line);
	while (b < (int)ft_strlen(line) + 1)
	{
		if (b == position && bool == 0)
		{
			cpy[a++] = c;
			bool = 1;
		}
		else
			cpy[a++] = line[b++];
	}
	cpy[a] = '\0';
	ft_refresh(line, cpy, position);
}

static void		ft_refresh(char *line, char *cpy, int position)
{
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_putstr(line + position);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	ft_strcpy(line, cpy);
}
