/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:19:10 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/14 10:40:15 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	signal_handler(int signal, siginfo_t *info, void *content)
{
	(void)content;
	(void)info;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	start_sigaction()
{
	struct sigaction sa_quit;
	struct sigaction sa_int;

	sigemptyset(&sa_quit.sa_mask);
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_sigaction = &signal_handler;
	sa_quit.sa_handler = SIG_IGN;
	sigaddset(&sa_int.sa_mask, SIGINT);
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sigaddset(&sa_int.sa_mask, SIGQUIT);
	sigaddset(&sa_quit.sa_mask, SIGINT);
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}