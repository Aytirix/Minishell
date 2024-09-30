/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:59:47 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/15 17:04:41 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_quote(char c, int backslash)
{
	return ((c == '"' && backslash == 0) || c == '\'');
}

bool	is_token(char c, t_flag f)
{
	return ((c == '>' || c == '<' || c == '|')
		&& !f.backslash && !f.d_quote && !f.sg_quote);
}

int	handle_token(int *res, char *s, bool *flag)
{
	if (res && flag)
	{
		++*res;
		*flag = 0;
	}
	if (*s == *(s + 1))
		return (1);
	return (0);
}

void	flag_variables_init(t_flag *flag)
{
	flag->backslash = 0;
	flag->d_quote = 0;
	flag->sg_quote = 0;
}
