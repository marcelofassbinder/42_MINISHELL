/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:06:16 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/23 16:01:42 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_exec(t_exec *exec, t_shell *shell)
{
	if (!exec || !exec->cmd_args[0])
		return ;
	if (!exec->cmd_args[0][0])
		shell_error(shell, "", 1, true);
	if (!ft_strcmp(exec->cmd_args[0], "env") && exec->cmd_args[1])
		shell_error(shell, "env", 2, true);
	if (!exec->is_builtin)
		run_execve(exec, shell);
	else if (exec->is_builtin)
		run_builtin(exec, shell);	
	free_and_exit(shell);
}

void	run_redir(t_redir *redir, t_shell *shell)
{
	if (!redirect(shell, redir, true))
		return ;
	run((void *)redir->down, shell);
}

void	run_pipe(t_pipe *pipe_str, t_shell *shell)
{
	int	fd[2];
	int	pid[2];
	
	if (pipe(fd) == -1)
		shell_error(shell, "Pipe error\n", 0, true);
	pid[0] = safe_fork(shell);
	if (pid[0] == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		run(pipe_str->left, shell);
		free_and_exit(shell);
	}
	pid[1] = safe_fork(shell);
	if (pid[1] == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		run(pipe_str->right, shell);
		free_and_exit(shell);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &shell->exit_status, 0);
	waitpid(pid[1], &shell->exit_status, 0);
	shell->exit_status = get_status(shell->exit_status);
}

void	run(void *root, t_shell *shell)
{
	enum e_type	node_type;
	t_exec		*exec;
	t_redir		*redir;
	t_pipe		*pipe;

	if (!root)
		return ;
	node_type = *(enum e_type *)root;
	if (node_type == WORD)
	{
		exec = (t_exec *)root;
		run_exec(exec, shell);
	}
	else if (node_type == REDIR_IN || node_type == D_REDIR_OUT || node_type == REDIR_OUT || node_type == HERE_DOC)
	{
		redir = (t_redir *)root;
		run_redir(redir, shell);
	}
	else if (node_type == PIPELINE)
	{
		pipe = (t_pipe *)root;
		run_pipe(pipe, shell);
	}
}
