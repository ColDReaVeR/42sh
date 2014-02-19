/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 09:31:57 by hestela           #+#    #+#             */
/*   Updated: 2014/02/19 03:21:25 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

int		ft_putstr_fd(char const *s, int fd)
{
	if (s)
		return (write(fd, s, ft_strlen(s)));
	else
		return (write(fd, "(null)", 6));
}
