/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 15:26:26 by hestela           #+#    #+#             */
/*   Updated: 2014/02/21 15:59:31 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "42sh.h"

void		ft_exec_and(char **av1, char **av2, char **env)
{
	if (!ft_builtin(av1))
		ft_exec(av1, env);
	if (g_env.prev_status == 0)
	{
		if (!ft_builtin(av2))
			ft_exec(av2, env);
	}
}

void        ft_exec_or(char **av1, char **av2, char **env)
{
	if (!ft_builtin(av1))
		ft_exec(av1, env);
	if (g_env.prev_status != 0)
	{
		if (!ft_builtin(av2))
			ft_exec(av2, env);
	}
}
