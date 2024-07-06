/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:19:10 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/06 14:14:19 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_handler(int signal)
{
	if (signal == SIGINT)
	{
		exit (130);
	}
	else
	{
		ft_printf(STDIN_FILENO, "Core dumped\n");
		exit(131);
	}
}

void	start_child_signals(void)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, child_handler);
}

/* Function to handle the received signal, during the execution of 
	this function other received signals are blocked if it is in the mask. */
void	signal_handler(int signal, siginfo_t *info, void *content)
{
	(void)info;
	(void)content;

	if (signal == SIGINT && g_status != -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf(STDIN_FILENO, "\n");
		rl_redisplay();
		g_status = 130;
		exit(130);
	}
}

/* Initialize the signal handling structure (sigaction), define the
masks (signals that are blocked if the signal handler is handling a signal).*/
void	start_sigaction(void)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_int;

	sigemptyset(&sa_quit.sa_mask);
	sigemptyset(&sa_int.sa_mask);
	sa_quit.sa_flags = 0;
	sa_int.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sa_int.sa_sigaction = &signal_handler;
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sigaddset(&sa_quit.sa_mask, SIGINT);
	sigaddset(&sa_int.sa_mask, SIGQUIT);
	sigaddset(&sa_int.sa_mask, SIGINT);
	sigaction(SIGQUIT, &sa_quit, NULL);
	sigaction(SIGINT, &sa_int, NULL);
}
