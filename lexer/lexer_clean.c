/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:40:28 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/06 19:20:11 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_lexer	*update_indexes(t_lexer *lexer)
{
	t_lexer	*first_node;
	int		i;

	i = 0;
	first_node = lexer;
	while (lexer)
	{
		lexer->index = i++;
		lexer = lexer->next;
	}
	return (first_node);
}

t_lexer	*delete_empty_nodes(t_lexer *lexer)
{
	t_lexer	*temp;
	t_lexer	*first_node;

	first_node = lexer;
	while (lexer)
	{
		temp = lexer->next;
		if (lexer->token == 0 && lexer->content[0] == '\0')
		{
			if (lexer->index == 0)
				first_node = update_indexes(lexer->next);
			free(lexer->content);
			if (lexer->prev != NULL)
				lexer->prev->next = lexer->next;
			if (lexer->next != NULL)
				lexer->next->prev = lexer->prev;
			free(lexer);
		}
		lexer = temp;
	}
	return (first_node);
}
