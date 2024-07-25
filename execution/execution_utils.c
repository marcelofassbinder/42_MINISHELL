/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:16:33 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/25 23:05:49 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_exit_sig(int *exit_code)
{
	int exit_status_0;
	int exit_status_1;

	if (WIFSIGNALED(exit_code[0]) || WIFSIGNALED(exit_code[1]))
	{
		exit_status_0 = WTERMSIG(exit_code[0]);
		exit_status_1 = WTERMSIG(exit_code[1]);
		if (exit_status_0 == SIGINT || exit_status_1 == SIGINT)
			ft_printf(STDOUT_FILENO, "\n");
		else if (exit_status_0 == SIGQUIT || exit_status_1 == SIGQUIT)
			ft_printf(STDOUT_FILENO, "Quit (core dumped)\n");
		if (WIFSIGNALED(exit_code[1]))
		{
			if (exit_status_1 == SIGINT)
				return (130);
			else if (exit_status_1 == SIGQUIT)
				return (131);
		}
	}
	return (WEXITSTATUS(exit_code[1]));
}

void	manage_pipe_exit(int *fd, int *pid, t_shell *shell)
{
	int exit_code[2];

	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &exit_code[0], 0);
	waitpid(pid[1], &exit_code[1], 0);
	shell->exit_status = check_exit_sig(exit_code);
	exit(shell->exit_status);
}

bool	has_no_file(t_shell *shell, t_redir *redir, int exit_flag)
{
	if (!redir->file)
	{
		if (shell->process == CHILD)
			shell_error(shell, "", 4, exit_flag);
		return (return_parent_error(shell, "", 4));
	}
	if (!redir->file[0])
	{
		if (shell->process == CHILD)
			shell_error(shell, redir->file, 2, exit_flag);
		return (return_parent_error(shell, "", 2));
	}
	return (1);
}

int	has_pipe(t_shell *shell)
{
	t_token *token;

	token = shell->token_list->first;
	while(token)
	{
		if (token->type == PIPELINE)
			return (1);
		token = token->next;
	}
	return (0);
}

int	get_status(int status)
{
	if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_printf(1, "\n");
			return (130);
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_printf(1, "Quit (core dumped)\n");
			return (131);
		}
	}
	return (0);
}