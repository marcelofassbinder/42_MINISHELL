/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:18:18 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/02 20:05:51 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **cmd_args, t_shell *shell)
{
	int	i;
	int	j;
	int n_flag;

	n_flag = 0;
	i = 0;
	while(cmd_args[++i][0] == '-')
	{
		j = 1; // -nnn
		while(cmd_args[i][j] == 'n')
			j++;
 		if (j != ft_strlen(cmd_args[i]))
			break ;
		n_flag = 1;
	}
	while (cmd_args[i])
	{
		ft_printf(STDOUT_FILENO, "%s", cmd_args[i++]);
		if (cmd_args[i])
			ft_printf(STDOUT_FILENO, " ");
	}
	if (n_flag == 0)
		ft_printf(STDOUT_FILENO, "\n");
	shell->exit_status = EXIT_SUCCESS;
}

