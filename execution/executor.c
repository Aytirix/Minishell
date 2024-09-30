/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/07/17 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	redirect(t_exe *exe, t_parser *cmd)
{
	int		res;
	t_lexer	*tmp;

	res = 0;
	tmp = cmd->redirections;
	if (!tmp)
		return (redirect_pipe(exe, cmd, 2));
	while (tmp)
	{
		if (tmp->token == INPUT || tmp->token == HEREDOC)
			res = redirect_input(exe, tmp);
		else
			res = redirect_pipe(exe, cmd, 0);
		if (res != 0)
			break ;
		if (tmp->token == OUTPUT || tmp->token == APPENDOUTPUT)
			res = redirect_output(exe, tmp);
		else
			res = redirect_pipe(exe, cmd, 1);
		if (res != 0)
			break ;
		tmp = tmp->next;
	}
	add_node_char("?", ft_itoa(exe->error), true, exe->env);
	return (res);
}

static int	execute_child(t_exe *exe, t_parser *cmd, bool is_exit)
{
	int	res;

	res = redirect(exe, cmd);
	if (res == 0 && cmd->builtin)
		res = cmd->builtin(exe->env, cmd);
	else if (res == 0 && cmd->cmd && cmd->cmd[0])
	{
		res = check_path(exe, cmd);
		if (res == 0)
		{
			if (exe->fd[0] != STDIN_FILENO)
				exe->fd[0] = close(exe->fd[0]);
			res = execve(exe->path, cmd->cmd, exe->env_tab);
			if (res == -1)
				res = free_exe(exe, 0, 1, "1");
		}
	}
	exe->fd[1] = close(exe->fd[1]);
	if (is_exit)
		exit(res);
	return (res);
}

static void	execute_pipeline(t_exe *exe, t_parser *cmd)
{
	if (cmd->cmd && cmd->cmd[0])
	{
		if (!cmd->next && !cmd->prev && cmd->builtin)
		{
			add_node_char("?", ft_itoa(execute_child(exe, cmd, 0)), true,
				exe->env);
			return ;
		}
		else
		{
			if ((cmd->next || cmd->prev) && pipe(exe->fd) == -1)
				return ;
			cmd->pid = fork();
			if (cmd->pid == -1)
				return ;
			if (cmd->pid == 0)
				execute_child(exe, cmd, 1);
		}
	}
	else
		redirect(exe, cmd);
	execute_parent(exe, cmd);
}

void	execute_parent(t_exe *exe, t_parser *cmd)
{
	t_parser	*tmp;

	if (cmd->next)
	{
		exe->fd[1] = close(exe->fd[1]);
		exe->fd_in = exe->fd[0];
		execute_pipeline(exe, cmd->next);
		exe->fd_in = close(exe->fd_in);
	}
	exe->fd[0] = close(exe->fd[0]);
	exe->fd[1] = close(exe->fd[1]);
	tmp = exe->parser;
	while (tmp)
	{
		if (tmp->pid != 0)
		{
			waitpid(tmp->pid, &exe->error, 0);
			add_node_char("?", ft_itoa(WEXITSTATUS(exe->error)), true,
				exe->env);
			tmp->pid = 0;
		}
		tmp = tmp->next;
	}
}

int	executor(t_env **env, t_parser *parser)
{
	t_exe	exe;

	exe = init_exe(env, parser);
	execute_pipeline(&exe, exe.parser);
	return (free_exe(&exe, 0, 0, NULL));
}
