/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 14:58:12 by hestela           #+#    #+#             */
/*   Updated: 2014/02/23 19:43:07 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <termcap.h>
#include "libft.h"
#include "42sh.h"

static void		ft_multiligne(int *position, char *str);

void			ft_move_left(int *position, char *str)
{
	int			i;

	i = 0;
	if (*position == 0 || *(str + *position - 1) == '\n')
	{
		if (*(str + *position - 1) == '\n')
			ft_multiligne(position, str);
		else
			ft_putchar(07);
		return ;
	}
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	(*position)--;
	if ((*position + g_prompt_len + 1) % g_ws.ws_col == 0)
	{
		tputs(tgetstr("sr", NULL), 1, ft_putchar);
		if (g_env.in_histo != 0)
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
		while (i < g_ws.ws_col)
		{
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
			i++;
		}
	}
}

static void		ft_multiligne(int *position, char *str)
{
	char		*start;
	int			i;

	i = 0;
	start = str;
	(*position) -= 2;
	str = str + *position;
	tputs(tgetstr("sr", NULL), 1, ft_putchar);
	while (*(str - 1) != '\n' && str != start)
		str--;
	if (str == start)
	{
		while (i < g_prompt_len)
		{
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
			i++;
		}
	}
	while (*(str + 1) != '\n')
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		str++;
	}
	tputs(tgetstr("nd", NULL), 1, ft_putchar);
	(*position)++;
}

void			ft_move_right(int *position, char *str)
{
	if (*position == (int)ft_strlen(str))
	{
		ft_putchar(07);
		return ;
	}
	if (*(str + *position) == '\n')
	{
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		(*position)++;
	}
	else if (*(str + *position))
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		(*position)++;
	}
	if ((*position + g_prompt_len + 1) % g_ws.ws_col == 1)
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
}

void			ft_move_to_word_L(int *position, char *line)
{
	if (*position == 0)
	{
		ft_putchar(07);
		return ;
	}
	if (*position > 0)
		ft_move_left(position, line);
	while (*(line + *position) == ' ' && *position > 0)
		ft_move_left(position, line);
	while (*(line + (*position - 1)) != ' ' && *position > 0)
		ft_move_left(position, line);
}

void			ft_move_to_word_R(int *position, char *line)
{
	if (*position == (int)ft_strlen(line))
	{
		ft_putchar(07);
		return ;
	}
	if (*position < (int)ft_strlen(line))
		ft_move_right(position, line);
	while (*(line + *position) != ' ' && *position < (int)ft_strlen(line))
		ft_move_right(position, line);
	while (*(line + *position) == ' ' && *(line + *position))
		ft_move_right(position, line);
}
