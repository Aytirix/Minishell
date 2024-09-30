/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:13:25 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:31:25 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*from;

	if (!dest && !src)
		return (NULL);
	dst = dest;
	from = src;
	if (dst < from)
	{
		while (n--)
			*dst++ = *from++;
	}
	else
	{
		while (n--)
			dst[n] = from[n];
	}
	return (dest);
}
/*
int main(void)
{
	char dest[]= "qqqqqicepsum dolor sit a";
	printf("%s",(char *)ft_memmove(dest,"consectetur", 5));
}*/