/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 18:41:05 by hestela           #+#    #+#             */
/*   Updated: 2013/11/27 10:41:36 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strequ(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 == *s2)
	{
		if (!*s1)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}
