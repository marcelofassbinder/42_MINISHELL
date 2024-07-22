/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:36 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/22 14:47:38 by mfassbin         ###   ########.fr       */
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

bool	env_exist(char *var_name, char **env)
{
	int		i;
	char	*cur_var;

	i = 0;
	while (env[i])
	{
		cur_var = get_variable_name(env[i]);
		if (!ft_strcmp(var_name, cur_var))
		{
			free(cur_var);
			return (true);
		}
		free(cur_var);
		i++;
	}
	return (false);
}

char	**replace_env(char *environment, t_shell *shell, int mode)
{
	int		i;
	char	*var_name;
	char	*cur_var;
	char	*var_value;

	var_name = get_variable_name(environment);
	i = 0;
	while (shell->envp[i])
	{
		cur_var = get_variable_name(shell->envp[i]);
		if (!ft_strcmp(cur_var, var_name))
		{
			if (mode == 1)
			{
				var_value = get_var_value(environment);
				shell->envp[i] = ft_strjoin(shell->envp[i], var_value);
				free(var_value);
			}
			else
			{
				free(shell->envp[i]);
				shell->envp[i] = ft_strdup(environment);
			}
		}
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

char	**export_error(t_shell *shell, char *var_name, char *environment)
{
	ft_printf(2, "minishell: export '%s': not a valid identifier\n", environment);
	shell->exit_status = 1;
	free(var_name);
	return (shell->envp);
}

int	add_mode(char *environment)
{
	int	i;

	i = 0;
	while (environment[i] && environment[i] != '=')
	{
		if (environment[i] == '+')
			return (1); // join mode
		i++;
	}
	return (0); // just add mode
}

char	*remove_plus(char *environment)
{
	char	*new;
	int		i;
	int		j;	

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(char), ft_strlen(environment));
	while (environment[i])
	{
		if (environment[i] != '+')
		{
			new[j] = environment[i];
			j++;	
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	**add_envp(char *environment, t_shell *shell)
{
	char	*var_name;
	int		mode;

	var_name = get_variable_name(environment);
	if (find_special(var_name) || ft_strchr(var_name, ' ') || !var_name[0])
		return (export_error(shell, var_name, environment));
	mode = add_mode(environment);
	if (env_exist(var_name, shell->envp))
		shell->envp = replace_env(environment, shell, mode);
	else
		shell->envp = set_new_env(environment, shell, mode);
	free(var_name);
	return (shell->envp);
}

void	swap(char **envs, int j)
{
	char	*temp;
	char	*cur_var_i;
	char	*cur_var_j;

	cur_var_i = get_variable_name(envs[j]);
	cur_var_j = get_variable_name(envs[j + 1]);
	if (ft_strcmp(cur_var_i, cur_var_j) > 0)
	{
	    temp = envs[j];
        envs[j] = envs[j + 1];
        envs[j + 1] = temp;
	}
	free(cur_var_i);
	free(cur_var_j);
}

char	**ordered_envs(t_shell *shell, int size)
{
	char	**ordered;
	int		i;
	int		j;

	ordered = copy_envs(shell, shell->envp);
	i = 0;
	j = 0;
    while (i < size - 1)
    {
        j = 0;
        while (j < size - i - 1)
        {
			swap(ordered, j);
            j++;
        }
        i++;
    }
	return (ordered);
}

void	print_env_x(t_shell *shell)
{
	int		i;
	char	*var;
	char	*value;
	char	**ordered;
	int		size;

	i = 0;
	size = 0;
	while (shell->envp[size])
        size++;
	ordered = ordered_envs(shell, size);
	while (ordered[i])
	{
		var = get_variable_name(ordered[i]);
		value = get_var_value(ordered[i]);
		ft_printf(STDOUT_FILENO, "declare -x %s", var);
		if (value)
			ft_printf(STDOUT_FILENO, "=\"%s\"", value);
		if (value)
			free(value);
		ft_printf(STDOUT_FILENO, "\n");
		free(var);
		i++;
	}
	free_envs(ordered);
}

void	export(char **cmd_args, t_shell *shell)
{
	int	i;

	shell->exit_status = EXIT_SUCCESS;
	i = 1;
	if (!cmd_args[1])
		print_env_x(shell);
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
