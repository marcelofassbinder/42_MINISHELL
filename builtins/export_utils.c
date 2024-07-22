/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:10:00 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/22 16:11:18 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	return (0); // add mode
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