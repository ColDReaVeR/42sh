/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 19:22:55 by hestela           #+#    #+#             */
/*   Updated: 2014/02/21 14:23:29 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>
#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

static void		ft_restore_term_for_exec(char *cmd, int *status);
static void		ft_exec_suite(char *cmd, char **av, char **env, int *status);
static int		ft_builtin_suite(char **av);

void			ft_exec(char **av, char **env)
{
	char		*tmp;
	char		*cmd;
	int			status;
	
	tmp = NULL;
	tmp = ft_strjoin("/", av[0]);
	free(av[0]);
	av[0] = ft_strdup(tmp);
	free(tmp);
	cmd = ft_check_exist(av[0]);
	if (cmd)
		ft_exec_suite(cmd, av, env, &status);
	free(cmd);
}

static void		ft_exec_suite(char *cmd, char **av, char **env, int *status)
{
	char		*str;
	char		*new;

	str = ft_strdup(av[0]);
	free(av[0]);
	av[0] = ft_strdup(cmd);
	g_env.thread = fork();
	if (g_env.thread == 0)
	{
		g_env.in_exec = NULL;
		execve(cmd, av, env);
	}
	else
	{
		new = ft_str_multi_join(3, str + 1, " ", av[1]);
		ft_restore_term_for_exec(new, status);
		free(new);
	}
	free(str);
}

static void		ft_restore_term_for_exec(char *cmd, int *status)
{
	g_env.term->c_lflag |= ICANON;
	g_env.term->c_lflag |= ECHO;
	g_env.term->c_lflag |= ISIG;
	signal(SIGINT, ft_kill);
	tcsetattr(0, 0, g_env.term);
	g_env.in_exec = cmd;
	if (ft_strncmp(g_env.in_exec, "emacs", 5) == 0)
		ft_putstr(C_RESET);
	waitpid(g_env.thread, status, WUNTRACED);
	if (!*status)
		g_env.prev_status = *status;
	else
		g_env.prev_status = (*status == 256 ? 1 : 18);
	g_env.in_exec = NULL;
	tcgetattr(0, g_env.term);
	g_env.term->c_lflag &= ~(ICANON);
	g_env.term->c_lflag &= ~(ECHO);
	g_env.term->c_lflag &= ~(ISIG);
	g_env.term->c_cc[VMIN] = 1;
	g_env.term->c_cc[VTIME] = 0;
	tcsetattr(0, 0, g_env.term);
	signal(SIGINT, SIG_IGN);
}

int				ft_builtin(char **av)
{
	if (ft_strcmp_case("env", av[0]) == 0)
		ft_env(av, g_env.env);
	else if (ft_strcmp_case("echo", av[0]) == 0)
		ft_echo(av);
	else if (ft_strcmp_case("cd", av[0]) == 0)
		ft_cd(av, g_env.env);
	else if (ft_strcmp_case("unsetenv", av[0]) == 0)
	{
		g_env.env = ft_unsetenv(av, g_env.env);
		ft_env_changes();
	}
	else if (ft_strcmp_case("setenv", av[0]) == 0)
	{
		g_env.env = ft_setenv(av, g_env.env);
		ft_env_changes();
	}
	else if (!ft_builtin_suite(av)) 
		return (0);
	return (1);
}

static int		ft_builtin_suite(char **av)
{
	if (ft_strcmp_case("exit", av[0]) == 0)
		ft_exit(av, 1);
	else if (ft_strcmp_case("fg", av[0]) == 0)
		ft_resume(av);
	else if (ft_strcmp_case("jobs", av[0]) == 0)
		ft_print_job_list();
	else if (ft_strcmp_case("export", av[0]) == 0)
	{
		g_env.env = ft_export(av, g_env.env);
		ft_env_changes();
	}		
	else if (ft_strcmp_case("unset", av[0]) == 0)
	{
		g_env.env = ft_unsetenv(av, g_env.env);
		ft_env_changes();
	}
	else
		return (0);
	return (1);
}
