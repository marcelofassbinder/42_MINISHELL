/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:06:16 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/01 13:55:30 by mfassbin         ###   ########.fr       */
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
	return(path);
}

void	run_execve(t_exec *exec, char **envp)
{	
	char **path;
	char *path_cmd;
	int i;
	
	path = get_path(getenv("PATH"));
	i = 0;
	if (access(exec->cmd_args[0], F_OK) == 0)
		execve(exec->cmd_args[0], exec->cmd_args, envp);
	while(path[i])
	{
		path_cmd = ft_strjoin(path[i], exec->cmd_args[0]);
		if (access(path_cmd, F_OK) == 0)
			execve(path_cmd, exec->cmd_args, envp);
		free(path_cmd);
		i++;
	}
	ft_printf(2, "%s: command not found\n", exec->cmd_args[0]);
}

void	run_exec(t_exec *exec, char **envp)
{
	//if (exec->is_builtin)
	if (!exec)
		return ;
	if (!exec->is_builtin)
		run_execve(exec, envp);		
	if (!ft_strncmp(exec->cmd_args[0], "echo", ft_strlen("echo") + 1))
		echo(exec->cmd_args);
	//exit(0);
}
void	run_redir(t_redir *redir, char **envp)
{
	int	fd;

	// Verificar se o arquivo ja existe e nao alterar as permissoes caso exista.
	if (redir->type == REDIR_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_printf(2, "%s: No such file or directory\n", redir->file);
			return ;
		}
		dup2(fd, STDOUT_FILENO);
	}
	else if (redir->type == REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
		{
			ft_printf(2, "%s: No such file or directory\n", redir->file);
			return ;
		}
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
			ft_printf(2, "%s: No such file or directory\n", redir->file);
			return ;
		}	
		dup2(fd, STDOUT_FILENO);
	}
	run((void *)redir->down, envp);
	close(fd);
}

void	run_pipe(t_pipe *pipe_str, char **envp)
{
	int	fd[2];
	
	if (pipe(fd) == -1)
		ft_printf(2, "Pipe Error\n");
	if (fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		run(pipe_str->left, envp);
	}
	if (fork() == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		run(pipe_str->right, envp);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}

void	run(void *root, char **envp)
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
		run_exec(exec, envp);
	}
	else if (node_type == REDIR_IN || node_type == D_REDIR_OUT || node_type == REDIR_OUT)
	{
		redir = (t_redir *)root;
		run_redir(redir, envp);
	}
	else if (node_type == PIPELINE)
	{
		pipe = (t_pipe *)root;
		run_pipe(pipe, envp);
	}
}
