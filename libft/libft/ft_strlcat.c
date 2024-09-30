/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:14:18 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:32:09 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;
	size_t	j;

	i = 0;
	srclen = ft_strlen(src);
	j = ft_strlen(dst);
	if (size <= j)
		return (size + srclen);
	while (src[i] && j + 1 < size)
		dst[j++] = src[i++];
	dst[j] = 0;
	return (ft_strlen(src + i) + j);
}
/*
int main(void)
{
	char dst[19] ="pqrstuvwxyz";
	char src[] = "abcd";
	printf("%ld",ft_strlcat(dst, src, 20));
}*/