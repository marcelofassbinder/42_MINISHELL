/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:57:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/27 20:13:01 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	has_word(t_token *token)
{
	while (token && token->type != PIPELINE)
	{
		if (token->type == WORD || token->type == T_NULL)
			return (true);
		token = token->next;
	}
	return (false);
}

void	*build_redir(void *down, t_token *token, t_shell *shell)
{
	t_token	*last_token;
	void	*root;

	root = NULL;
	last_token = find_last_or_pipe(token, 1);
	token = get_previous_redir(last_token);
	while (token)
	{
		if (last_redir(token))
			root = create_new_redir(down, token, shell, 0);
		else
			root = create_new_redir(root, token, shell, 0);
		token = get_previous_redir(token);
	}
	if (!root)
		return (down);
	return (root);
}

void	*build_exec(t_token *token, t_shell *shell)
{
	void	*root;
	t_exec	*exec;

	if (has_word(token))
	{
		exec = ft_calloc(sizeof(t_exec), 1);
		exec->cmd_args = define_cmd_args(token);
		exec->is_builtin = is_builtin(exec->cmd_args[0]);
		exec->type = WORD;
	}
	else
		exec = NULL;
	root = build_redir(exec, token, shell);
	return (root);
}

t_pipe	*build_pipe(void *left, void *right)
{
	t_pipe	*pipe;

	pipe = ft_calloc(sizeof(t_pipe), 1);
	pipe->left = left;
	pipe->right = right;
	pipe->type = PIPELINE;
	return (pipe);
}

void	*parse(t_token *token, t_shell *shell)
{
	void	*root;

	root = build_exec(token, shell);
	token = find_last_or_pipe(token, 0);
	if (token)
		root = build_pipe(root, parse(token->next, shell));
	return (root);
}
