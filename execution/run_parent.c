/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/20 14:57:00 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void	run_builtin_p(t_exec *exec, t_shell *shell)
{
	if (!exec->cmd_args[0])
		return ;
	if (!ft_strcmp(exec->cmd_args[0], "echo"))
		echo(exec->cmd_args, shell);
	else if (!ft_strcmp(exec->cmd_args[0], "export"))
		export(exec->cmd_args, shell);
	else if (!ft_strcmp(exec->cmd_args[0], "unset"))
		unset(exec->cmd_args, shell);
	else if (!ft_strcmp(exec->cmd_args[0], "pwd"))
		pwd(shell);
	else if (!ft_strcmp(exec->cmd_args[0], "cd"))
		cd(exec->cmd_args, shell);
	else if (!ft_strcmp(exec->cmd_args[0], "exit"))
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
	if (redirect(shell, redir, false))
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
	shell->process = PARENT;
	if (node_type == WORD)
		run_builtin_p((t_exec *)root, shell);
	else if (node_type == REDIR_IN || node_type == REDIR_OUT || node_type == D_REDIR_OUT || node_type == HERE_DOC)
		run_redir_p((t_redir *)root, shell);
}