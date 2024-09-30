/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:29:59 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/08 20:30:08 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen(int nb)
{
	int	res;

	res = 0;
	if (nb == -2147483648)
		return (11);
	else if (nb <= 0)
	{
		nb = -nb;
		res++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		res++;
	}
	return (res);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return (ft_putstr("(null)"));
	i = ft_strlen(s);
	write(1, s, i);
	return (i - 1);
}
