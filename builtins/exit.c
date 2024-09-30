/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:11:23 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:38:54 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_exit_code(struct s_parser *parser, int exit_code)
{
	while (parser->cmd[1] && parser->cmd[1][exit_code])
	{
		if (!ft_isdigit(parser->cmd[1][exit_code])
			&& parser->cmd[1][exit_code] != '-'
			&& parser->cmd[1][exit_code] != '+')
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required\n",
				parser->cmd[1]);
			exit(2);
		}
		exit_code++;
	}
}

int	my_exit(t_env **env, struct s_parser *parser)
{
	int	exit_code;

	printf("exit\n");
	(void)env;
	exit_code = 0;
	check_exit_code(parser, 0);
	if (parser->cmd[1] && !parser->cmd[2])
	{
		exit_code = ft_atoi(parser->cmd[1]) % 256;
		if (exit_code < 0)
			exit_code = 256 + exit_code;
	}
	else if (parser->cmd[1] && parser->cmd[2])
	{
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
	else
		exit_code = 1;
	exit(exit_code);
	return (exit_code);
}
