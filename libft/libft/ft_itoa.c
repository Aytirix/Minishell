/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:05:46 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:30:51 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	solve(int n, char **str, int len, int baselen)
{
	while (len-- > 0 && (*str)[len] != '-')
	{
		if (n < 0)
			(*str)[len] = -(n % baselen) + '0';
		else
			(*str)[len] = n % baselen + '0';
		n /= baselen;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		nb;

	len = 0;
	nb = n;
	if (n < 0 || n == 0)
		len++;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	str = (char *)ft_calloc(sizeof(char), len + 1);
	if (!(str))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	solve(n, &str, len, 10);
	return (str);
}

char	*ft_itoa_base(int n, char *base)
{
	char	*str;
	int		len;
	int		nb;
	int		baselen;

	len = 0;
	nb = n;
	baselen = ft_strlen(base);
	if (n < 0 || n == 0)
		len++;
	while (nb != 0)
	{
		nb /= baselen;
		len++;
	}
	str = (char *)ft_calloc(sizeof(char), len + 1);
	if (!(str))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	solve(n, &str, len, baselen);
	return (str);
}
