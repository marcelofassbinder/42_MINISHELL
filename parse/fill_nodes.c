/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:17:02 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/27 20:10:54 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(char *str)
{
	if (!str)
		return (false);
	if (!ft_strcmp(str, "pwd"))
		return (true);
	if (!ft_strcmp(str, "echo"))
		return (true);
	if (!ft_strcmp(str, "cd"))
		return (true);
	if (!ft_strcmp(str, "export"))
		return (true);
	if (!ft_strcmp(str, "unset"))
		return (true);
	if (!ft_strcmp(str, "exit"))
		return (true);
	return (false);
}

void	define_redir_file(t_redir *redir, t_token *token)
{
	if (!token->next)
	{
		redir->file = NULL;
		redir->file_status = GENERAL;
	}
	else if (token->next->type == W_SPACE)
	{
		if (!token->next->next)
		{
			redir->file = NULL;
			redir->file_status = GENERAL;
		}
		else
		{
			redir->file = token->next->next->data;
			redir->file_status = token->next->next->status;
		}
	}
	else
	{
		redir->file = token->next->data;
		redir->file_status = token->next->status;
	}
}

t_redir	*define_redir(void *down, t_token *token, t_shell *shell)
{
	t_redir		*redir;
	enum e_type	node_type;

	redir = ft_calloc(sizeof(t_redir), 1);
	if (!redir)
		shell_error(shell, "Calloc error: redir", 0, true);
	redir->type = token->type;
	define_redir_file(redir, token);
	if (down)
	{
		node_type = *(enum e_type *)down;
		if (node_type == WORD)
			redir->down = (t_exec *)down;
		else if (node_type == REDIR_IN || node_type == REDIR_OUT
			|| node_type == D_REDIR_OUT || node_type == HERE_DOC)
			redir->down = (t_redir *)down;
	}
	else
		redir->down = NULL;
	return (redir);
}

t_redir	*create_new_redir(void *down, t_token *token, t_shell *shell, int flag)
{
	t_redir		*redir;
	static int	id = 0;

	if (flag == 1)
	{
		id = 0;
		return (NULL);
	}
	redir = define_redir(down, token, shell);
	if (redir->type == HERE_DOC)
	{
		redir->id = id;
		id ++;
	}
	return (redir);
}

t_token	*get_next_token(t_token *token)
{
	if (!token)
		return (token);
	while (token->type == W_SPACE)
	{
		token = token->next;
		if (!token)
			return (token);
	}
	return (token);
}
