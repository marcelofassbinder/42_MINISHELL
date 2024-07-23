/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:58:59 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/23 15:59:37 by vivaccar         ###   ########.fr       */
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