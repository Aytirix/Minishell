/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:14:23 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:32:11 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < (size - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (ft_strlen(src));
}
/*
int main(void)
{
	char dst[30] = "";
	char *src = "lorem ipsum dolor sit amet";

	ft_memset(dst, 'A', 30);
	printf("%s\n", dst);
	printf("%ld\n", ft_strlcpy(dst, src, 0));
	printf("%s\n", dst);
}*/