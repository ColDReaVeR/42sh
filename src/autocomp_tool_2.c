/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp_tool_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 03:59:42 by hestela           #+#    #+#             */
/*   Updated: 2014/02/21 10:13:23 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

char			*ft_get_comp_path(char *begin)
{
	char		buf[1024];
	int			i;
	int			j;

	i = 0;
	j = 0;
	ft_bzero(buf, 1024);
	while (begin[i])
	{
		if (begin[i] != '\\')
		{
			buf[j] = begin[i];
			j++;
		}
		i++;
	}
	while (buf[j] != '/')
	{
		buf[j] = '\0';
		j--;
	}
	return (ft_strdup(buf));
}

char			*ft_get_comp_rest(char *begin)
{
	char		buf[1024];
	int			i;
	int			j;

	ft_bzero(buf, 1024);
	i = ft_strlen(begin);
	j = 0;
	while (begin[i] != '/')
		i--;
	i++;
	while (begin[i])
	{
		if (begin[i] != '\\')
		{
			buf[j] = begin[i];
			i++;
		}
		j++;
	}
	buf[j] = '*';
	return (ft_strdup(buf));
}

void			ft_rewrite_path(char **new, char *path)
{
	char		buf[10240];
	char		*ptr;
	char		*str;
	int			i;

	i = 0;
	str = *new;
	ft_bzero(buf, 10240);
	ptr = ft_strstr(str, path);
	while (str++ != ptr && i++ >= 0)
		buf[i - 1] = *(str - 1);
	ptr += ft_strlen(path);
	while (*path)
	{
		if (*path == ' ' && i++ >= 0)
			buf[i - 1] = '\\';
		buf[i] = *path;
		path++;
		i++;
	}
	while (*ptr && i++ >= 0 && ptr++)
		buf[i - 1] = *(ptr - 1);
	free(*new);
	*new = ft_strdup(buf);
}
