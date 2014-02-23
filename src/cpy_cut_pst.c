/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_cut_pst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 13:37:42 by hestela           #+#    #+#             */
/*   Updated: 2014/02/23 19:38:59 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <termcap.h>
#include "libft.h"
#include "42sh.h"

static void		ft_concat(int *i, char *new, char *str, int *position);
static void		ft_refresh(char *line, int *position, char *new);

void			ft_cut(char *line, int *position)
{
	int			pos;
	int			i;

	i = *position;
	if (g_env.cut)
	{
		free(g_env.cut);
		g_env.cut = NULL;
	}
	g_env.cut = ft_strdup(line + i);
	pos = *position;
	while (*position < (int)ft_strlen(line))
		ft_move_right(position, line);
	while (*position > pos)
		ft_back(position, line);
}

void			ft_copy(char *line, int position)
{
	int			i;

	i = position;
	if (g_env.cut)
	{
		free(g_env.cut);
		g_env.cut = NULL;
	}
	g_env.cut = ft_strdup(line + i);
}

void			ft_paste(char *line, int *position)
{
	char		*new;
	int			i[3];
	int			len1;
	int			len2;

	if (g_env.cut)
	{
		i[0] = 0;
		i[1] = 0;
		i[2] = 0;
		len1 = ft_strlen(line);
		len2 = ft_strlen(g_env.cut);
		if ((len1 + g_prompt_len + 1) / g_ws.ws_col
		< (len1 + len2 + g_prompt_len + 1) / g_ws.ws_col)
			g_env.in_histo = 1;
		new = (char *) malloc(sizeof(*new) * (len1 + 1 + len2));
		ft_concat(i, new, line, position);
		new[i[1]] = '\0';
		ft_refresh(line, position, new);
	}
}

static void		ft_concat(int *i, char *new, char *str, int *position)
{
	while (i[0] < *position)
	{
		new[i[1]] = str[i[0]];
		i[0]++;
		i[1]++;
	}
	while (g_env.cut[i[2]])
	{
		new[i[1]] = g_env.cut[i[2]];
		i[2]++;
		i[1]++;
	}
	while (str[i[0]])
	{
		new[i[1]] = str[i[0]];
		i[0]++;
		i[1]++;
	}
}

static void		ft_refresh(char *line, int *position, char *new)
{
	int			i;

	i = 0;
	ft_strcpy(line, new);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_putstr(new + *position);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	while (i < (int)ft_strlen(g_env.cut))
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		i++;
		(*position)++;
		if ((*position + g_prompt_len + 1) % g_ws.ws_col == 1)
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
	}
}
