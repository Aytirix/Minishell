/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:18:35 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/23 17:17:45 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_init(t_env **env, char **envp)
{
	t_env	*new;

	while (envp && *envp)
	{
		new = new_node(*envp);
		add_node(env, new, 1);
		++envp;
	}
	add_node_char("?", "0", false, env);
}

void	check_delete(t_env **env, t_env **cpy)
{
	t_env	*temp;
	t_env	*tcpy;
	t_env	*old;
	int		found;

	temp = *env;
	old = NULL;
	while (temp)
	{
		found = 0;
		tcpy = *cpy;
		while (tcpy && !found)
		{
			if (ft_strcmp(temp->name, tcpy->name) == 0)
				found = 1;
			tcpy = tcpy->next;
		}
		if (!found)
			if (remove_env_var(env, &old, &temp))
				continue ;
		old = temp;
		temp = temp->next;
	}
}
