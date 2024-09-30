/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:14:52 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:32:29 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*clean;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (s1[start] != 0)
	{
		while (s1[end] && ft_strchr(set, s1[end]))
			end--;
	}
	clean = ft_substr(s1, start, end - start + 1);
	return (clean);
}
/*
int main(void)
{
	printf("%s", ft_strtrim(" > x> x  x hello    !        ","x >"));
}*/