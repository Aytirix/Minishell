/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:03:31 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/16 16:10:46 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	malloc_error(t_lexer *list)
{
	while (list)
	{
		if (list->token == 0 && list->content == NULL)
		{
			printf("%s\n", MALLOC);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

void	lexer(t_lexer **list, char *str, t_env *env)
{
	char	**split;

	split = ft_split_lexer(str);
	if (split == NULL)
		return ;
	lexer_init(list, split, env);
	if (malloc_error(*list))
		free_lexer(list);
	free_tab(split);
	if (*list == NULL)
		return ;
}
