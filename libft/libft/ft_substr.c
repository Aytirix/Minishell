/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:14:56 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:33:39 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	slen;
	size_t	i;

	i = 0;
	slen = ft_strlen(s);
	if (start + len > slen)
	{
		if (start < slen)
			len = ft_strlen(s + start);
		else
			len = 0;
	}
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (len--)
		cpy[i++] = s[start++];
	cpy[i] = 0;
	return (cpy);
}
/*
int main(void)
{
	char *str = "i just want this part #############";
 	size_t size = 20;
 	printf("%s",ft_substr(str, 5, size));
}*/