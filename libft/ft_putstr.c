/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 09:26:24 by hestela           #+#    #+#             */
/*   Updated: 2014/02/19 03:21:55 by msommagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

int		ft_putstr(char const *s)
{
	if (s)
		return (write(1, s, ft_strlen(s)));
	else
		return (write(1, "(null)", 6));
}
