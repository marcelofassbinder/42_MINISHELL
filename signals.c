/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:19:10 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/18 17:57:41 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* Function to handle the received signal, during the execution of 
	this function other received signals are blocked if it is in the mask. */
void	signal_handler(int signal, siginfo_t *info, void *content)
{
	(void)content;
	(void)info;
	if (signal == SIGINT)
	{
		ft_printf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
