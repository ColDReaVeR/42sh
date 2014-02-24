/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 12:35:39 by hestela           #+#    #+#             */
/*   Updated: 2014/02/24 19:28:18 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <termcap.h>
#include "42sh.h"

static int		ft_getkey(char *str);
static void		ft_check_key_suite(int key, int *pos, char *line);
static void		ft_ctrl_d(int *pos, char *line);

void			ft_check_key(char *buf, char *line, int *position, int *comp)
{
	int				key;
	static char		saved[ARG_MAX];

	key = ft_getkey(buf);
	if (key == TAB)
		ft_autocomp(line, position, comp);
	else
		*comp = 0;
	if (key == UP && g_env.quote_wait == 0)
	{
		if (g_env.in_histo == 0)
			ft_strcpy(saved, line);
		ft_previous_cmd(position, line);
	}
	if (key == DOWN && g_env.quote_wait == 0)
		ft_next_cmd(position, line, saved);
	if (key == ALT_W || key == ALT_W2)
		ft_cut(line, position);
	if (key == CTRL_X)
		ft_paste(line, position);
	if (key == CTRL_W)
		ft_copy(line, *position);
	ft_check_key_suite(key, position, line);
	ft_bzero(buf, 8);
}

static void		ft_check_key_suite(int key, int *pos, char *line)
{

	if (key == CTRL_LEFT)
		ft_move_to_word_L(pos, line);
	if (key == CTRL_RIGHT)
		ft_move_to_word_R(pos, line);
	if (key == CTRL_UP)
		ft_move_up(pos, line);
	if (key == CTRL_DW)
		ft_move_down(pos, line);
	if (key == CTRL_A || key == HOME)
		ft_move_to_beg(pos, line);
	if (key == CTRL_E || key == END)
		ft_move_to_end(pos, line);
	if (key == LEFT)
		ft_move_left(pos, line);
	if (key == RIGHT)
		ft_move_right(pos, line);
	if (key == BACK)
		ft_back(pos, line);
	if (key == CTRL_D)
		ft_ctrl_d(pos, line);
	if (key == CTRL_C && g_env.in_exec == NULL && g_env.quote_wait == 0)
	{
		ft_kill(1);
		*pos = 0;
	}
}

static void		ft_ctrl_d(int *pos, char *line)
{
	if (!ft_strlen(line) && g_env.quote_wait == 0)
	{
		ft_putchar('\n');
		ft_exit(NULL, 0);
	}
	else if (*pos == (int)ft_strlen(line))
		ft_putchar(7);
	else if (*pos != (int)ft_strlen(line) && (int)ft_strlen(line) != 0)
	{
		ft_del_char(line, *pos + 1);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
	}
}

static int		ft_getkey(char *str)
{
	int			result;
	int			i;
	int			mult;
	int			value;

	result = 0;
	i = 0;
	while (i < 6)
	{
		mult = 10;
		value = str[i];
		while (value > 10)
		{
			mult *= 10;
			value /= 10;
		}
		result = result * mult + str[i];
		i++;
	}
	return (result);
}
