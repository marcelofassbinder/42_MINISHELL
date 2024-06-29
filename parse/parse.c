/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:57:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/29 15:52:03 by vivaccar         ###   ########.fr       */
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
			root = create_new_redir_e(down, token);
		else
			root = create_new_redir_r(root, token);	
		token = get_previous_redir(token);		
	}
	if (!root)
		return (down);
	return (root);
}	

void	*build_exec(t_token *token)
{
	void	*root;
	t_exec	*exec;

	exec = ft_calloc(sizeof(t_exec), 1);
	exec->cmd_args = define_cmd_args(token);
	exec->is_builtin = is_builtin(exec->cmd_args[0]);
	exec->type = WORD;
/* 	ft_printf(1, "\n--- NODE EXEC ---\n");
	ft_printf(1, "ENDERECO = %x\n", exec);
	ft_printf(1, "exec->type = %i\n", exec->type);
	ft_printf(1, "cmd_args[0] = %s\n", exec->cmd_args[0]);
	ft_printf(1, "is_builtin? = %i\n", exec->is_builtin); */
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
/* 	ft_printf(1, "\n--- NODE PIPE ---\n");
	ft_printf(1, "ENDERECO = %x\n", pipe);
	ft_printf(1, "pipe->type = %i\n", pipe->type);
	ft_printf(1, "pipe->left = %x\n", pipe->left);
	ft_printf(1, "pipe->right = %x\n", pipe->right); */
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
