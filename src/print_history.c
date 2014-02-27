/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 17:03:49 by hestela           #+#    #+#             */
/*   Updated: 2014/02/24 19:59:33 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "42sh.h"

static int		ft_list_len(t_histo *list);
static void		ft_print_history(t_histo *list);

void			ft_history(char **av)
{
	int			nb;
	t_histo		*list;
	int			len;
	int			i;

	i = 0;
	list = g_env.histo->start;
	len = ft_list_len(list);
	if (av[1] && av[1][0] == '-' && ft_isdigit(av[1][1]))
		nb = ft_atoi(av[1] + 1);
	else
		nb = 20;
	if (len - nb <= 0)
		ft_print_history(list);
	else
	{
		while (i < len - nb - 1)
		{
			list = list->next;
			i++;
		}
		ft_print_history(list);
	}
}

static int		ft_list_len(t_histo *list)
{
	int			len;

	len = 0;
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}

static void		ft_print_history(t_histo *list)
{
	while (list->next)
	{
		ft_putendl(list->line);
		list = list->next;
	}
}
