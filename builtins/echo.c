/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:18:18 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/01 17:29:57 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **cmd_args, t_shell *shell)
{
	int	i;

	(void)shell;
	i = 1;
	while (cmd_args[i])
	{
		ft_printf(1, "%s", cmd_args[i]);
		i++;
		if (cmd_args[i])
			ft_printf(1, " ");
	}	
	ft_printf(1, "\n");
}