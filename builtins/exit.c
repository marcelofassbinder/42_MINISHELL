/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:46:53 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/08 21:46:22 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	str_is_digit(char *str)
{
	while(*str)
	{
		if (!ft_isdigit(*str))
			return(0);
		str++;
	}
	return (1);
}

void	exit_cmd(char **cmd_args, t_shell *shell)
{
	ft_printf(1, "exit\n");
	if (!cmd_args[1])
	{
		shell->exit_status = EXIT_SUCCESS;
		free_and_exit(shell);
	}
	else if (cmd_args[1] && str_is_digit(cmd_args[1]))
		exit_number(cmd_args, shell);
	else
	{
		shell->exit_status = 2;
		ft_printf(2, "minishell: exit: %s: numeric argument recquired\n", cmd_args[1]);
		free_and_exit(shell);
	}
}

void	exit_number(char **cmd_args, t_shell *shell)
{
	int status;

	status = 0;
	if (cmd_args[2])
	{
		shell->exit_status = EXIT_FAILURE;
		ft_printf(2, "minishell: exit: too many arguments\n");
		return ;
	}
	else
	{
		status = ft_atoi(cmd_args[1]);
		if (status >= INT_MIN || status <= INT_MAX)
		{
			shell->exit_status = status;
			free_and_exit(shell);
		}
	}
}
