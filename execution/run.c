/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:06:16 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/09 20:04:30 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **get_path(char *path_from_env)
{
	char **path;
	int	i;

	if (!path_from_env)
		return (NULL);
	path = ft_split(path_from_env,':');
	i = 0;
	while(path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;		
	}
	free(path_from_env);
	return(path);
}

void	run_execve(t_exec *exec, t_shell *shell)
{	
	char **path;
	char *path_cmd;
	int i;

	path = get_path(ft_get_env("PATH", shell));
	i = 0;
	if (access(exec->cmd_args[0], F_OK) == 0)
		execve(exec->cmd_args[0], exec->cmd_args, shell->envp);
	if (!path)
		shell_error(shell, exec->cmd_args[0], 2, true);
	while(path[i])
	{
		path_cmd = ft_strjoin(path[i], exec->cmd_args[0]);
		if (access(path_cmd, F_OK) == 0)
			execve(path_cmd, exec->cmd_args, shell->envp);
		free(path_cmd);
		i++;
	}
	shell->exit_status = EXIT_CMD;
	free(path);
	shell_error(shell, exec->cmd_args[0], 1, true);
}

void	run_builtin(t_exec *exec, t_shell *shell)
{
	if (!ft_strncmp(exec->cmd_args[0], "echo", ft_strlen("echo") + 1))
		echo(exec->cmd_args, shell);
	if (!ft_strncmp(exec->cmd_args[0], "env", ft_strlen("env") + 1))
		env(exec->cmd_args, shell);
	if (!ft_strncmp(exec->cmd_args[0], "export", ft_strlen("export") + 1))
		export(exec->cmd_args, shell);
	if (!ft_strncmp(exec->cmd_args[0], "unset", ft_strlen("unset") + 1))
		unset(exec->cmd_args, shell);
	if (!ft_strncmp(exec->cmd_args[0], "pwd", ft_strlen("pwd") + 1))
		pwd(shell);
	if (!ft_strncmp(exec->cmd_args[0], "cd", ft_strlen("cd") + 1))
		cd(exec->cmd_args, shell);
	if (!ft_strncmp(exec->cmd_args[0], "exit", ft_strlen("exit") + 1))
		exit_cmd(exec->cmd_args, shell);
}

bool	is_local_variable(t_exec *exec, t_shell *shell)
{
	ft_printf(1, "%s", exec->cmd_args[0]);
	(void)shell;
	return (false);
}

void	run_exec(t_exec *exec, t_shell *shell)
{
	if (!exec)
		return ;
	if (is_local_variable(exec, shell))
		free_and_exit(shell);
	else if (!exec->is_builtin)
		run_execve(exec, shell);
	else if (exec->is_builtin)
		run_builtin(exec, shell);
	free_and_exit(shell);
}

int	return_parent_error(t_shell *shell, char *str, int error)
{
	shell->exit_status = 1;
	if (error == 1) // erro de comando
		ft_printf(STDERR_FILENO, "%s: command not found\n", str);
	else if (error == 2) // erro de arquivo ou diretorio
		ft_printf(STDERR_FILENO, "minishell: %s: No such file or directory\n", str);
	else if (error == 3) // erro de permissao
		ft_printf(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
	return (0);
}

int	redirect_out(t_shell *shell, t_redir *redir, int exit_flag)
{
	int	fd;

	fd = 0;
	if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
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
		if (shell->process == CHILD)
			shell_error(shell, redir->file, 3, exit_flag);
		else
			return (return_parent_error(shell, redir->file, 3));
	}
	if (fd != -1)
		dup2(fd, STDIN_FILENO);
	return (1);
}

int	redirect(t_shell *shell, t_redir *redir, int exit_flag)
{
	int	success;
	
	if (redir->type == REDIR_OUT || redir->type == D_REDIR_OUT)
		success = redirect_out(shell, redir, exit_flag);
	else if (redir->type == REDIR_IN)
		success = redirect_in(shell, redir, exit_flag);
	return (success);
}

void	run_redir(t_redir *redir, t_shell *shell)
{
	redirect(shell, redir, true);
	run((void *)redir->down, shell);
}

void	run_pipe(t_pipe *pipe_str, t_shell *shell)
{
	int	fd[2];
	
	if (pipe(fd) == -1)
		shell_error(shell, "Pipe error\n", 0, true);
	if (safe_fork(shell) == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		start_child_signals();
		run(pipe_str->left, shell);
	}
	if (safe_fork(shell) == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		start_child_signals();
		run(pipe_str->right, shell);
	}
	close(fd[0]);
	close(fd[1]);
	wait(&shell->exit_status);
	wait(&shell->exit_status);
	shell->exit_status = WEXITSTATUS(shell->exit_status);
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
	else if (node_type == REDIR_IN || node_type == D_REDIR_OUT || node_type == REDIR_OUT)
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
