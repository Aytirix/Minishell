/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:38 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/17 16:21:15 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*new_node(void *content)
{
	t_env	*new;
	char	**line;

	if (!content)
		return (0);
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	line = split_for_env(content);
	new->index = 0;
	new->name = ft_strdup(line[0]);
	if (line[1] && ft_strlen(line[1]) > 0)
		new->value = ft_strdup(line[1]);
	else if (line[1] && ft_strlen(line[1]) == 0)
		new->value = ft_strdup("");
	else
		new->value = NULL;
	new->next = NULL;
	free_tab(line);
	return (new);
}

static t_env	*last_node(t_env *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

int	max_index(t_env *env)
{
	int	max;

	max = 0;
	while (env)
	{
		if (env->index > max)
			max = env->index;
		env = env->next;
	}
	return (max);
}

int	add_node(t_env **lst, t_env *nw, int force)
{
	int		i;
	t_env	*last;

	i = -1;
	while (nw && nw->name[++i] && !force)
	{
		if ((i == 0 && ft_isdigit(nw->name[i])) || (!ft_isalnum(nw->name[i])
				&& nw->name[i] != '_'))
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: export: `$s=$s': not a valid identifier\n",
				&nw->name, &nw->value);
			free(nw);
			return (1);
		}
	}
	i = env_edit(lst, nw);
	if (nw && !i && *lst)
	{
		last = last_node(*lst);
		last->next = nw;
	}
	else if (nw && !i)
		*lst = nw;
	return (0);
}
