/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:44:28 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/16 16:35:47 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parser(t_parser **parser)
{
	t_parser	*temp;

	while (*parser)
	{
		temp = (*parser)->next;
		if ((*parser)->cmd)
			free_tab((*parser)->cmd);
		free_lexer(&(*parser)->redirections);
		free(*parser);
		*parser = temp;
	}
	*parser = NULL;
}
