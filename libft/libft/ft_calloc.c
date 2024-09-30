/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:04:58 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:30:37 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if ((int)nmemb < 0 && (int)size < 0)
		return (NULL);
	tab = (void *)malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, nmemb * size);
	return (tab);
}
/*int main(void)
{
	printf("%p\n", ft_calloc(-5, -5));
}*/
