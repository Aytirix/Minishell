/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:25:45 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/14 14:10:39 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*temp;

	while (*lexer)
	{
		temp = (*lexer)->next;
		free((*lexer)->content);
		free(*lexer);
		*lexer = temp;
	}
	*lexer = NULL;
}

void	print_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		printf("NULL\n");
	while (lexer)
	{
		printf("content: [%s]\n", lexer->content);
		printf("token: [%d]\n", lexer->token);
		lexer = lexer->next;
	}
}
