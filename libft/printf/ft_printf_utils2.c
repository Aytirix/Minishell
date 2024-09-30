/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:54:33 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:22:29 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_adress(unsigned long long p)
{
	int	len;

	len = 0;
	if (p == 0)
		return (ft_putstr("(nil)"));
	len += ft_putstr("0x");
	len += ft_putnbrbase(p, "0123456789abcdef", 16);
	return (len);
}

int	ft_putnbrbase(unsigned long long n, char *base, unsigned int lenbase)
{
	int	len;

	len = 0;
	if (n < (unsigned long long)lenbase)
		return (ft_putchar(base[n]));
	else
	{
		len = ft_putnbrbase(n / lenbase, base, lenbase) + 1;
		ft_putnbrbase(n % lenbase, base, lenbase);
	}
	return (len);
}

int	ft_putnbr(int n)
{
	int	len;

	len = ft_nbrlen(n);
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	else if (n >= 0 && n <= 9)
	{
		ft_putchar(n + '0');
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putchar((n % 10) + '0');
	}
	return (len);
}

int	ft_putuinbr(unsigned int n)
{
	int	i;

	i = 0;
	if (n <= 9)
		ft_putchar(n + '0');
	else
	{
		i = ft_putuinbr(n / 10);
		ft_putchar((n % 10) + '0');
	}
	return (i + 1);
}
