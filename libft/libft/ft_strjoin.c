/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:14:10 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:32:04 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	i = 0;
	j = 0;
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (0);
	*joined = 0;
	if (!joined)
		return (NULL);
	while (s1[i++])
		joined[i - 1] = s1[i - 1];
	while (s2[j])
		joined[i++ - 1] = s2[j++];
	joined[i - 1] = 0;
	return (joined);
}
/*
int main(void)
{
	printf("%s", ft_strjoin("bonjour,", " aurevoir"));
}*/