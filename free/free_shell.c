/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:17:12 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/31 15:46:10 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_and_exit(t_shell *shell)
{
	int	status;

	status = shell->exit_status;
	free_all_allocated_memory(shell, 1);
	exit(status);
}

void	shell_error(t_shell *shell, char *str, int error, bool exit_flag)
{
	int	status;

	status = shell->exit_status;
	error_message(error, str);
	free_all_allocated_memory(shell, 1);
	if (exit_flag)
		exit(status);
}

void	free_all_allocated_memory(t_shell *shell, int free_shell)
{
	if (shell->token_list)
	{
		if (shell->token_list->first)
			free_token_list(shell->token_list);
		free(shell->token_list);
	}
	if (shell->envp)
		free_envs(shell->envp);
	if (shell->root)
		free_tree(shell->root);
	if (shell->line)
		free(shell->line);
	if (shell->array_fd_here_doc)
		free(shell->array_fd_here_doc);
	if (free_shell && shell)
		free(shell);
}

void	error_message(int error, char *str)
{
	if (error == 1)
		ft_printf(STDERR_FILENO, "%s: command not found\n", str);
	else if (error == 2)
		ft_printf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			str);
	else if (error == 3)
		ft_printf(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
	else if (error == 4)
		ft_printf(STDERR_FILENO, "minishell: ambiguous redirect\n", str);
	else if (error == 5)
		ft_printf(STDERR_FILENO, "minishell: %s: Is a directory\n", str);
	else if (error == 6)
		ft_printf(STDERR_FILENO, "minishell: %s: Not a directory\n", str);
	else
		ft_printf(STDERR_FILENO, "%s\n", str);
}

void	free_envs(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
