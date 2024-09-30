/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:26:02 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/17 16:43:15 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_export(t_env **env, struct s_parser *parser)
{
	int	i;

	i = 0;
	while (parser->cmd[++i])
	{
		if (add_node(env, new_node(parser->cmd[i]), 0))
		{
			add_node_char("?", "1", false, env);
			return (1);
		}
	}
	if (!parser->cmd[1])
		print_export(*env);
	return (0);
}

void	add_node_char(char *name, char *value, bool is_free, t_env **env)
{
	char	*temp;

	temp = ft_joinf("%s=%s", name, value);
	add_node(env, new_node(temp), 1);
	free(temp);
	if (is_free)
		free(value);
}

static void	index_export(t_env *env)
{
	t_env	*first_node;
	t_env	*to_index;
	int		index;

	first_node = env;
	to_index = env;
	while (to_index)
	{
		index = 0;
		while (env)
		{
			if (to_index != env && ft_strcmp(env->name, to_index->name) < 0)
				++index;
			env = env->next;
		}
		to_index->index = index;
		to_index = to_index->next;
		env = first_node;
	}
}

static void	print_line_export(t_env *env)
{
	int	i;

	i = 0;
	if (ft_strcmp(env->name, "?") != 0)
	{
		printf("declare -x %s", env->name);
		if (env->value)
		{
			printf("=\"");
			while (env->value[i])
			{
				if (ft_strchr("$\"\\`", env->value[i]))
					printf("\\");
				print_brut_format(env->value[i]);
				i++;
			}
			printf("\"");
		}
		printf("\n");
	}
}

void	print_export(t_env *env)
{
	t_env	*first_node;
	int		max;
	int		i;

	i = 0;
	first_node = env;
	index_export(env);
	max = max_index(env);
	while (i <= max)
	{
		if (env->index == i)
		{
			print_line_export(env);
			++i;
		}
		if (env->next == NULL)
			env = first_node;
		else
			env = env->next;
	}
}
