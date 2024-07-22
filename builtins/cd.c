/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:36:03 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/22 13:41:14 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char **cmd_args, t_shell *shell)
{
	char *update_old_pwd;

	if (cmd_args[1])
	{
		if (cmd_args[2])
			safe_chdir(NULL, shell, 2);
	}
	update_old_pwd = safe_getcwd(NULL, 0, shell);
	if (!cmd_args[1] || !ft_strcmp(cmd_args[1], "--")
		|| !ft_strcmp(cmd_args[1], "~"))
		cd_home(cmd_args, shell);
	else if (!ft_strcmp(cmd_args[1], "-"))
	{
		safe_chdir(shell->old_pwd, shell, 0);
		pwd(shell);
	}
	else
		safe_chdir(cmd_args[1], shell, 0);
	free(shell->old_pwd);
	shell->old_pwd = update_old_pwd;
	shell->exit_status = EXIT_SUCCESS;
}

void	cd_home(char **cmd_args, t_shell *shell)
{
	char	*home;

	home = NULL;
	if (!cmd_args[1] || !ft_strcmp(cmd_args[1], "--"))
	{
		home = expand(ft_strdup("HOME"), shell);
		safe_chdir(home, shell, 1);
		free(home);
	}
	else if (!ft_strcmp(cmd_args[1], "~"))
	{
		home = getenv("HOME");
		safe_chdir(home, shell, 1);
	}
}
