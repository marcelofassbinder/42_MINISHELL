/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:22:49 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/08 20:54:20 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_builtin_p(t_exec *exec, t_shell *shell)
{
	shell->process = PARENT;
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
	else if (!ft_strncmp(exec->cmd_args[0], "exit", ft_strlen("exit") + 1))
		exit_cmd(exec->cmd_args, shell);
	else
	{
		shell->process = CHILD;
		shell->exit_status = EXIT_CMD;
	}
}

void	run_redir_p(t_redir *redir, t_shell *shell)
{
	int saved_stdout;
	int saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	redirect(shell, redir, false);
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