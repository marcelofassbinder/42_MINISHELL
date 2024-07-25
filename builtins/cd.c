/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:36:03 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/25 22:58:14 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char **cmd_args, t_shell *shell)
{
	char	*update_old;
	char	*old_pwd_env;

	if (cmd_args[1])
	{
		if (cmd_args[2])
			return (safe_chdir(NULL, shell, 2));
	}
	update_old = safe_getcwd(NULL, 0, shell);
	if (!cmd_args[1] || !ft_strcmp(cmd_args[1], "--")
		|| !ft_strcmp(cmd_args[1], "~"))
		cd_home(cmd_args, shell);
	else if (!ft_strcmp(cmd_args[1], "-"))
	{
		old_pwd_env = ft_get_env("OLDPWD", shell);
		if (!cd_old_dir(old_pwd_env, update_old, shell))
			return ;
	}
	else
		safe_chdir(cmd_args[1], shell, 0);
	update_old_pwd(update_old, shell);
	//shell->exit_status = EXIT_SUCCESS;
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

int	cd_old_dir(char *old_pwd_env, char *update_old, t_shell *shell)
{
	if (old_pwd_env)
	{
		safe_chdir(old_pwd_env, shell, 0);
		pwd(shell);
		free(old_pwd_env);
		return (1);
	}
	else
	{
		free(update_old);
		return_parent_error(shell, "minishell: cd: OLDPWD not set", 0);
		return (0);
	}
}

void	update_old_pwd(char *update_old, t_shell *shell)
{
	char	*old_pwd_str;

	old_pwd_str = ft_strdup("OLDPWD=");
	old_pwd_str = ft_strjoin(old_pwd_str, update_old);
	if (env_exist("OLDPWD", shell->envp))
		shell->envp = replace_env(old_pwd_str, shell, 0);
	else
		shell->envp = set_new_env(old_pwd_str, shell, 0);
	free(update_old);
	free(old_pwd_str);
}
