/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 18:06:30 by hestela           #+#    #+#             */
/*   Updated: 2014/02/23 00:44:32 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

static void		ft_export_new_env(char **av, int *i, char ***env);

void			ft_env(char **av, char **env)
{
	int			i;
	int			j;
	char		*str;

	i = 0;
	if (av[0])
	{
		if (av[1])
		{
			if (ft_env_i(av))
				return ;
		}
		while (env[i++])
		{
			j = -1;
			str = env[i - 1];
			while (str[j] != '=' && j++ >= -1)
				ft_printf("%$%c", INFOS_CLR, str[j]);
			ft_putstr(TEXT_CLR);
			while (str[j] && j++ >= -1)
				ft_putchar(str[j]);
			ft_putchar('\n');
		}
	}
	g_env.prev_status = 0;
}

void			ft_exec_without_env(char **av)
{
	char		**new_av;
	int			i;
	int			len;
	int			k;
	char		**new_env;

	len = 0;
	i = 2;
	k = 0;
	ft_export_new_env(av, &i, &new_env);
	while (av[i] && len++ >= 0)
		i++;
	new_av = (char**) malloc(sizeof(*new_av) * len + 1);
	i = 2;
	while (ft_strchr(av[i], '='))
		i++;
	while (av[i])
	{
		new_av[k] = ft_strdup(av[i]);
		i++;
		k++;
	}
	new_av[k] = '\0';
	ft_exec(new_av, new_env);
}

static void		ft_export_new_env(char **av, int *i, char ***env)
{
	int			len;
	int			k;
	char		**new_env;

	len = 0;
	k = *i;
	*env = NULL;
	while (ft_strchr(av[k], '=') && len++ >= 0)
		k++;
	if (k == *i)
	{
		*env = NULL;
		return ;
	}
	*env = (char**) malloc(sizeof(**env) * len + 1);
	new_env = *env;
	k = 0;
	while (ft_strchr(av[*i], '='))
	{
		new_env[k] = ft_strdup(av[*i]);
		k++;
		(*i)++;
	}
	new_env[k] = '\0';
}

char			**ft_update_pwd(char *str, int mode)
{
	char		**av;

	av = (char**) malloc(sizeof(*av) * 4);
	av[3] = '\0';
	av[0] = ft_strdup("setenv");
	if (mode == 1)
		av[1] = ft_strdup("OLDPWD");
	else if (mode == 2)
		av[1] = ft_strdup("PWD");
	av[2] = ft_strdup(str);
	return (av);
}
