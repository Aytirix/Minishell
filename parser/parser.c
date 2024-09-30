/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:30:11 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/11 16:31:33 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	(*is_builtin(char **cmd))(t_env **env, struct s_parser *parser)
{
	if (cmd == NULL || cmd[0] == NULL)
		return ((void *)0);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (my_echo);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (my_cd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (my_pwd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (my_export);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (my_unset);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (my_env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (my_exit);
	return ((void *)0);
}

static t_parser	*new_node_parser(t_lexer *lexer, t_parser_utils *utils)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (0);
	new->redirections = utils->redirections;
	new->nb_of_redirections = utils->nb_of_redirections;
	new->cmd = build_command(lexer);
	new->builtin = is_builtin(new->cmd);
	new->pid = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static t_parser	*last_node(t_parser *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

static void	add_node_parser(t_parser **lst, t_parser *newnode)
{
	t_parser	*last;

	if (*lst)
	{
		last = last_node(*lst);
		last->next = newnode;
		newnode->prev = last;
	}
	else
		*lst = newnode;
}

void	parser_init(t_parser **parser, t_lexer **lexer, t_parser_utils *utils)
{
	t_lexer	*lxr;
	int		i;
	int		cmds;

	i = 0;
	lxr = *lexer;
	cmds = count_pipes(lxr) + 1;
	while (cmds--)
	{
		utils->redirections = NULL;
		utils->nb_of_redirections = 0;
		detach_redirections(&lxr, utils);
		if (*utils->lexer == NULL)
			return ;
		if (!i++)
			*lexer = lxr;
		else
			lxr = lxr->next;
		add_node_parser(parser, new_node_parser(lxr, utils));
		if (cmds == 0)
			break ;
		while (lxr->token != PIPE)
			lxr = lxr->next;
	}
	free_lexer(lexer);
}
