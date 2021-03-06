/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/28 10:08:01 by hestela           #+#    #+#             */
/*   Updated: 2014/02/25 15:40:41 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "42sh.h"

static void		ft_update_cmd(char *line);
static void		ft_exec_list(t_cmd *list);
static void		ft_exec_redir(char *cmd1, char *cmd2, int redir);
static void		ft_del_list(t_cmd *list);

int				main(void)
{
	char		str[ARG_MAX] = {0};
	t_cmd		*list;

	ft_check_env();
	list = NULL;
	ft_init();
	while (1)
	{
		ft_check_position();
		g_prompt_len = ft_printf("%$%s 42sh (%T)%% "\
			, PROMPT_CLR, ft_getenv(g_env.env, "USER"));
		g_env.in_histo = 0;
		ft_update_cmd(str);
		ft_update_history(str, 0);
		ft_do_replacements(str);
		list = ft_parser(str);
		ft_exec_list(list);
		ft_del_list(list);
		ft_bzero(str, ft_strlen(str));
	}
	return (0);
}

static void		ft_update_cmd(char *line)
{
	int			bool;
	char		tmp[ARG_MAX] = {0};
	char		tmp2[ARG_MAX] = {0};

	bool = 0;
	while (ft_check_quote(line) || !bool)
	{
		if (*line)
			ft_strcpy(tmp, line);
		else
			ft_bzero(tmp, ft_strlen(tmp));
		if (*tmp)
			ft_strcat(tmp, "\n");
		ft_get_input(line);
		ft_strcpy(tmp2, line);
		ft_strcpy(line, tmp);
		ft_strcat(line, tmp2);
		bool = 1;
	}
	ft_printf("%$", TEXT_CLR);
}

static void		ft_exec_list(t_cmd *list)
{
	char		**av;

	av = NULL;
	while (list)
	{
		if (list->redir == 0)
		{
			av = ft_split_args(list->line, 0);
			if (!ft_builtin(av))
				ft_exec(av, g_env.env);
			ft_array_str_free(av);
			list = list->next;
		}
		else
		{
			ft_exec_redir(list->line, list->next->line, list->redir);
			list = list->next->next;
		}
	}
}

static void		ft_exec_redir(char *cmd1, char *cmd2, int redir)
{
	char		**av1;
	char		**av2;
	void		(*f[7])(char**, char**, char**);

	if (ft_is_empty(cmd1) || ft_is_empty(cmd2))
	{
		ft_printf_fd(2, "%$42sh: parse error%$\n", ERROR_CLR, TEXT_CLR);
		return ;
	}
	f[0] = &ft_exec_pipe;
	f[1] = &ft_exec_right;
	f[2] = &ft_exec_left;
	f[3] = &ft_exec_right_d;
	f[4] = &ft_exec_left_d;
	f[5] = &ft_exec_and;
	f[6] = &ft_exec_or;
	av1 = ft_split_args(cmd1, 0);
	av2 = ft_split_args(cmd2, 0);
	f[redir - 1](av1, av2, g_env.env);
	ft_array_str_free(av1);
	ft_array_str_free(av2);
}

static void		ft_del_list(t_cmd *list)
{
	t_cmd		*node;

	while (list)
	{
		node = list;
		list = list->next;
		free(node->line);
		free(node);
	}
}
