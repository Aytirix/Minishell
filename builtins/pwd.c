/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:25:50 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:38:59 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_pwd(t_env **env, struct s_parser *parser)
{
	t_env	*tmp;

	(void)parser;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
		{
			ft_printf("%s\n", tmp->value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}
