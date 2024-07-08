/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:07:56 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/08 18:19:05 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(char **cmd_args, t_shell *shell)
{
	int		i;

	if (cmd_args[1])
	{
		if (cmd_args[1][0] == '-')
		{
			ft_printf(STDERR_FILENO, "env '%s': no such file or directory\n", cmd_args[1]);
			shell->exit_status = 125;
			return ;		
		}
		ft_printf(STDERR_FILENO, "env '%s': no such file or directory\n", cmd_args[1]);
		shell->exit_status = EXIT_CMD;
		return ;
	}
	i = 0;
	while (shell->envp[i])
	{
		ft_printf(1, "%s\n", shell->envp[i]);
		i++;
	}
	shell->exit_status = EXIT_SUCCESS;
}
