/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/07/17 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../includes/minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_exe
{
	t_env			**env_cpy;
	t_env			**env;
	char			**env_tab;
	struct s_parser	*parser;

	char			*path;
	char			**envp;
	char			*tmp;
	int				fd[2];
	int				fd_heredoc[2];
	int				fd_tmp;
	int				i;
	int				fd_in;
	int				error;
	pid_t			pid;
}					t_exe;

// execution.c
void				execute_parent(t_exe *exe, t_parser *cmd);

// redirections.c
int					redirect_pipe(t_exe *exe, t_parser *cmd, int type);
int					redirect_input(t_exe *exe, t_lexer *red);
int					redirect_output(t_exe *exe, t_lexer *red);
int					here_doc(t_exe *exe, t_lexer *red);

// tools.c
t_exe				init_exe(t_env **env, t_parser *parser);
int					free_exe(t_exe *exe, int is_malloc, int error,
						char *message);
int					check_path(t_exe *exe, t_parser *cmd);
int					get_path_cmd(t_exe *exe, char *cmd);
int					create_path(t_exe *exe, char *cmd, char *path);
#endif