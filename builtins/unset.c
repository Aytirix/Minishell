/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:26:10 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/23 17:20:15 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	remove_env_var(t_env **env, t_env **old, t_env **temp)
{
	if (*old == NULL)
		*env = (*temp)->next;
	else
		(*old)->next = (*temp)->next;
	free((*temp)->name);
	free((*temp)->value);
	free(*temp);
	*temp = *env;
	if (*old == NULL)
		return (1);
	return (0);
}

int	my_unset(t_env **env, struct s_parser *psr)
{
	t_env	*old;
	t_env	*temp;
	int		i;

	temp = *env;
	old = NULL;
	i = 1;
	while (temp && psr->cmd[i])
	{
		if (ft_strcmp(psr->cmd[i], temp->name) == 0 && ft_strcmp(psr->cmd[i],
				"?") != 0)
		{
			if (remove_env_var(env, &old, &temp))
				continue ;
			if (psr->cmd[i++ + 1] == NULL)
			{
				add_node_char("?", "0", false, env);
				return (0);
			}
		}
		old = temp;
		temp = temp->next;
	}
	add_node_char("?", "0", false, env);
	return (0);
}
