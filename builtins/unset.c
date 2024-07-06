/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:37:40 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/06 16:59:49 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**remove_env(char *to_remove, t_shell *shell)
{
	int		i;
	char	**new_envs;
	int		j;
	char	*cur_var;

	i = 0;
	while (shell->envp[i])
		i++;
	new_envs = ft_calloc(sizeof(char *), i);
	if (!new_envs)
		shell_error(shell, "Calloc Error: Remove env\n", 0);
	j = i;
	i = 0;
	while (i < j -1)
	{
		cur_var = get_variable_name(shell->envp[i]);
		if (!ft_strncmp(to_remove, cur_var, ft_strlen(to_remove) + 1))
		{
			i++;
			free(cur_var);
			continue;
		}
		new_envs[i] = ft_strdup(shell->envp[i]);
		free(cur_var);
		i++;
	}
	return (new_envs);
}

char	**delete_envp(char *environment, t_shell *shell)
{
	int		i;
	char	*cur_var;
	char	**new_envs;

	i = 0;
	new_envs = NULL;
	while (shell->envp[i])
	{
		cur_var = get_variable_name(shell->envp[i]);
		if (!ft_strncmp(environment, cur_var, ft_strlen(environment) + 1))
		{
			new_envs = remove_env(cur_var, shell);
			free (cur_var);
			return (new_envs);
		}
		free(cur_var);
		i++;
	}
	return (shell->envp);
}

void	unset(char **cmd_args, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		shell->envp = delete_envp(cmd_args[i], shell);
		i++;
	}
	shell->exit_status = EXIT_SUCCESS;
}