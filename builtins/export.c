/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:36 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/08 19:03:51 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_variable_name(char *environment)
{
	char	*var_name;
	int		i;

	i = 0;
	while (environment[i] && environment[i] != '=')
		i++;
	var_name = ft_substr(environment, 0, i);
	return (var_name);
}

bool	env_exist(char *var_name, char **env)
{
	int		i;
	char	*cur_var;

	i = 0;
	while (env[i])
	{
		cur_var = get_variable_name(env[i]);
		if (!ft_strncmp(var_name, cur_var, ft_strlen(var_name) + 1))
		{
			free(cur_var);
			return (true);
		}
		free(cur_var);
		i++;
	}
	return (false);
}

char	**replace_env(char *environment, t_shell *shell)
{
	int		i;
	char	*var_name;
	char	*cur_var;

	var_name = get_variable_name(environment);
	i = 0;
	while (shell->envp[i])
	{
		cur_var = get_variable_name(shell->envp[i]);
		if (!ft_strncmp(cur_var, var_name, ft_strlen(var_name) + 1))
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strdup(environment);
		}
		free(cur_var);
		i++;
	}
	free(var_name);
	return (shell->envp);
}
char	**set_new_env(char *environment, t_shell *shell)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (shell->envp[i])
		i++;
	env_copy = ft_calloc(sizeof(char *), i + 2);
	if (!env_copy)
		shell_error(shell, "Calloc Error: env\n", 0);
	i = 0;
	while (shell->envp[i])
	{
		env_copy[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	env_copy[i] = ft_strdup(environment);
	free_envs(shell->envp);
	return (env_copy);
}

char	**add_envp(char *environment, t_shell *shell)
{
	char	*var_name;

	var_name = get_variable_name(environment);
	if (find_special(var_name) || ft_strchr(var_name, ' ') || !var_name[0])
	{		
		ft_printf(2, "minishell: export '%s': not a valid identifier\n", environment);
		shell->exit_status = 1;
		free(var_name);
		return (shell->envp);
	}
	if (ft_strchr(environment, '='))
	{
		if (env_exist(var_name, shell->envp))
			shell->envp = replace_env(environment, shell);
		else
			shell->envp = set_new_env(environment, shell);
		free(var_name);
	}
	return (shell->envp);
}

void	export(char **cmd_args, t_shell *shell)
{
	int	i;

	shell->exit_status = EXIT_SUCCESS;
	i = 0;
	while (cmd_args[i])
	{
		if (cmd_args[i][0] == '-')
		{
			ft_printf(2, "minishell: export '%s': not a valid identifier\n", cmd_args[i]);
			shell->exit_status = 2;
			i++;
			continue ;			
		}
		if (ft_isdigit(cmd_args[i][0]))
		{
			ft_printf(2, "minishell: export '%s': not a valid identifier\n", cmd_args[i]);
			shell->exit_status = 1;
			i++;
			continue ;
		}
		shell->envp = add_envp(cmd_args[i], shell);
		i++;
	}
}