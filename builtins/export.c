/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:36 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/03 22:49:10 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_variable_name(char *environment)
{
	char	*var_name;
	int		i;

	i = 0;
	while (environment[i] != '=')
		i++;
	var_name = ft_substr(environment, 0, i);
	return (var_name);
}

bool	env_exist(char *var_name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(var_name, get_variable_name(env[i]), ft_strlen(var_name) + 1))
			return (true);
		i++;
	}
	return (false);
}

char	**replace_env(char *environment, t_shell *shell)
{
	int		i;
	char	*var_name;

	var_name = get_variable_name(environment);
	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp(get_variable_name(shell->envp[i]), var_name, ft_strlen(var_name) + 1))
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strdup(environment);
		}
		i++;
	}
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
		shell_error(shell, "Caloc error: env\n");
	i = 0;
	while (shell->envp[i])
	{
		env_copy[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	env_copy[i] = ft_strdup(environment);
	return (env_copy);
}

char	**add_envp(char *environment, t_shell *shell)
{
	char	*var_name;

	if (ft_strchr(environment, '='))
	{
		var_name = get_variable_name(environment);
		if (find_special(var_name) || ft_strchr(var_name, ' ') || !var_name[0])
		{		
			ft_printf(1, "minishell: export '%s': not a valid identifier\n", var_name);
			safe_exit(shell, 127);
		}
		if (env_exist(var_name, shell->envp))
			shell->envp = replace_env(environment, shell);
		else
			shell->envp = set_new_env(environment, shell);
	}
	return (shell->envp);
}

void	export(char **cmd_args, t_shell *shell)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		shell->envp = add_envp(cmd_args[i], shell);
		i++;
	}
	i = 0;
	while (shell->envp[i])
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
}