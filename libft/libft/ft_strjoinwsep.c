/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinwsep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:10:57 by dren              #+#    #+#             */
/*   Updated: 2024/05/13 19:05:34 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	total_len(char **strs, char *sep, int size)
{
	int	joined_len;
	int	sep_len;
	int	i;

	i = 0;
	joined_len = 0;
	sep_len = ft_strlen(sep);
	while (i < size)
	{
		joined_len += ft_strlen(strs[i]);
		if (i != size - 1)
			joined_len += sep_len;
		i++;
	}
	return (joined_len);
}

char	*ft_strjoinwsep(int size, char **strs, char *sep)
{
	char	*big_str;
	int		i;

	i = 0;
	if (size == 0 || !strs || !sep)
		return (ft_strdup(""));
	big_str = malloc(sizeof(char) * (total_len(strs, sep, size) + 1));
	big_str[0] = '\0';
	while (i < size)
	{
		big_str = ft_strcat(big_str, strs[i++]);
		if (i != size)
			big_str = ft_strcat(big_str, sep);
	}
	return (big_str);
}
