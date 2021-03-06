/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 00:09:56 by hestela           #+#    #+#             */
/*   Updated: 2014/02/27 15:45:45 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termcap.h>
#include "libft.h"
#include "42sh.h"

static void		ft_get_alias_list(void);
static void		ft_add_node(char *str);
static void		ft_create_node(char *alias, char *string);
static void		ft_get_history(void);

void			ft_init(void)
{
	char		buf[1024];
	char		histo_path[1024] = {0};

	ioctl(1, TIOCGWINSZ, &g_ws);
	signal(SIGWINCH, ft_resize);
	g_env.alias_lst = NULL;
	g_env.quote_wait = 0;
	signal(SIGINT, SIG_IGN);
	g_env.pid_list = NULL;
	g_env.cut = NULL;
	g_env.histo = NULL;
	ft_get_alias_list();
	if (tgetent(buf, ft_getenv(g_env.env, "TERM")) == -1)
		exit(EXIT_FAILURE);
	tcgetattr(0, &g_env.term);
	g_env.term.c_lflag &= ~(ICANON | ECHO | ISIG);
	g_env.term.c_cc[VMIN] = 1;
	g_env.term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &g_env.term);
	ft_strcpy(histo_path, ft_getenv(g_env.env, "HOME"));
	ft_strcat(histo_path, "/.42sh_histo");
	g_env.histo_fd = open(histo_path, O_CREAT | O_RDWR, 0777);
	ft_get_history();
}

static void		ft_get_history(void)
{
	char		*str;
	int			i;

	str = NULL;
	while (ft_gnl(g_env.histo_fd, &str) > 0)
	{
		i = 0;
		if (str[i] == ':' && str[i + 1] == ' ' && ft_isdigit(str[i + 2]))
		{
			while (ft_strncmp(str + i, ":0;", 3) && str + i)
				i++;
			if (str + i == '\0')
				ft_update_history(str, 1);
			else
				ft_update_history(str + i + 3, 1);
		}
		else
			ft_update_history(str, 1);
	}
	free(str);
}

static void		ft_get_alias_list(void)
{
	int			i;
	int			fd;
	char		*tmp;
	char		*path;

	tmp = ft_strjoin(ft_getenv(g_env.env, "HOME"), "/");
	path = ft_strjoin(tmp, ".bashrc");
	fd = open(path, O_RDONLY);
	free(tmp);
	tmp = NULL;
	while (ft_gnl(fd, &tmp) > 0)
	{
		i = 0;
		while (*(tmp + i) == ' ' || *(tmp + i) == '\t')
			i++;
		if (!ft_strncmp(tmp + i, "alias ", 6))
			ft_add_node(tmp + i);
	}
	if (g_env.alias_lst)
		g_env.alias_lst = g_env.alias_lst->start;
	free(path);
	free(tmp);
}

static void		ft_add_node(char *str)
{
	char		alias[50];
	char		string[200];
	int			i;

	i = 0;
	while (*str && *str != ' ')
		str++;
	str++;
	while (*str != '=')
	{
		alias[i] = *str;
		i++;
		str++;
	}
	str += 2;
	alias[i] = '\0';
	i = 0;
	while (*str != '\'' && *str)
	{
		string[i] = *str;
		str++;
		i++;
	}
	string[i] = '\0';
	ft_create_node(alias, string);
}

static void		ft_create_node(char *alias, char *string)
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
	g_env.alias_lst->next = malloc(sizeof(t_alias_lst));
	g_env.alias_lst = g_env.alias_lst->next;
	g_env.alias_lst->next = NULL;
	g_env.alias_lst->start = start;
	g_env.alias_lst->alias = ft_strdup(alias);
	g_env.alias_lst->string = ft_strdup(string);
}
