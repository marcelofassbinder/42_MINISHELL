/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:17:12 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/05 13:32:01 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envs(char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	safe_exit(t_shell *shell, int status)
{
	if (shell->token_list)
	{
		if (shell->token_list->first)
			free_token_list(shell->token_list);
		free(shell->token_list);
	}
	if (shell->root)
		free_tree(shell->root);
	if (shell->line)
		free(shell->line);
	if (shell->envp)
		free_envs(shell->envp);
	if (shell)
		free(shell);
	exit(status);
}