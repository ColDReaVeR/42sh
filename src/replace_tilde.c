/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tilde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 22:47:47 by hestela           #+#    #+#             */
/*   Updated: 2014/02/23 20:19:34 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

static int		ft_count_tilde(char *s);
static void		ft_cat_home(char *line, char *str, char *home);

void			ft_replace_tilde(char *line)
{
	char		*str;
	char		*home;

	if (ft_count_tilde(line))
	{
		home = ft_getenv(g_env.env, "HOME");
		str = malloc(sizeof(*str) * (ft_strlen(line)\
			+ (ft_strlen(home) * ft_count_tilde(line)) + 1));
		ft_cat_home(line, str, home);
		ft_strcpy(line, str);
		free(str);
	}
}

static int		ft_count_tilde(char *s)
{
	int			count;
	char		quote;

	quote = '\0';
	count = 0;
	if (*s == '~')
	{
		count++;
		s++;
	}
	while (*s)
	{
		if (quote == '\0' && ft_strchr("\"'", *s))
			quote = *s;
		else if (quote == *s && *(s - 1) != '\\')
			quote = '\0';
		if (*s == '~' && ft_strchr(";\"'`<>| ", *(s - 1)) && quote == '\0')
			count++;
		s++;
	}
	return (count);
}

static void		ft_instring(char *quote, char *line, int j)
{
	if (*quote == '\0' && ft_strchr("\"'", line[j]))
		*quote = line[j];
	else if (*quote == line[j] && line[j - 1] != '\\')
		*quote = '\0';
}

static void		ft_cat_home(char *line, char *str, char *home)
{
	int			i;
	int			j;
	char		quote;

	i = 0;
	j = 0;
	quote = '\0';
	while (line[j] != '~' && quote == '\0')
	{
		ft_instring(&quote, line, j);
		str[i] = line[j];
		i++;
		j++;
	}
	while (*home)
	{
		str[i] = *home;
		home++;
		i++;
	}
	j++;
	while (line[j] && i++ > 0 && j++ > 0)
		str[i - 1] = line[j - 1];
	str[i] = '\0';
}
