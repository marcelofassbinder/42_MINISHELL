/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:36 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/27 22:25:47 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			ft_printf(2, "minishell: export '%s': not a valid identifier\n",
				cmd_args[i]);
			shell->exit_status = 2;
			i++;
			continue ;
		}
		shell->envp = add_envp(cmd_args[i], shell);
		i++;
	}
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
