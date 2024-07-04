/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:37:40 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/04 21:47:12 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/* void	unset(char **cmd_args, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		shell->envp = delete_envp(cmd_args[i], shell);
		i++;
	}
	shell->exit_status = 0;
} */