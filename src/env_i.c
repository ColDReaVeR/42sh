/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 13:37:14 by hestela           #+#    #+#             */
/*   Updated: 2014/02/18 14:37:44 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

static int		ft_is_option(char *opt);
static int		ft_is_executable(char *str);
static void		ft_simple_exec(char **av);
static void		ft_exec_without_env(char **av);

int				ft_env_i(char **av)
{
	if (!ft_is_option(av[1]))
	{
		if (!ft_is_executable(av[1]))
			return (1);
	}
	if (ft_is_option(av[1]) && !av[2])
		return (1);
	if (!ft_is_option(av[1]) && ft_is_executable(av[1]))
	{
		ft_simple_exec(av);
		return (1);
	}
	else if (ft_is_option(av[1]) && ft_is_executable(av[2]))
	{
		ft_exec_without_env(av);
		return (1);
	}
	return (1);
}

static int		ft_is_option(char *opt)
{
	if (*opt != '-')
		return (0);
	opt++;
	while (*opt)
	{
		if (*opt != 'i')
		{
			ft_printf("%$%s%$", ERROR_CLR\
				, "usage: env [-i] [name=value ...] [utility [argument ...]]"
				,TEXT_CLR);
			return (0);
		}
		opt++;
	}
	return (1);
}

static int		ft_is_executable(char *str)
{
	char		*path;

	path = ft_strjoin("/", str);
	if (!ft_check_exist(path))
	{
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

static void		ft_simple_exec(char **av)
{
	char		**new_av;
	int			i;
	int			len;
	int			k;

	len = 0;
	i = 1;
	k = 0;
	while (av[i])
	{
		len++;
		i++;
	}
	new_av = (char**) malloc(sizeof(*new_av) * len + 1);
	i = 1;
	while (av[i])
	{
		new_av[k] = ft_strdup(av[i]);
		i++;
		k++;
	}
	new_av[k] = '\0';
	ft_exec(new_av, g_env.env);
}

static void		ft_exec_without_env(char **av)
{
	char		**new_av;
	int			i;
	int			len;
	int			k;

	len = 0;
	i = 2;
	k = 0;
	while (av[i])
	{
		len++;
		i++;
	}
	new_av = (char**) malloc(sizeof(*new_av) * len + 1);
	i = 2;
	while (av[i])
	{
		new_av[k] = ft_strdup(av[i]);
		i++;
		k++;
	}
	new_av[k] = '\0';
	ft_exec(new_av, NULL);
}
