/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:24:39 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/10 16:28:30 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pass_args(t_parser *parser, int *i)
{
	int	j;

	while (parser->cmd[*i])
	{
		if (parser->cmd[*i][0] != '-' || parser->cmd[*i][1] != 'n')
			break ;
		j = 2;
		while (parser->cmd[*i][j] == 'n')
			j++;
		if (parser->cmd[*i][j] != '\0' && parser->cmd[*i][j] != 'n')
			break ;
		(*i)++;
	}
	if ((*i) == 1)
		return (1);
	return (0);
}

int	my_echo(t_env **env, struct s_parser *parser)
{
	int	i;
	int	back_slash_n;

	(void)env;
	i = 1;
	back_slash_n = pass_args(parser, &i);
	while (parser->cmd[i])
	{
		ft_printf("%s", parser->cmd[i]);
		if (parser->cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (back_slash_n)
		printf("\n");
	return (0);
}
