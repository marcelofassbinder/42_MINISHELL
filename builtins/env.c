/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:07:56 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/03 18:26:55 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(char **cmd_args, t_shell *shell)
{
	int		i;

	if (cmd_args[1])
	{
		ft_printf(1, "env '%s': no such file or directory\n", cmd_args[1]);
		safe_exit(shell, 127);
	}
	i = 0;
	while (shell->envp[i])
	{
		ft_printf(1, "%s\n", shell->envp[i]);
		i++;
	}
}