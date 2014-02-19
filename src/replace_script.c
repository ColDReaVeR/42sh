/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_script.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 21:01:35 by hestela           #+#    #+#             */
/*   Updated: 2014/02/19 01:21:38 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "42sh.h"

static int		ft_add_script(char **line, char *buf, int i, int *j);
static char		*ft_script_path(char *str, int i);
static char		*ft_add_insert(char *script);
static void		ft_insert_script(char *to_insert, char *buf, int j);

void			ft_replace_script(char **line, int i, int j)
{
	char		buf[10240];
	char		quote;

	ft_bzero(buf, 10240);
	quote = '\0';
	while (line[0][i])
	{
		ft_in_string(&quote, line[0][i], line[0][i - 1]);
		if (ft_strncmp(line[0] + i, ".sh", 3) == 0 && quote == '\0')
		{
			while (i >= 0
				&& !ft_strchr(" ;&|<>", line[0][i]) && i-- >= 0 && j-- >= 0)
				buf[j + 1] = '\0';
			j++;
			i++;
			i += ft_add_script(line, buf, i, &j);
		}
		else if (i++ >= 0 && j++ >= 0)
			buf[j - 1] = line[0][i - 1];
	}
	free(*line);
	*line = ft_strdup(buf);
}

static int		ft_add_script(char **line, char *buf, int i, int *j)
{
	char		*str;
	char		*to_insert;
	char		*script;
	int			len;
	int			l;

	l = 0;
	str = *line;
	script = ft_script_path(str, i);
	len = ft_strlen(script);
	if (ft_check_is_cmd(line, buf, i, j))
		return (len);
	if (access(script, F_OK) != 0)
	{
		while (script[l] && l++ >= 0 && (*j)++ >= 0)
			buf[*j - 1] = script[l - 1];
		free(script);
		return (len);
	}
	to_insert = ft_add_insert(script);
	ft_insert_script(to_insert, buf, *j);
	*j += ft_strlen(to_insert);
	free(to_insert);
	free(script);
	return (len);
}

static char		*ft_script_path(char *str, int i)
{
	char		buf[1024];
	int			j;

	j = 0;
	ft_bzero(buf, 1024);
	while (!ft_strchr(" ;><|& \0", str[i]))
	{
		buf[j] = str[i];
		i++;
		j++;
	}
	return (ft_strdup(buf));
}

static char		*ft_add_insert(char *script)
{
	char		*str;
	char		buf[10240];
	int			fd;
	int			i;
	int			j;

	ft_bzero(buf, 10240);
	str = NULL;
	i = 0;
	fd = open(script, O_RDONLY);
	while (ft_gnl(fd, &str) > 0)
	{
		j = 0;
		buf[i] = ';';
		i++;
		while (str[j] && str[j] != '#')
		{
			buf[i] = str[j];
			i++;
			j++;
		}
	}
	buf[i] = ';';
	close(fd);
	return (ft_strdup(buf));
}

static void		ft_insert_script(char *to_insert, char *buf, int j)
{
	int			k;
	int			l;

	k = 0;
	l = j;
	while (to_insert[k])
	{
		buf[l] = to_insert[k];
		l++;
		k++;
	}
	buf[l] = ';';
}
