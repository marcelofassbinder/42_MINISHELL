/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:36:03 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/08 20:16:21 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_cd_args(char **cmd_args, t_shell *shell)
{
	if (cmd_args[1])
	{
		if (cmd_args[2])
		{
			safe_chdir(NULL, shell, 2);
			return (0);
		}
	}
	return (1);
}	

void	cd(char **cmd_args, t_shell *shell)
{
	char *update_old_pwd;

	if (!check_cd_args(cmd_args, shell))
		return ;
	update_old_pwd = safe_getcwd(NULL, 0, shell);
	if (!cmd_args[1] || !ft_strncmp(cmd_args[1], "--", 3)
		|| !ft_strncmp(cmd_args[1], "~", 2))
		cd_home(cmd_args, shell);
	else if (!ft_strncmp(cmd_args[1], "-", 2))
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
	if (!cmd_args[1] || !ft_strncmp(cmd_args[1], "--", 3))
	{
		home = expand(ft_strdup("HOME"), shell);
		safe_chdir(home, shell, 1);
		free(home);
	}
	else if (!ft_strncmp(cmd_args[1], "~", 2))
	{
		home = getenv("HOME");
		safe_chdir(home, shell, 1);
	}
}
