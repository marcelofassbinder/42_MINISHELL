/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:57:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/28 15:24:22 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_builtin(char *str)
{
	if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		return (true);
	if (!ft_strncmp(str, "echo", ft_strlen(str)))
		return (true);
	if (!ft_strncmp(str, "cd", ft_strlen(str)))
		return (true);
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (true);
	if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (true);
	if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (true);
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (true);
	return (false);
}

t_token	*get_next_redir(t_token *token)
{
	if (token->next)
		token = token->next;
	else 
		return (NULL);
	while (token && token->type != REDIR_IN && token->type != REDIR_OUT && token->type != D_REDIR_OUT)
	{
		token = token->next;
	}
	return(token);
}

bool	last_redir(t_token *token)
{
	if (token->type != REDIR_IN && token->type != REDIR_OUT && token->type != D_REDIR_OUT)
		return (false);
	token = get_next_redir(token);
	if (!token)
		return (true);
	return (false);
}

void	*build_redir(void *down, t_token *token)
{
	t_redir	*redir;
	//void	*root;
	
	if(last_redir(token))
	{
		redir = ft_calloc(sizeof(t_redir), 1);
		redir->file = token->next->next->data;
		redir->type = token->type;
		redir->down = down;
		return ((void *) redir);
	}
	token = get_next_redir(token);
	while (token)
	{
		redir = ft_calloc(sizeof(t_redir), 1);
		redir->file = token->next->next->data;
		redir->type = token->type;
		token = get_next_redir(token);
		if (token)
			redir->down = build_redir(down, token);
	}
	return (NULL);
}

t_token	*find_last_or_pipe(t_token *token)
{
	while (token->next)
	{
		if (token->type == PIPELINE)
			return (token);
		token = token->next;
	}
	return (token);
}

t_token	*get_previous_redir(t_token *token)
{
	if (token->prev)
		token = token->prev;
	else
		return (NULL);
	while (token)
	{
		if (token->type == REDIR_IN || token->type == D_REDIR_OUT || token->type == REDIR_OUT)
			return (token);
		token = token->prev;
	}
	return (token);
}

t_redir *create_new_redir(void *down, t_token *token)
{
	t_redir	*redir;

	redir = ft_calloc(sizeof(t_redir), 1);
	redir->type = token->type;
	if (token->next->type == W_SPACE)
		redir->file = token->next->next->data;
	else
		redir->file = token->next->data;
	redir->down = down;
	ft_printf(1, "--- REDIR ---\n");
	ft_printf(1, "redir->type = %i\n", redir->type);
	ft_printf(1, "aponta para = %s\n", redir->down->type);
	ft_printf(1, "redir->file = %s\n", redir->file);
	return (redir);
}

void	*build_redir2(void *down, t_token *token)
{
	t_token	*last_token;
	void	*root;

	root = NULL;
	last_token = find_last_or_pipe(token);
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
	ft_printf(1, "\ncounter of args = %i\n", counter);
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
	i = 0;
	while(cmd_args[i])
	{
		ft_printf(1, "CMD_ARGS[%i] = %s\n", i, cmd_args[i]);
		i++;
	}
	return(cmd_args);
}

void	*build_exec(t_token *token)
{
	void	*root;
	t_exec	*exec;

	exec = ft_calloc(sizeof(t_exec), 1);
	exec->cmd_args = define_cmd_args(token);
	exec->is_builtin = is_builtin(exec->cmd_args[0]);
	exec->type = WORD;
	root = build_redir2(exec, token);
	ft_printf(1, "--- EXEC ---\n");
	ft_printf(1, "exec->type = %i\n", exec->type);
	ft_printf(1, "cmd_args[0] = %s\n", exec->cmd_args[0]);
	ft_printf(1, "is_builtin? = %i\n", exec->is_builtin);
	return(root);
}
/* 
void	*parse(t_token *token)
{
	void	*root;

	root = build_exec(token);
	token = get_next_pipe(token);
	if (token)
		root = build_pipe(root, parse(token->next));
	return (root);
} */