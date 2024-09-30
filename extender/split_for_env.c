/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:07:19 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/15 15:07:48 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*fill_str_with(char const *s, int start, int end)
{
	char	*fill;
	int		i;

	i = 0;
	fill = malloc(sizeof(char) * (end - start + 1));
	if (!fill)
		return (NULL);
	while (start < end)
		fill[i++] = s[start++];
	fill[i] = 0;
	return (fill);
}

static int	sizeofsplit(const char *s)
{
	const char	*equal;

	equal = ft_strchr(s, '=');
	if (equal == NULL)
		return (1);
	else
		return (2);
}

char	**split_for_env(char const *s)
{
	char	**split;
	int		len;
	int		i;
	int		end;
	int		start;

	len = sizeofsplit(s);
	i = 0;
	start = 0;
	end = 1;
	split = malloc(sizeof(char *) * (len + 1));
	if (!split)
		return (NULL);
	while (s[end] && s[end] != '=')
		end++;
	while (i < len)
	{
		if (i != 0)
			while (s[end])
				end++;
		split[i++] = fill_str_with(s, start, end);
		start = end + 1;
	}
	split[i] = NULL;
	return (split);
}

char	**convert_env_tab(t_env *env)
{
	t_env	*tmp;
	char	**tab;
	int		i;

	i = 1;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		tab[i] = ft_strjoin(tmp->name, "=");
		tab[i] = ft_strjoinf(tab[i], tmp->value, 1);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}
