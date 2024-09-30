/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:25:33 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/23 18:05:06 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_target_dir(t_env **env, t_parser *parser, char **dir)
{
	if (parser->cmd[1] == NULL || ft_strncmp(parser->cmd[1], "~", 1) == 0)
	{
		*dir = find_value("HOME", *env);
		if (!*dir)
		{
			add_node_char("?", "1", false, env);
			ft_fprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
		}
		else if (parser->cmd[1] && parser->cmd[1][1])
			*dir = ft_joinf("%s%s", *dir, parser->cmd[1] + 1);
	}
	else if (ft_strcmp(parser->cmd[1], "-") == 0)
	{
		*dir = find_value("OLDPWD", *env);
		if (!*dir)
		{
			add_node_char("?", "1", false, env);
			ft_fprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
		}
		else
			printf("%s\n", *dir);
	}
	else
		*dir = parser->cmd[1];
}

static int	check_cd_error(t_env **env, t_parser *parser)
{
	if (parser->cmd[1] && parser->cmd[2])
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		add_node_char("?", "1", false, env);
		return (1);
	}
	return (0);
}

int	my_cd(t_env **env, t_parser *parser)
{
	char	*temp;

	if (check_cd_error(env, parser))
		return (1);
	get_target_dir(env, parser, &temp);
	if (!temp)
		return (1);
	if (chdir(temp) != 0)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", temp,
			strerror(errno));
		add_node_char("?", "1", false, env);
		return (1);
	}
	temp = ft_strjoinf("OLDPWD=", find_value("PWD", *env), 0);
	add_node(env, new_node(temp), 0);
	free(temp);
	temp = ft_strjoinf("PWD=", getcwd(NULL, 0), 2);
	add_node(env, new_node(temp), 0);
	free(temp);
	add_node_char("?", "0", false, env);
	return (0);
}
