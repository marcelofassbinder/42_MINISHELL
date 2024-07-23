/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:00:24 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/23 16:01:46 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_parent_error(t_shell *shell, char *str, int error)
{
	shell->exit_status = EXIT_FAILURE;
	if (error == 1) // erro de comando
	{
		shell->exit_status = EXIT_CMD;
		ft_printf(STDERR_FILENO, "%s: command not found\n", str);
	} 
	else if (error == 2) // erro de arquivo ou diretorio
		ft_printf(STDERR_FILENO, "minishell: %s: No such file or directory\n", str);
	else if (error == 3) // erro de permissao
		ft_printf(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
	else if (error == 4) // erro de permissao
		ft_printf(STDERR_FILENO, "minishell: %s: ambiguous redirect\n", str);
	else
		ft_printf(STDERR_FILENO, "%s\n", str);
	return (0);
}

bool	has_no_file(t_shell *shell, t_redir *redir, int exit_flag)
{
	if (!redir->file)
	{
		if (shell->process == CHILD)
			shell_error(shell, "", 4, exit_flag);
		return (return_parent_error(shell, "", 4));
	}
	if (!redir->file[0])
	{
		if (shell->process == CHILD)
			shell_error(shell, redir->file, 2, exit_flag);
		return (return_parent_error(shell, "", 2));
	}
	return (1);
}

//teste
int	has_pipe(t_shell *shell)
{
	t_token *token;

	token = shell->token_list->first;
	while(token)
	{
		if (token->type == PIPELINE)
			return (1);
		token = token->next;
	}
	return (0);
}