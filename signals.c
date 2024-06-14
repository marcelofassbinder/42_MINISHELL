/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:19:10 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/14 10:57:35 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

void	start_sigaction()
{
	struct sigaction sa_quit;
	struct sigaction sa_int;

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