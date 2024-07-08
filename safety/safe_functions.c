/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:42:54 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/08 19:05:05 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	safe_fork(t_shell *shell)
{
	int pid;

	pid = fork();
	if (pid == -1)
		shell_error(shell, "Error while creating a child process", 0);
	return (pid);
}

void safe_chdir(char *chdir_arg, t_shell *shell, int flag)
{
	if (flag == 2)
	{
		ft_printf(2, "minishell: cd: too many arguments\n");
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	else if (chdir(chdir_arg) == -1)
	{
		if (flag == 1)
			ft_printf(2, "minishell: cd: HOME not set\n");
		else
			ft_printf(2, "minishell: cd: %s: no such file or directory\n", chdir_arg);
		shell->exit_status = EXIT_FAILURE;
	}
}

char *safe_getcwd(char *buf, size_t size, t_shell *shell)
{
	char *cwd;

	cwd = getcwd(buf, size);
	if (!cwd)
	{
		free(cwd);
		shell->exit_status = EXIT_FAILURE;
		shell_error(shell, "PWD Error", 0);
		return (NULL);
	}
	return(cwd);
}