/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 03:50:46 by hestela           #+#    #+#             */
/*   Updated: 2014/02/17 12:29:58 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <dirent.h>
#include "libft.h"
#include "42sh.h"

static char		*ft_add_list_2(char **ln, int *ps);
static char		*ft_comp_file_2(char *beg);

void			ft_comp_current_dir(char **ln, int *ps, int pv, int *comp)
{
	char		buf[2048];

	ft_bzero(buf, 2048);
	if (!g_comp_lst)
		ft_add_comp_list("./", "*");
	if (g_comp_lst)
	{
		ft_comp_path(ln, pv, buf);
		if (!g_comp_lst->next)
			g_comp_lst = g_comp_lst->start;
		else
			g_comp_lst = g_comp_lst->next;
		ft_comp_refresh(ln, buf, ps, pv);
		*comp = 1;
	}
	else
	{
		ft_putchar(7);
		*comp = 0;
	}
}

void			ft_comp_file(char **ln, int *ps, int pv, int *comp)
{
	static char		*path;

	if (!g_comp_lst)
	{
		if (path)
			free(path);
		path = ft_add_list_2(ln, ps);
	}
	if (!g_comp_lst)
	{
		ft_putchar(7);
		*comp = 0;
	}
	else
	{
		ft_comp_file_3(ln, pv, ps, path);
		*comp = 1;
	}
}

static char		*ft_add_list_2(char **ln, int *ps)
{
	char		begin[1024];
	int			i;
	char		*path;

	i = 0;
	ft_bzero(begin, 1024);
	while (ln[0][*ps] && !ft_strchr(" ;><&|", ln[0][*ps]))
	{
		begin[i] = ln[0][*ps];
		i++;
		ft_move_right(ps, *ln);
	}
	path = ft_comp_file_2(begin);
	return (path);
}

static char		*ft_comp_file_2(char *beg)
{
	char		*path;
	char		*to_comp;
	char        *newpath;

	if (!ft_strchr(beg, '/'))
		to_comp = ft_strjoin(beg, "*");
	else
		to_comp = ft_get_comp_rest(beg);
	path = (ft_strchr(beg, '/') ? ft_get_comp_path(beg) : NULL);
	if (path)
	{
		if (path[0] == '~' && path[1] == '/')
			newpath = ft_str_multi_join(3, ft_getenv(g_env.env, "HOME")\
				, "/", path + 2);
		else
			newpath = ft_strdup(path);
		ft_add_comp_list(newpath, to_comp);
		free(newpath);
	}
	else
		ft_add_comp_list("./", to_comp);
	free(to_comp);
	return (path);
}
