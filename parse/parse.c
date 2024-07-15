/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:57:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/15 16:19:34 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*build_redir(void *down, t_token *token)
{
	t_token	*last_token;
	void	*root;

	root = NULL;
	last_token = find_last_or_pipe(token, 1);
	token = get_previous_redir(last_token);
	while (token)
	{
		if (last_redir(token))
			root = create_new_redir(down, token);
		else
			root = create_new_redir(root, token);
		token = get_previous_redir(token);
	}
	if (!root)
		return (down);
	return (root);
}	

bool	has_word(t_token *token)
{
	while (token && token->type != PIPELINE)
	{
		if (token->type == WORD)
			return (true);
		token = token->next;
	}
	return (false);
}

void	*build_exec(t_token *token)
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
/* 	ft_printf(STDOUT_FILENO, "\n--- NODE EXEC ---\n");
	ft_printf(STDOUT_FILENO, "ENDERECO = %x\n", exec);
	ft_printf(STDOUT_FILENO, "exec->type = %i\n", exec->type);
	ft_printf(STDOUT_FILENO, "cmd_args[0] = %s\n", exec->cmd_args[0]);
	ft_printf(STDOUT_FILENO, "is_builtin? = %i\n", exec->is_builtin); */
	else
		exec = NULL;
	root = build_redir(exec, token);
	return(root);
}

t_pipe	*build_pipe(void *left, void *right)
{
	t_pipe	*pipe;

	pipe = ft_calloc(sizeof(t_pipe), 1);
	pipe->left = left;
	pipe->right = right;
	pipe->type = PIPELINE;
/* 	ft_printf(STDOUT_FILENO, "\n--- NODE PIPE ---\n");
	ft_printf(STDOUT_FILENO, "ENDERECO = %x\n", pipe);
	ft_printf(STDOUT_FILENO, "pipe->type = %i\n", pipe->type);
	ft_printf(STDOUT_FILENO, "pipe->left = %x\n", pipe->left);
	ft_printf(STDOUT_FILENO, "pipe->right = %x\n", pipe->right); */
	return (pipe);
}

void	*parse(t_token *token)
{
	void	*root;

	root = build_exec(token);
	token = find_last_or_pipe(token, 0);
	if (token)
		root = build_pipe(root, parse(token->next));
	return (root);
}
