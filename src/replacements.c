/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 22:30:21 by hestela           #+#    #+#             */
/*   Updated: 2014/02/23 20:16:52 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

void			ft_do_replacements(char *line)
{
	ft_replace_alias(line);
	if (ft_strchr(line, '~'))
		ft_replace_tilde(line);
	if (ft_strchr(line, '$'))
		ft_replace_variable(line);
	if (ft_strchr(line, '*'))
		ft_replace_star(line);
	if (ft_strstr(line, ".sh"))
		ft_replace_script(line, 0, 0);
}

int				ft_check_is_cmd(char *line, char *buf, int i, int *j)
{
	int			cmd;
	int			k;

	cmd = 0;
	k = i;
	k--;
	while (k >= 0 && !ft_strchr(";><&|", line[k]))
	{
		if (line[k] != ' ')
			cmd = 1;
		k--;
	}
	if (cmd)
	{
		while (!ft_strchr(" <>&|;\0", line[i]))
		{
			buf[*j] = line[i];
			i++;
			(*j)++;
		}
		return (1);
	}
	return (0);
}
