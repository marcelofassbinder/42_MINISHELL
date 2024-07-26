/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:56:14 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/26 16:02:00 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_out(t_shell *shell, t_redir *redir, int exit_flag)
{
	int	fd;

	fd = 0;
	if (!has_no_file(shell, redir, exit_flag))
		return (0);
	if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		shell->exit_status = EXIT_FAILURE;
		if (shell->process == CHILD)
			shell_error(shell, redir->file, 3, exit_flag);
		else
			return (return_parent_error(shell, redir->file, 3));
	}
	else
		dup2(fd, STDOUT_FILENO);
	return (1);
}

int	redirect_in(t_shell *shell, t_redir *redir, int exit_flag)
{
	int	fd;

	fd = 0;	
	if (!has_no_file(shell, redir, exit_flag))
		return (0);
	if (access(redir->file, F_OK) != 0)
	{
		if (shell->process == CHILD)
			shell_error(shell, redir->file, 2, true);
		else
			return (return_parent_error(shell, redir->file, 2));
	}	
	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		shell->exit_status = EXIT_FAILURE;
		if (shell->process == CHILD)
			shell_error(shell, redir->file, 3, exit_flag);
		else
			return (return_parent_error(shell, redir->file, 3));
	}
	else
		dup2(fd, STDIN_FILENO);
	return (1);
}

int	redirect(t_shell *shell, t_redir *redir, int exit_flag)
{
	int	success;
	
	success = 0;
	if (redir->type == HERE_DOC)
	{
		success = 1;
		dup2(shell->array_fd_here_doc[redir->id], STDIN_FILENO);
	}
	else if (redir->type == REDIR_OUT || redir->type == D_REDIR_OUT)
		success = redirect_out(shell, redir, exit_flag);
	else
		success = redirect_in(shell, redir, exit_flag);
	return (success);
}
