/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:10:26 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/16 16:04:08 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	tokenize(char *content)
{
	if (ft_strlen(content) > 2)
		return (WORD);
	else if (ft_strcmp(content, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(content, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(content, "<") == 0)
		return (INPUT);
	else if (ft_strcmp(content, ">>") == 0)
		return (APPENDOUTPUT);
	else if (ft_strcmp(content, ">") == 0)
		return (OUTPUT);
	return (WORD);
}

t_lexer	*new_node_lexer(char *content, t_token tk, int i)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (0);
	new->token = tk;
	new->content = content;
	new->index = i;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*last_node(t_lexer *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

void	add_node_lexer(t_lexer **lst, t_lexer *newnode)
{
	t_lexer	*last;

	if (*lst)
	{
		last = last_node(*lst);
		last->next = newnode;
		newnode->prev = last;
	}
	else
		*lst = newnode;
}

void	lexer_init(t_lexer **lexer, char **split, t_env *env)
{
	char	*content;
	t_token	token;
	int		i;

	i = -1;
	while (split[++i])
	{
		content = NULL;
		token = tokenize(split[i]);
		if (!token)
		{
			content = clean_str(split[i], env);
			if (ft_strlen(content) == 0)
			{
				free(content);
				continue ;
			}
		}
		add_node_lexer(lexer, new_node_lexer(content, token, i));
	}
}
