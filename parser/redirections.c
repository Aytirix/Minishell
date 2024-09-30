/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:03:16 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/11 16:37:34 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *error, t_parser_utils *utils)
{
	printf("%s\n", error);
	free_lexer(utils->lexer);
	free_parser(utils->parser);
}

void	rm_from_lexer(t_lexer **lexer, int index)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer	*next;

	node = *lexer;
	while (node && node->index != index)
		node = node->next;
	if (!node)
		return ;
	prev = node->prev;
	next = node->next;
	if (prev == NULL)
	{
		free(node);
		node = NULL;
		*lexer = next;
		if (next)
			(*lexer)->prev = NULL;
		return ;
	}
	node->prev->next = next;
	if (node->next)
		node->next->prev = prev;
	free(node);
	node = NULL;
}

void	add_new_redirection(t_lexer *to_add, t_lexer **lexer,
		t_parser_utils *utils)
{
	t_lexer	*newnode;
	int		i1;
	int		i2;

	newnode = new_node_lexer(to_add->next->content,
			to_add->token, utils->nb_of_redirections);
	if (!newnode)
		return (ft_error(MALLOC, utils));
	add_node_lexer(&utils->redirections, newnode);
	i1 = to_add->index;
	i2 = to_add->next->index;
	rm_from_lexer(lexer, i1);
	rm_from_lexer(lexer, i2);
	++utils->nb_of_redirections;
}

void	token_error(t_lexer *problem, t_parser_utils *utils)
{
	if (!problem)
		printf("%s `newline'\n", SYNTAX_ERROR);
	else
	{
		if (problem->token == INPUT)
			printf("%s `<'\n", SYNTAX_ERROR);
		else if (problem->token == OUTPUT)
			printf("%s `>'\n", SYNTAX_ERROR);
		else if (problem->token == HEREDOC)
			printf("%s `<<'\n", SYNTAX_ERROR);
		else if (problem->token == APPENDOUTPUT)
			printf("%s `>>'\n", SYNTAX_ERROR);
		else
			printf("%s `|'\n", SYNTAX_ERROR);
	}
	free_lexer(utils->lexer);
	free_parser(utils->parser);
}

void	detach_redirections(t_lexer **lexer, t_parser_utils *utils)
{
	t_lexer	*to_remove;

	if ((*lexer)->token == PIPE)
		to_remove = (*lexer)->next;
	else
		to_remove = *lexer;
	while (to_remove && to_remove->token == 0)
		to_remove = to_remove->next;
	if (!to_remove || (to_remove->token == PIPE
			&& to_remove->next && to_remove->next->token != PIPE))
		return ;
	if (!to_remove->next || to_remove->next->token)
		return (token_error(to_remove->next, utils));
	add_new_redirection(to_remove, lexer, utils);
	if (!(*lexer))
		return ;
	detach_redirections(lexer, utils);
}
