/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:17:32 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/16 16:46:42 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_redirections(t_lexer *redirections, int nb)
{
	printf("\n%d redirections :\n", nb);
	while (redirections)
	{
		printf("	%d- {%d} %s\n", redirections->index + 1,
			redirections->token,
			redirections->content);
		redirections = redirections->next;
	}
	printf("\n");
}

void	print_parser(t_parser *parser)
{
	int	i;

	while (parser)
	{
		i = 0;
		printf("\n");
		printf("command : ");
		if (parser->cmd)
		{
			while (parser->cmd[i])
				printf("[%s] ", parser->cmd[i++]);
		}
		else
			printf("NULL");
		print_redirections(parser->redirections, parser->nb_of_redirections);
		parser = parser->next;
	}
}
