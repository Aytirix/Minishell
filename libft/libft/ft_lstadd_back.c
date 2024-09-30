/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:06:52 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:30:55 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
/*
int main(void)
{
	t_list *l = ((void*)0);
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
	ft_lstadd_back(&l, n);
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

//gcc -Wall -Wextra -Werror ft_lstadd_back.c ft_lstnew.c 
ft_strdup.c print_lst.c ft_strlen.c ft_lstlast.c
}*/