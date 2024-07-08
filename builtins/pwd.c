/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:35:16 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/08 19:47:27 by vivaccar         ###   ########.fr       */
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
		shell->exit_status = EXIT_FAILURE;
		shell_error(shell, "PWD Error", 0, true);
	}
	ft_printf(1, "%s\n", buf);
	free(buf);
	shell->exit_status = EXIT_SUCCESS;
}