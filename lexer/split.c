/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:44:48 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/15 17:04:05 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words_lexer(char *s)
{
	int		i;
	int		res;
	t_flag	f;
	bool	flag;

	i = 0;
	res = 0;
	flag = 0;
	flag_variables_init(&f);
	while (s[i])
	{
		handle_backslash(s[i], &f.backslash);
		if (is_quote(s[i], f.backslash))
			handle_quotes(s[i], &f);
		if (is_token(s[i], f))
			i += handle_token(&res, (s + i), &flag);
		else if (!is_whitespace(s[i]))
			is_start_of_word(&res, f, &flag);
		else if (!(f.d_quote || f.sg_quote))
			flag = 0;
		i++;
	}
	if (f.d_quote || f.sg_quote)
		return (-1);
	return (res);
}

static char	*fill_str_with(const char *s, int start, int end)
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

void	skip_whitespaces(char *s, t_index *idx)
{
	while (s[idx->start] && is_whitespace(s[idx->start]))
		++idx->start;
	idx->end = idx->start - 1;
}

static void	split_loop(int size, char *s, char **split)
{
	t_flag	f;
	t_index	idx;
	int		i;

	i = 0;
	flag_variables_init(&f);
	idx.start = 0;
	while (i < size)
	{
		handle_backslash(s[idx.start], &f.backslash);
		skip_whitespaces(s, &idx);
		if (is_token(s[idx.start], f))
			idx.end += handle_token(NULL, (s + idx.start), NULL) + 2;
		else
		{
			while (s[++idx.end] && !is_token(s[idx.end], f)
				&& (!is_whitespace(s[idx.end]))
				&& handle_backslash(s[idx.end], &f.backslash))
				if (is_quote(s[idx.end], f.backslash))
					found_quote(&idx, s);
		}
		split[i++] = fill_str_with(s, idx.start, idx.end);
		idx.start = idx.end;
	}
}

char	**ft_split_lexer(char *s)
{
	char		**split;
	int			size;

	size = count_words_lexer(s);
	if (size == -1)
	{
		printf("Error: check your quotes\n");
		return (NULL);
	}
	split = malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	split_loop(size, s, split);
	split[size] = NULL;
	return (split);
}
