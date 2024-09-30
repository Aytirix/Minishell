/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:22:17 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/22 16:23:06 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	envclear(t_env **lst)
{
	t_env	*temp;

	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free((*lst)->name);
		free((*lst)->value);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
