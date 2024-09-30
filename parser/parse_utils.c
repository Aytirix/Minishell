/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:18:21 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/11 16:34:04 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_nodes(t_lexer *lexer)
{
	int	res;

	res = 0;
	while (lexer && lexer->token != PIPE)
	{
		++res;
		lexer = lexer->next;
	}
	return (res);
}

int	count_pipes(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		if (lexer->token == PIPE)
			++i;
		lexer = lexer->next;
	}
	return (i);
}

char	**build_command(t_lexer *lexer)
{
	char	**cmd;
	int		i;
	int		len;

	i = -1;
	if (!lexer)
		return (NULL);
	len = count_nodes(lexer);
	cmd = malloc(sizeof(char *) * (len + 1));
	while (++i < len)
	{
		cmd[i] = ft_strdup(lexer->content);
		lexer = lexer->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
