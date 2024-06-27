/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:57:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/26 15:05:36 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* void	define_root(t_token_list *token_list)
{
	void 	*root;
	t_token *tmp;

	tmp = token_list->first;
	root = build_exec(tmp);
	while(tmp)
	{
		if (tmp->type == PIPELINE)
		{
			root = build_pipe(tmp);
		}
		tmp = tmp->next;
	}
	tmp = token_list->first;
	if (root == NULL)
	{
		while(tmp)
		{
			if (tmp->type == REDIR_IN || tmp->type ==REDIR_OUT || tmp->type == D_REDIR_OUT || tmp->type == HERE_DOC)
			{
				root = tmp;
				build_redir(tmp);
			}
			tmp = tmp->next;
		}
	}
	if (root == NULL)
		root = token_list->first;
} */
/* 
t_pipe	*build_pipe(t_token *token)
{
	t_pipe	*pipe_struct;

	pipe_struct = ft_calloc(sizeof(t_pipe), 1);
	pipe_struct->type = PIPELINE;
	while(token)
	{
		if (token->type == REDIR_IN || token->type ==REDIR_OUT || token->type == D_REDIR_OUT || token->type == HERE_DOC)
			pipe_struct->left = build_redir(token);
		
		token = token->prev;
	}
	
	while (token)
	{
		if (token->type == PIPELINE)
			pipe_struct->right = build_pipe(token);
		token = token->next;
	}
	return (pipe_struct);
} */

t_redir	*build_redir(t_token *token)
{
	t_redir	*redir;
	t_token	*find_cmd;

	redir = ft_calloc(sizeof(t_redir), 1);
	redir->type = token->type;
	find_cmd = token;
	while (token)
	{
		if (token->next && (token->next->type == W_SPACE || token->next->type == WORD))
		{
			if (token->next->type == W_SPACE)
				token = token->next;
			redir->file = ft_strdup(token->next->data);
			token = token->next;
			break;
		}
		else
			token = token->next;
	}
	if (redir->type == REDIR_OUT || redir->type == D_REDIR_OUT)
	{
		find_cmd = find_cmd->prev;
		while (find_cmd->prev && (find_cmd->type == WORD || find_cmd->type == W_SPACE))
			find_cmd = find_cmd->prev;
		redir->exec = build_exec(find_cmd);
	}
	else if (redir->type == REDIR_IN)
	{
		find_cmd = find_cmd->next;
		if (find_cmd && find_cmd->type == W_SPACE)
			find_cmd = find_cmd->next;
		find_cmd = find_cmd->next->next;
		ft_printf(1, "token enviado: %s\n", find_cmd->data);
		redir->exec = build_exec(find_cmd);		
	}
	/* else if (redir->type == HERE_DOC)
		//FUNCAO DO HERE_DOC */
	ft_printf(1, "\nfile do redir -> %s\n", redir->file);
	return (redir);
}

void test_redir(t_token_list *token_list)
{
	t_token *tmp;

	tmp = token_list->first;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == D_REDIR_OUT || tmp->type == HERE_DOC)
			build_redir(tmp);
		tmp = tmp->next;
	}
}

t_exec	*build_exec(t_token *token)
{
	t_exec	*exec;
	int		i;

	exec = ft_calloc(sizeof(t_exec), 1);
	exec->type = WORD;
	while (token)
	{
		if (token->type == WORD)
		{
			i = command_args(token);
			exec->cmd_args = ft_calloc(sizeof(char *), i + 1);
			i = 0;
			while (token && (token->type == WORD || token->type == W_SPACE))
			{
				if (token->type == WORD)
				{
					exec->cmd_args[i] = ft_strdup(token->data);
					i++;
				}
				token = token->next;
			}
			break ;
		}
		else
			token = token->next;
	}
	ft_printf(1, "\nCOMMAND ARGS:\n");
	while (*exec->cmd_args)
	{
		ft_printf(1, "command args -> %s\n", *exec->cmd_args);
		exec->cmd_args++;
	}
	return (exec);
}

int	command_args(t_token *token)
{
	int i;

	i = 0;
	while(token && (token->type == WORD || token->type == W_SPACE))
	{
		if (token->type == WORD)
			i++;
		token = token->next;
	}
	return (i);
}