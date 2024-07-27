/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:18:18 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/27 22:23:14 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **cmd_args, t_shell *shell)
{
	int	i;
	int	n_option;

	i = 0;
	n_option = 0;
	if (!cmd_args[1])
	{
		ft_printf(STDOUT_FILENO, "\n");
		shell->exit_status = EXIT_SUCCESS;
		return ;
	}
	if (cmd_args[1][0] == '-' && cmd_args[1][1] == 'n')
		n_option = check_option_n(cmd_args);
	i += n_option;
	i++;
	while (cmd_args[i])
	{
		ft_printf(STDOUT_FILENO, "%s", cmd_args[i]);
		i++;
		if (cmd_args[i])
			ft_printf(STDOUT_FILENO, " ");
	}
	if (n_option == 0)
		ft_printf(STDOUT_FILENO, "\n");
	shell->exit_status = EXIT_SUCCESS;
}

int	check_option_n(char **cmd_args)
{
	int	j;
	int	i;
	int	count;

	count = 0;
	i = 1;
	while (cmd_args[i] && cmd_args[i][0] == '-')
	{
		if (cmd_args[i][0] == '-')
		{
			j = 1;
			while (cmd_args[i][j] == 'n')
				j++;
			if (j == ft_strlen(cmd_args[i]))
				count++;
		}
		i++;
	}
	return (count);
}
