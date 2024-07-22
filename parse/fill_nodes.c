/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:17:02 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/22 12:59:17 by mfassbin         ###   ########.fr       */
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
	if (token->next->type == W_SPACE)
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

t_redir *define_redir(void *down, t_token *token, t_shell *shell)
{
	t_redir *redir;
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
		else if (node_type == REDIR_IN || node_type == REDIR_OUT || node_type == D_REDIR_OUT || node_type == HERE_DOC)
			redir->down = (t_redir *)down;
	}
	else
		redir->down = NULL;
	return (redir);
}

t_redir *create_new_redir(void *down, t_token *token, t_shell *shell, int flag)
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

bool	is_local_variable(t_token *token)
{
	if (token->status == GENERAL && token->type == WORD 
		&& ft_strchr(token->data, '='))
		return (true);
	return (false);
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

int	count_args(t_token *token)
{
	int	count;
	int	flag;

	flag = 0;
	count = 0;
	while(token && token->type != PIPELINE)
	{
		if (is_local_variable(token) && flag == 0)
		{
			token = get_next_token(token->next);
			continue ;
		}
		else if (token->type == WORD || token->type == T_NULL)
			count++;
		token = token->next;
		flag = 1;
	}
	return (count);
}


char	**define_cmd_args(t_token *token)
{
	char	**cmd_args;
	int		counter;
	int		i;
	int		flag;
	
	flag = 0;
	counter = count_args(token);
	cmd_args = ft_calloc(sizeof(char *), counter + 1);
	i = 0;
	while(token && token->type != PIPELINE)
	{
		if (is_local_variable(token) && flag == 0)
		{
			token = get_next_token(token->next);
			continue ;
		}
		else if (token->type == WORD || token->type == T_NULL)
		{
			cmd_args[i] = ft_strdup(token->data);
			i++;
		}
		flag = 1;
		token = token->next;
	}
	return(cmd_args);
}
