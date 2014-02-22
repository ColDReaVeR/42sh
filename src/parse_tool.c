/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 17:17:20 by hestela           #+#    #+#             */
/*   Updated: 2014/02/22 17:19:08 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_get_redir_id(char *str)
{
	int		redir;

	if (*str == '>' && *str == *(str + 1))
		redir = 4;
	else if (*str == '<' && *str == *(str + 1))
		redir = 5;
	else if (*str == '&' && *str == *(str + 1))
		redir = 6;
	else if (*str == '|' && *str == *(str + 1))
		redir = 7;
	else if (*str == '|')
		redir = 1;
	else if (*str == '>')
		redir = 2;
	else if (*str == '<')
		redir = 3;
	else
		redir = 0;
	return (redir);
}
