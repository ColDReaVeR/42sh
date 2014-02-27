/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msommagg <msommagg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 01:46:28 by msommagg          #+#    #+#             */
/*   Updated: 2014/02/25 02:27:13 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "42sh.h"
#include "libft.h"

static void		ft_add_alias(char *str);
static void		ft_add_alias_next(char *alias, char *string);

void			ft_alias(char **av)
{
	t_alias_lst		*tmp;

	tmp = g_env.alias_lst;
	while (tmp && !av[1])
	{
		ft_printf("%s=%s\n", tmp->alias, tmp->string);
		tmp = tmp->next;
	}
	if (av[1])
		ft_add_alias(av[1]);
}

static void		ft_add_alias(char *str)
{
	char		alias[50];
	char		string[200];
	int			i;

	i = 0;
	while (*str != '=')
	{
		alias[i] = *str;
		i++;
		str++;
	}
	str++;
	alias[i] = '\0';
	i = 0;
	while (*str != '\'' && *str)
	{
		string[i] = *str;
		str++;
		i++;
	}
	string[i] = '\0';
	ft_add_alias_next(alias, string);
}

static void		ft_add_alias_next(char *alias, char *string)
{
	static t_alias_lst		*start;

	if (!g_env.alias_lst)
	{
		g_env.alias_lst = malloc(sizeof(t_alias_lst));
		start = g_env.alias_lst;
		g_env.alias_lst->start = start;
		g_env.alias_lst->alias = ft_strdup(alias);
		g_env.alias_lst->string = ft_strdup(string);
		g_env.alias_lst->next = NULL;
		return ;
	}
	start = g_env.alias_lst;
	while (g_env.alias_lst->next)
		g_env.alias_lst = g_env.alias_lst->next;
	g_env.alias_lst->next = malloc(sizeof(t_alias_lst));
	g_env.alias_lst = g_env.alias_lst->next;
	g_env.alias_lst->next = NULL;
	g_env.alias_lst->start = start;
	g_env.alias_lst->alias = ft_strdup(alias);
	g_env.alias_lst->string = ft_strdup(string);
	g_env.alias_lst = start;
}
