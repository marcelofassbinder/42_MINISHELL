/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:35:16 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/06 16:59:49 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_shell *shell)
{
	char *buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
	{
		free(buf);
		ft_printf(STDERR_FILENO, "PWD Error\n");
		shell->exit_status = EXIT_FAILURE;
		safe_exit(shell);
	}
	ft_printf(1, "%s\n", buf);
	free(buf);
	shell->exit_status = EXIT_SUCCESS;
}