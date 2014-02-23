/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 17:16:03 by hestela           #+#    #+#             */
/*   Updated: 2014/02/23 19:59:18 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <termcap.h>
#include "libft.h"
#include "42sh.h"

void			ft_previous_cmd(int *position, char *line)
{
	if (!g_env.histo || !g_env.histo->prev)
	{
		ft_putchar(07);
		return ;
	}
	g_env.in_histo = 1;
	while (*position > 0)
		ft_move_left(position, line);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	g_env.histo = g_env.histo->prev;
	ft_strcpy(line, g_env.histo->line);
	ft_putstr(line);
	*position += (int)ft_strlen(line);
}

void			ft_next_cmd(int *position, char *line, char *buf)
{
	if (!g_env.histo || !g_env.histo->next)
	{
		g_env.in_histo = 0;
		ft_putchar(07);
		return ;
	}
	while (*position > 0)
		ft_move_left(position, line);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	g_env.histo = g_env.histo->next;
	if (g_env.histo->line)
		ft_strcpy(line, g_env.histo->line);
	else
		ft_strcpy(line, buf);
	ft_putstr(line);
	*position += (int)ft_strlen(line);
}

static void		ft_update(char *line)
{
	if (g_env.histo == NULL)
	{
		g_env.histo = malloc(sizeof(t_histo));
		g_env.histo->prev = NULL;
		g_env.histo->next = malloc(sizeof(t_histo));
		g_env.histo->line = ft_strdup(line);
		g_env.histo->start = g_env.histo;
		g_env.histo->next->start = g_env.histo->start;
		g_env.histo->next->prev = g_env.histo;
		g_env.histo = g_env.histo->next;
		g_env.histo->next = NULL;
		g_env.histo->line = NULL;
	}
	else
	{
		while (g_env.histo->next)
			g_env.histo = g_env.histo->next;
		g_env.histo->line = ft_strdup(line);
		g_env.histo->next = malloc(sizeof(t_histo));
		g_env.histo->next->start = g_env.histo->start;
		g_env.histo->next->prev = g_env.histo;
		g_env.histo = g_env.histo->next;
		g_env.histo->next = NULL;
		g_env.histo->line = NULL;
	}
}

void			ft_update_history(char *line)
{
	if (*line)
	{
		ft_update(line);
		ft_putendl_fd(line, g_env.histo_fd);
	}
	else
	{
		if (g_env.histo)
		{
			while (g_env.histo->next)
				g_env.histo = g_env.histo->next;
		}
	}
}
