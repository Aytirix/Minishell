/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:06:57 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:30:57 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
int main(void)
{
	t_list *l = ft_lstnew(ft_strdup("nyacat"));
 	t_list *n = ft_lstnew(ft_strdup("OK"));

	if (l == NULL)
	{
		printf("Liste vide !\n");
	}
	while (l != NULL)
	{
		printf("[%s] ", (char *)l->content);
		l = l->next;
	}
	printf("\n");
	ft_lstadd_front(&l, n);
	if (l == NULL)
	{
		printf("Liste vide !\n");
	}
	while (l != NULL)
	{
		printf("[%s] ", (char *)l->content);
		l = l->next;
	}
	printf("\n");
}*/