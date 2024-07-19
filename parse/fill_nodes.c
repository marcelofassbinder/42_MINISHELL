/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:17:02 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/19 13:52:13 by vivaccar         ###   ########.fr       */
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

char	*get_redir_file(t_token *token)
{
	char *file;

	if (token->next->type == W_SPACE)
	{
		if (!token->next->next)
			file = NULL;
		else
			file = token->next->next->data;
	}
	else
		file = token->next->data;
	return (file);
}

t_redir *create_new_redir(void *down, t_token *token)
{
	t_redir		*redir;
	enum e_type	node_type;

	redir = ft_calloc(sizeof(t_redir), 1);
	redir->type = token->type;
	redir->file = get_redir_file(token);
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

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while(token && token->type != PIPELINE)
	{
		if (token->type == WORD || token->type == T_NULL)
			count++;
		token = token->next;
	}
	return (count);
}


char	**define_cmd_args(t_token *token)
{
	char	**cmd_args;
	int		counter;
	int		i;

	counter = count_args(token);
	cmd_args = ft_calloc(sizeof(char *), counter + 1);
	i = 0;
	while(token && token->type != PIPELINE)
	{
		if (token->type == WORD || token->type == T_NULL)
		{
			cmd_args[i] = ft_strdup(token->data);
			i++;
		}
		token = token->next;
	}
	return(cmd_args);
}