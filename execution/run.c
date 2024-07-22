/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:06:16 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/22 19:17:20 by mfassbin         ###   ########.fr       */
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

char	**filter_envs(char **envp)
{
	int		i;
	int		j;
	char	**new_envs;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			j++;
		i++;
	}
	new_envs = ft_calloc(sizeof(char *), j + 1);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			new_envs[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	return (new_envs);
}

void	run_execve(t_exec *exec, t_shell *shell)
{	
	char	**path;
	char	*path_cmd;
	int		i;
	int		error;
	char	**envs;

	error = 0;
	if (!exec->cmd_args[0])
		return ;
	path = get_path(ft_get_env("PATH", shell));
	i = 0;
	if (access(exec->cmd_args[0], F_OK) == 0)
	{
		envs = filter_envs(shell->envp);
		error = execve(exec->cmd_args[0], exec->cmd_args, envs);
	}
	if (!path)
		shell_error(shell, exec->cmd_args[0], 2, true);
	while(path[i])
	{
		path_cmd = ft_strjoin(path[i], exec->cmd_args[0]);
		if (access(path_cmd, F_OK) == 0)
		{
			envs = filter_envs(shell->envp);
			error = execve(path_cmd, exec->cmd_args, envs);
		}
		free(path_cmd);
		i++;
	}
	shell->exit_status = EXIT_CMD;
	free(path);
	if (error == -1)
	{
		free_envs(envs);
		shell->exit_status = 126;
		shell_error(shell, exec->cmd_args[0], 3, true);
	}
	shell_error(shell, exec->cmd_args[0], 1, true);
}

void	run_builtin(t_exec *exec, t_shell *shell)
{
	if (!ft_strcmp(exec->cmd_args[0], "echo"))
		echo(exec->cmd_args, shell);
	if (!ft_strcmp(exec->cmd_args[0], "export"))
		export(exec->cmd_args, shell);
	if (!ft_strcmp(exec->cmd_args[0], "unset"))
		unset(exec->cmd_args, shell);
	if (!ft_strcmp(exec->cmd_args[0], "pwd"))
		pwd(shell);
	if (!ft_strcmp(exec->cmd_args[0], "cd"))
		cd(exec->cmd_args, shell);
	if (!ft_strcmp(exec->cmd_args[0], "exit"))
		exit_cmd(exec->cmd_args, shell);
}

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

int	return_parent_error(t_shell *shell, char *str, int error)
{
	shell->exit_status = EXIT_FAILURE;
	if (error == 1) // erro de comando
	{
		shell->exit_status = EXIT_CMD;
		ft_printf(STDERR_FILENO, "%s: command not found\n", str);
	} 
	else if (error == 2) // erro de arquivo ou diretorio
		ft_printf(STDERR_FILENO, "minishell: %s: No such file or directory\n", str);
	else if (error == 3) // erro de permissao
		ft_printf(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
	else if (error == 4) // erro de permissao
		ft_printf(STDERR_FILENO, "minishell: %s: ambiguous redirect\n", str);
	else
		ft_printf(STDERR_FILENO, "%s\n", str);
	return (0);
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
		if (shell->process == CHILD)
			shell_error(shell, redir->file, 3, exit_flag);
		else
			return (return_parent_error(shell, redir->file, 3));
	}
	else
		dup2(fd, STDIN_FILENO);
	return (1);
}

//teste
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

int	redirect(t_shell *shell, t_redir *redir, int exit_flag)
{
	int	success;
	
	success = 0;
	if (redir->type == HERE_DOC)
	{
		success = 1;
		dup2(shell->fd_heredoc[redir->id], STDIN_FILENO);
	}
	else if (redir->type == REDIR_OUT || redir->type == D_REDIR_OUT)
		success = redirect_out(shell, redir, exit_flag);
	else
		success = redirect_in(shell, redir, exit_flag);
	return (success);
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
		exit(0);
	}
	pid[1] = safe_fork(shell);
	if (pid[1] == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		run(pipe_str->right, shell);
		exit(0);
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
