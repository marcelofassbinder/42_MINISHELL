/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:17:12 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/01 18:26:37 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_exec(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->cmd_args[i])
	{
		free(exec->cmd_args[i]);
		i++;
	}
	free(exec->cmd_args);
	free(exec);
}

void	free_redir(t_redir *redir)
{
	void	*down;

	down = redir->down;
	free(redir);
	free_tree(down);
}

void	free_pipe(t_pipe *pipe)
{
	void	*left;
	void	*right;

	left = pipe->left;
	right = pipe->right;
	free(pipe);
	free_tree(left);
	free_tree(right);
}

void	free_tree(void *root)
{
	enum e_type	node_type;


	if (!root)
		return ;
	node_type = *(enum e_type *)root;
	if (node_type == WORD)
		free_exec((t_exec *)root);
	else if (node_type == REDIR_IN || node_type == REDIR_OUT || node_type == D_REDIR_OUT)
		free_redir((t_redir *)root);
	else if (node_type == PIPELINE)
		free_pipe((t_pipe *)root);
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
	if (shell)
		free(shell);
	exit(status);
}