/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:13:42 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/31 15:51:05 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char *path_from_env)
{
	char	**path;
	int		i;

	if (!path_from_env)
		return (NULL);
	path = ft_split(path_from_env, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	free(path_from_env);
	return (path);
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

void	handle_exec_error(int execve_ret, t_exec *exec, t_shell *shell)
{
	shell->exit_status = EXIT_CMD;
	if (execve_ret == -1)
	{
		if (access(exec->cmd_args[0], F_OK) == 0)
		{
			if ((exec->cmd_args[0][0] == '.' && exec->cmd_args[0][1] == '/')
				|| exec->cmd_args[0][0] == '/')
			{
				shell->exit_status = 126;
				shell_error(shell, exec->cmd_args[0], 5, true);
			}
			else
				shell_error(shell, exec->cmd_args[0], 1, true);
		}
		else
			shell_error(shell, exec->cmd_args[0], 3, true);
	}
	if ((exec->cmd_args[0][0] == '.' && exec->cmd_args[0][1] == '/')
			|| exec->cmd_args[0][0] == '/')
		shell_error(shell, exec->cmd_args[0], 2, true);
	shell_error(shell, exec->cmd_args[0], 1, true);
}

void	run_execve(t_exec *exec, t_shell *shell)
{
	int		i;
	int		execve_ret;
	char	**path;
	char	**envs;
	char	*path_cmd;

	execve_ret = 0;
	envs = filter_envs(shell->envp);
	if (access(exec->cmd_args[0], F_OK) == 0)
		execve_ret = execve(exec->cmd_args[0], exec->cmd_args, envs);
	path = get_path(ft_get_env("PATH", shell));
	if (!path)
		shell_error(shell, exec->cmd_args[0], 2, true);
	i = 0;
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], exec->cmd_args[0]);
		if (access(path_cmd, F_OK) == 0)
			execve_ret = execve(path_cmd, exec->cmd_args, envs);
		free(path_cmd);
		i++;
	}
	free(path);
	free_envs(envs);
	handle_exec_error(execve_ret, exec, shell);
}
