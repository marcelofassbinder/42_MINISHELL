/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:22:49 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/06 16:59:49 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_builtin_p(t_exec *exec, t_shell *shell)
{
	if (!ft_strncmp(exec->cmd_args[0], "echo", ft_strlen("echo") + 1))
		echo(exec->cmd_args, shell);
	else if (!ft_strncmp(exec->cmd_args[0], "env", ft_strlen("env") + 1))
		env(exec->cmd_args, shell);
	else if (!ft_strncmp(exec->cmd_args[0], "export", ft_strlen("export") + 1))
		export(exec->cmd_args, shell);
	else if (!ft_strncmp(exec->cmd_args[0], "unset", ft_strlen("unset") + 1))
		unset(exec->cmd_args, shell);
	else if (!ft_strncmp(exec->cmd_args[0], "pwd", ft_strlen("pwd") + 1))
		pwd(shell);
	else if (!ft_strncmp(exec->cmd_args[0], "cd", ft_strlen("cd") + 1))
		cd(exec->cmd_args, shell);
	else
		shell->exit_status = EXIT_CMD;
	//safe_exit(shell, shell->exit_status);
}

void	run_redir_p(t_redir *redir, t_shell *shell)
{
	int fd;
	int saved_stdout;
	int saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (redir->type == REDIR_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			shell_error(shell, "Error while opening file for writing", 0);
			return;
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			shell_error(shell, "Error while duplicating file descriptor", 0);
			close(fd);
			return;
		}
	}
	else if (redir->type == REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
		{
			shell_error(shell, "Error while opening file for reading", 0);
			return;
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			shell_error(shell, "Error while duplicating file descriptor", 0);
			close(fd);
			return;
		}
	}
	else
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			shell_error(shell, "Error while opening file for appending", 0);
			return;
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			shell_error(shell, "Error while duplicating file descriptor", 0);
			close(fd);
			return;
		}
	}
	close(fd);
	run_in_parent(redir->down, shell);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

void	run_in_parent(void *root, t_shell *shell)
{
	enum e_type node_type;

	if (!root)
		return ;
	node_type = *(enum e_type *)root;
	if (node_type == WORD)
		run_builtin_p((t_exec *)root, shell);
	else if (node_type == REDIR_IN || node_type == REDIR_OUT || node_type == D_REDIR_OUT)
		run_redir_p((t_redir *)root, shell);
}