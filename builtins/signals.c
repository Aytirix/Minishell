/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:18:47 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/23 16:22:34 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigint_heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		close(STDIN_FILENO);
	}
}

void	set_signal_action(void (*handler)(int))
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = handler;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
