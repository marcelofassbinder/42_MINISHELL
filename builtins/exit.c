/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:46:53 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/27 18:57:55 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_cmd(char **cmd_args, t_shell *shell)
{
	ft_printf(1, "exit\n");
	if (!cmd_args[1])
		free_and_exit(shell);
	else if (cmd_args[1] && str_is_digit(cmd_args[1]))
		exit_number(cmd_args, shell);
	else
	{
		shell->exit_status = EXIT_SYNTAX;
		ft_printf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", cmd_args[1]);
		free_and_exit(shell);
	}
}

void	exit_line(t_shell *shell)
{
	int	status;

	status = shell->exit_status;
	free_envs(shell->envp);
	free(shell->line);
	free(shell);
	ft_printf(STDOUT_FILENO, "exit\n");
	exit(status);
}

void	exit_number(char **cmd_args, t_shell *shell)
{
	int	status;

	status = 0;
	if (cmd_args[2])
	{
		shell->exit_status = EXIT_FAILURE;
		ft_printf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return ;
	}
	else
	{
		status = ft_atoi(cmd_args[1]);
		if (status >= INT_MIN || status <= INT_MAX)
		{
			while (status < 0)
				status += 256;
			status = status % 256;
			shell->exit_status = status;
			free_and_exit(shell);
		}
	}
}

int	str_is_digit(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
