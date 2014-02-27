/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 15:12:19 by hestela           #+#    #+#             */
/*   Updated: 2014/02/23 19:52:36 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <termcap.h>
#include "libft.h"
#include "42sh.h"

static void		ft_multiligne(int *position, char *line);
static void		ft_multi_suite(int *position, char *line);

void			ft_move_to_beg(int *position, char *str)
{
	if (*position == 0)
	{
		ft_putchar(07);
		return ;
	}
	while (*position > 0)
	{
		ft_move_left(position, str);
	}
}

void			ft_move_to_end(int *position, char *str)
{
	if (*position == (int)ft_strlen(str))
	{
		ft_putchar(07);
		return ;
	}
	while (*position < (int)ft_strlen(str))
	{
		ft_move_right(position, str);
	}
}

void			ft_back(int *position, char *line)
{
	int			i;

	i = 0;
	if (*position == 0 || *(line + *position - 1) == '\n')
	{
		if (*position == 0)
			ft_putchar(07);
		else
			ft_multiligne(position, line);
		return ;
	}
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	if ((*position + g_prompt_len) % g_ws.ws_col == 0)
	{
		tputs(tgetstr("sr", NULL), 1, ft_putchar);
		if (g_env.in_histo != 0)
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
		while (i++ < g_ws.ws_col)
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
	}
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
	ft_del_char(line, *position);
	(*position)--;
}

static void		ft_multiligne(int *position, char *line)
{
	char		*start;
	int			str;
	int			i;

	i = 0;
	(*position) -= 2;
	start = line + *position;
	str = *position;
	tputs(tgetstr("sr", NULL), 1, ft_putchar);
	while (*(start - 1) != '\n' && str)
		str--;
	if (str == 0)
	{
		while (i++ < g_prompt_len)
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
	}
	while (*(start + 1) != '\n')
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		start++;
	}
	ft_multi_suite(position, line);
}

static void		ft_multi_suite(int *position, char *line)
{
	(*position) += 2;
	tputs(tgetstr("nd", NULL), 1, ft_putchar);
	ft_del_char(line, *position);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	(*position)--;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_putstr(line + *position);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}
