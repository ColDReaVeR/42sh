/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 18:06:30 by hestela           #+#    #+#             */
/*   Updated: 2014/02/18 14:15:30 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "42sh.h"

void		ft_env(char **av, char **env)
{
	int		i;
	int		j;
	char	*str;

	if (av[0])
	{
		if (av[1])
		{
			if (ft_env_i(av))
				return ;
		}
		while (env[i])
		{
			j = -1;
			str = env[i];
			ft_putstr(INFOS_CLR);
			while (str[j] != '=' && j++ >= -1)
				ft_putchar(str[j]);
			ft_putstr(TEXT_CLR);
			while (str[j] && j++ >= -1)
				ft_putchar(str[j]);
			ft_putchar('\n');
			i++;
		}
	}
}
