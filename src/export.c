/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 19:50:08 by hestela           #+#    #+#             */
/*   Updated: 2014/02/21 14:37:32 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

static int      ft_exist(char *var, char **env);
static char     **ft_add_new_var(char **env, char *name, char *value);
static void     ft_update_value(char **env, char *name, char *value);
static void		ft_get_values(char *str, char *var, char *value);

char			**ft_export(char **av, char **env)
{
	int			i;
	char		var[100];
	char		value[500];

	i = 1;
	if (av[1] == NULL)
		ft_array_str_print(env);
	while (av[i])
	{
		ft_bzero(var, 100);
		ft_bzero(value,500);
		ft_get_values(av[i], var, value);
		if (!ft_exist(var, env))
			env = ft_add_new_var(env, var, value);
		else
			ft_update_value(env, var, value);
		i++;
	}
	g_env.prev_status = 0;
	return (env);
}

static void		ft_get_values(char *str, char *var, char *value)
{
	int			j;

	j = 0;
	if (!ft_strchr(str, '='))
		ft_strcpy(var, str);
	else
	{
		while (*str != '=' && j++ >= 0)
		{
			var[j - 1] = *str;
			str++;
		}
		str++;
		j = 0;
		while (*str)
		{
			value[j] = *str;
			str++;
			j++;
		}
	}
}

static int      ft_exist(char *var, char **env)
{
	int         i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& *(env[i] + ft_strlen(var)) == '=')
			return (1);
		i++;
	}
	return (0);
}

static char     **ft_add_new_var(char **env, char *name, char *value)
{
	char        **envcpy;
	int         i;
	int         len;
	char        *tmp;

	envcpy = NULL;
	i = 0;
	len = (int) ft_array_str_len(env);
	envcpy = (char**) malloc(sizeof(*envcpy) * len + 3);
	while (env[i])
	{
		envcpy[i] = ft_strdup(env[i]);
		i++;
	}
	if (!value)
		envcpy[i] = ft_strjoin(name, "=");
	else
	{
		tmp = ft_strjoin(name, "=");
		envcpy[i] = ft_strjoin(tmp, value);
		free(tmp);
	}
	envcpy[i + 1] = NULL;
	envcpy[0] = ft_strdup(env[0]);
	return (envcpy);
}

static void     ft_update_value(char **env, char *name, char *value)
{
	int         i;
	char        *tmp;

	i = 0;
	while (ft_strncmp(env[i], name, ft_strlen(name)) != 0)
		i++;
	if (!value)
	{
		free(env[i]);
		env[i] = ft_strjoin(name, "=");
	}
	else
	{
		tmp = ft_strjoin(name, "=");
		env[i] = ft_strjoin(tmp, value);
		free(tmp);
	}
}
