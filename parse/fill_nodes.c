/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:17:02 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/03 15:58:47 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(char *str)
{
	if (!str)
		return (false);
	if (!ft_strncmp(str, "pwd", ft_strlen("pwd") + 1))
		return (true);
	if (!ft_strncmp(str, "echo", ft_strlen("echo") + 1))
		return (true);
	if (!ft_strncmp(str, "cd", ft_strlen("cd") + 1))
		return (true);
	if (!ft_strncmp(str, "export", ft_strlen("export") + 1))
		return (true);
	if (!ft_strncmp(str, "unset", ft_strlen("unset") + 1))
		return (true);
	if (!ft_strncmp(str, "env", ft_strlen("env") + 1))
		return (true);
	if (!ft_strncmp(str, "exit 2 " , ft_strlen("exit") + 1))
		return (true);
	return (false);
}

t_redir *create_new_redir(void *down, t_token *token)
{
	t_redir		*redir;
	enum e_type	node_type;

	redir = ft_calloc(sizeof(t_redir), 1);
	redir->type = token->type;
	if (token->next->type == W_SPACE)
		redir->file = token->next->next->data;
	else
		redir->file = token->next->data;
	if (down)
	{
		node_type = *(enum e_type *)down;
		if (node_type == WORD)
			redir->down = (t_exec *)down;
		else if (node_type == REDIR_IN || node_type == REDIR_OUT || node_type == D_REDIR_OUT)
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
		if (token->type == WORD)
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
		if (token->type == WORD)
		{
			cmd_args[i] = ft_strdup(token->data);
			i++;
		}
		token = token->next;
	}
	return(cmd_args);
}