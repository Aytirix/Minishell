/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:09:00 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/23 17:19:27 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	lexer_parser(t_parser **parser, char *str, t_env *env)
{
	t_lexer			*lexer_list;
	t_parser_utils	utils;

	lexer_list = NULL;
	lexer(&lexer_list, str, env);
	if (lexer_list == NULL)
		return ;
	utils.lexer = &lexer_list;
	utils.parser = parser;
	parser_init(parser, &lexer_list, &utils);
	if (DEBUG)
		print_parser(*parser);
}

static char	*print_line(t_env *env)
{
	char	*str;
	char	*tmp;

	tmp = find_value("USER", env);
	if (tmp)
		str = ft_joinf("%s%s%s", BOLD_GREEN, tmp, RESET_COLOR);
	else
		str = ft_strdup("");
	tmp = find_value("PWD", env);
	if (tmp)
	{
		if (ft_strncmp(tmp, "/home/", 6) == 0)
			str = ft_joinf("$s:%s~%s", &str, BOLD_BLUE, ft_strchr(tmp + 6,
						'/'));
		else
			str = ft_joinf("$s:%s/%s", &str, BOLD_BLUE, tmp + 1);
	}
	str = ft_joinf("$s%s$$ ", &str, RESET_COLOR);
	tmp = readline(str);
	free(str);
	return (tmp);
}

void	minishell(t_env **env, int saved_stin, int saved_stout)
{
	t_parser	*parser_list;
	char		*str;

	str = NULL;
	parser_list = NULL;
	while (1)
	{
		if (str)
			free(str);
		str = print_line(*env);
		if (str == NULL)
			break ;
		add_history(str);
		lexer_parser(&parser_list, str, *env);
		if (parser_list == NULL)
			continue ;
		executor(env, parser_list);
		dup2(saved_stin, STDIN_FILENO);
		dup2(saved_stout, STDOUT_FILENO);
		free_parser(&parser_list);
	}
	free(str);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		saved_stin;
	int		saved_stout;

	env = NULL;
	saved_stin = dup(STDIN_FILENO);
	saved_stout = dup(STDOUT_FILENO);
	(void)av;
	(void)envp;
	if (ac > 1)
	{
		ft_fprintf(2, "minishell requires no arguments\n");
		exit(EXIT_FAILURE);
	}
	env_init(&env, envp);
	set_signal_action(sigint_handler);
	minishell(&env, saved_stin, saved_stout);
	envclear(&env);
}
