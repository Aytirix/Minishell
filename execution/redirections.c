/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/07/17 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	redirect_pipe(t_exe *exe, t_parser *cmd, int type)
{
	if (exe->fd_in != STDIN_FILENO && (type == 0 || type == 2))
	{
		if (dup2(exe->fd_in, STDIN_FILENO) == -1)
		{
			exe->fd_in = close(exe->fd_in);
			return (free_exe(exe, 0, 1, "Failed to redirect input"));
		}
		exe->fd_in = close(exe->fd_in);
	}
	if (cmd->next && (type == 1 || type == 2))
	{
		if (dup2(exe->fd[1], STDOUT_FILENO) == -1)
		{
			exe->fd[1] = close(exe->fd[1]);
			return (free_exe(exe, 0, 1, "Failed to redirect input"));
		}
		exe->fd[1] = close(exe->fd[1]);
	}
	return (0);
}

int	redirect_input(t_exe *exe, t_lexer *red)
{
	if (!red)
		return (0);
	if (red->token == HEREDOC)
		return (here_doc(exe, red));
	else if (access(red->content, F_OK) != 0)
		return (free_exe(exe, 1, 1, ft_strjoinf(red->content,
					": No such file or directory\n", 0)));
	exe->fd_tmp = open(red->content, O_RDONLY);
	if (exe->fd_tmp == -1)
		return (free_exe(exe, 0, 1, "Failed to open input file"));
	if (dup2(exe->fd_tmp, STDIN_FILENO) == -1)
	{
		exe->fd_tmp = close(exe->fd_tmp);
		return (free_exe(exe, 0, 1, "Failed to redirect input"));
	}
	exe->fd_tmp = close(exe->fd_tmp);
	return (0);
}

int	redirect_output(t_exe *exe, t_lexer *red)
{
	if (!red)
		return (0);
	if (red->token == APPENDOUTPUT)
		exe->fd_tmp = open(red->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		exe->fd_tmp = open(red->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exe->fd_tmp == -1)
		return (free_exe(exe, 0, 1, "1"));
	if (dup2(exe->fd_tmp, STDOUT_FILENO) == -1)
	{
		exe->fd_tmp = close(exe->fd_tmp);
		return (free_exe(exe, 0, 1, "1"));
	}
	exe->fd_tmp = close(exe->fd_tmp);
	return (0);
}

static void	here_doc_child(t_lexer *red, t_exe *exe)
{
	char	*line;

	set_signal_action(sigint_heredoc_handler);
	close(exe->fd_heredoc[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(exe->fd_heredoc[1]);
			exit(1);
		}
		if (ft_strncmp(line, red->content, ft_strlen(red->content)) == 0
			&& ft_strlen(line) == ft_strlen(red->content))
		{
			free(line);
			break ;
		}
		line = ft_strjoinf(line, "\n", 1);
		write(exe->fd_heredoc[1], line, ft_strlen(line));
		free(line);
	}
	close(exe->fd_heredoc[1]);
	exit(0);
}

int	here_doc(t_exe *exe, t_lexer *red)
{
	if (pipe(exe->fd_heredoc) == -1)
		return (free_exe(exe, 0, 1, "1"));
	exe->pid = fork();
	if (exe->pid == -1)
	{
		close(exe->fd_heredoc[0]);
		close(exe->fd_heredoc[1]);
		return (free_exe(exe, 0, 1, "1"));
	}
	if (exe->pid == 0)
		here_doc_child(red, exe);
	else
	{
		close(exe->fd_heredoc[1]);
		wait(NULL);
		waitpid(exe->pid, &exe->error, 0);
		set_signal_action(sigint_handler);
		if (dup2(exe->fd_heredoc[0], STDIN_FILENO) == -1)
		{
			close(exe->fd_heredoc[0]);
			return (free_exe(exe, 0, 1, "1"));
		}
		close(exe->fd_heredoc[0]);
	}
	return (0);
}
