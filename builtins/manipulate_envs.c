/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_envs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:15:43 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/25 22:39:46 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_variable_name(char *environment)
{
	char	*var_name;
	int		i;

	i = 0;
	while (environment[i] && environment[i] != '=' && environment[i] != '+')
		i++;
	if (environment[i] == '+')
	{
		if (environment[i + 1] == '=')
		{
			var_name = ft_substr(environment, 0, i);
			return (var_name);
		}
		else
		{
			while (environment[i] && environment[i] != '=')
				i++;
			var_name = ft_substr(environment, 0, i);
			return (var_name);
		}
	}
	var_name = ft_substr(environment, 0, i);
	return (var_name);
}

char	*do_replace(char *environment, char *envp, int mode)
{
	char	*var_value;
	char	*new_env;

	if (mode == 1)
	{
		var_value = get_var_value(environment);
		new_env = ft_strjoin(envp, var_value);
		free(var_value);
		return (new_env);
	}
	free(envp);
	return (ft_strdup(environment));
}

char	**replace_env(char *environment, t_shell *shell, int mode)
{
	int		i;
	char	*var_name;
	char	*cur_var;

	var_name = get_variable_name(environment);
	i = 0;
	while (shell->envp[i])
	{
		cur_var = get_variable_name(shell->envp[i]);
		if (!ft_strcmp(cur_var, var_name))
			shell->envp[i] = do_replace(environment, shell->envp[i], mode);
		free(cur_var);
		i++;
	}
	free(var_name);
	return (shell->envp);
}

char	**set_new_env(char *environment, t_shell *shell, int mode)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (shell->envp[i])
		i++;
	env_copy = ft_calloc(sizeof(char *), i + 2);
	if (!env_copy)
		shell_error(shell, "Calloc Error: env\n", 0, true);
	i = 0;
	while (shell->envp[i])
	{
		env_copy[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	if (mode == 1)
		env_copy[i] = remove_plus(environment);
	if (mode == 0)
		env_copy[i] = ft_strdup(environment);
	free_envs(shell->envp);
	return (env_copy);
}

char	**add_envp(char *environment, t_shell *shell)
{
	char	*var_name;
	int		mode;

	var_name = get_variable_name(environment);
	if (find_special(var_name) || ft_strchr(var_name, ' ') || !var_name[0]
		|| ft_isdigit(var_name[0]))
		return (export_error(shell, var_name, environment));
	mode = add_mode(environment);
	if (env_exist(var_name, shell->envp))
		shell->envp = replace_env(environment, shell, mode);
	else
		shell->envp = set_new_env(environment, shell, mode);
	free(var_name);
	return (shell->envp);
}
