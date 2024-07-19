/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:19:10 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/19 17:37:27 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_change(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf(1, "\n");
		g_received_signal = 2;
	}
	else
	{
		ft_printf(1, " quit (Core dumped)\n");
		g_received_signal = 3;
	}
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_iterative(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_modify(void)
{
	signal(SIGINT, signal_change);
	signal(SIGQUIT, signal_change);
}

/* Function to handle the received signal, during the execution of
	this function other received signals are blocked if it is in the mask. */
void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf(STDIN_FILENO, "\n");
		rl_redisplay();
		g_received_signal = 2;
	}
}

/* Initialize the signal handling structure (sigaction), define the
masks (signals that are blocked if the signal handler is handling a signal).*/
void	start_sig(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
