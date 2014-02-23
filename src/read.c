/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 11:46:28 by hestela           #+#    #+#             */
/*   Updated: 2014/02/23 00:49:50 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include "libft.h"
#include "42sh.h"

static void		ft_read(char **line, int *position, int *autocomp, int ret);

void			ft_get_input(char **line)
{
	int				position;
	static int		autocomp;

	autocomp = 0;
	signal(SIGTSTP, ft_suspend);
	position = 0;
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	*line = ft_strdup("\0");
	ft_read(line, &position, &autocomp, 1);
	while (position < (int)ft_strlen(*line))
		ft_move_right(&position, *line);
	ft_putchar('\n');
}

static void		ft_read(char **line, int *position, int *autocomp, int ret)
{
	char		buf[1024];
	int			i;

	g_env.saved_line = line;
	while (!ft_strchr(buf, '\n') && ret > 0)
	{
		ft_bzero(buf, 1024);
		ret = read(0, buf, 1024);
		buf[ret] = '\0';
		if (ft_isprint(*buf))
		{
			i = 0;
			*autocomp = 0;
			while (buf[i++])
			{
				ft_putchar(buf[i - 1]);
				ft_add_char(line, *position, buf[i - 1]);
				(*position)++;
				if ((*position + g_prompt_len + 1) % g_ws.ws_col == 1)
					tputs(tgetstr("sf", NULL), 1, ft_putchar);
			}
		}
		else if (*buf != '\n')
			ft_check_key(buf, line, position, autocomp);
	}
}
