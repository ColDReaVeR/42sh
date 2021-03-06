/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/11 14:14:12 by hestela           #+#    #+#             */
/*   Updated: 2013/12/12 13:21:37 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long		ft_itoo(long n)
{
	long	rem;
	long	i;
	long	octal;

	i = 1;
	octal = 0;
	while (n != 0)
	{
		rem = n % 8;
		n /= 8;
		octal += rem * i;
		i *= 10;
	}
	return (octal);
}
