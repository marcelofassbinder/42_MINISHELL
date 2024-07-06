/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:36:03 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/06 22:24:07 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char **cmd_args, t_shell *shell)
{
	char *home;
	char *old_path;

	if (cmd_args[2])
	{
		ft_printf(2, "minishell: cd: too many arguments\n");
		shell->exit_status = EXIT_FAILURE;
	}
	old_path = NULL;
	old_path = getcwd(old_path, 0);
	if (!cmd_args[1] || !ft_strncmp(cmd_args[1], "--", 3) || !ft_strncmp(cmd_args[1], "~", 2))
	{
		if (!cmd_args[1] || !ft_strncmp(cmd_args[1], "--", 3))
			home = expand(ft_strdup("HOME"), shell);
		else if (!ft_strncmp(cmd_args[1], "~", 2))
			home = getenv("HOME");
		if (chdir(home) == -1)
		{
			ft_printf(2, "minishell: cd: HOME not set\n");
			shell->exit_status = EXIT_FAILURE;
		}
	}
	else if (!ft_strncmp(cmd_args[1], "/", 2))
		chdir("/");
	else if (!ft_strncmp(cmd_args[1], "-", 2))
	{
		/* chdir(old_path);	
		pwd(shell);
		old_path = getcwd(old_path, 0); */
		//arrumar esta parte
	}
	else
		chdir(cmd_args[1]);
	shell->exit_status = EXIT_SUCCESS;
}
