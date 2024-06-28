/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:57:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/28 17:18:05 by mfassbin         ###   ########.fr       */
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
	while (token && !is_redir(token) && token->type != PIPELINE)
		token = token->next;
	if (token && token->type == PIPELINE)
		return (NULL);
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

t_token	*find_last_or_pipe(t_token *token, int flag)
{
	while (token->next)
	{
		if (token->type == PIPELINE)
			return (token);
		token = token->next;
	}
	if (flag == 1)
		return (token);
	return (NULL);
}

t_token	*get_previous_redir(t_token *token)
{
	if (token->prev)
		token = token->prev;
	else
		return (NULL);
	while (token && token->type != PIPELINE)
	{
		if (token->type == REDIR_IN || token->type == D_REDIR_OUT || token->type == REDIR_OUT)
			return (token);
		token = token->prev;
	}
	return (NULL);
}

t_redir *create_new_redir_e(t_exec *down, t_token *token)
{
	t_redir	*redir;

	redir = ft_calloc(sizeof(t_redir), 1);
	redir->type = token->type;
	if (token->next->type == W_SPACE)
		redir->file = token->next->next->data;
	else
		redir->file = token->next->data;
	redir->down = down;
	ft_printf(1, "\n--- NODE REDIR ---\n");
	ft_printf(1, "ENDERECO = %x\n", redir);
	char *s[] = {"GENERAL", "IN_S_QUOTE", "IN_D_QUOTE", "W_SPACE", "WORD", "PIPELINE", "ENV", "REDIR_IN", "REDIR_OUT", "D_REDIR_OUT", "HERE_DOC", "S_QUOTE", "D_QUOTE", "FILE"};
	ft_printf(1, "redir->type = %s\n", s[redir->type]);
	t_exec *print = redir->down;
	ft_printf(1, "aponta para exec cmd = %s\n", print->cmd_args[0]);
	ft_printf(1, "redir->file = %s\n", redir->file);
	return (redir);
}

t_redir *create_new_redir_r(t_redir *down, t_token *token)
{
	t_redir	*redir;

	redir = ft_calloc(sizeof(t_redir), 1);
	redir->type = token->type;
	if (token->next->type == W_SPACE)
		redir->file = token->next->next->data;
	else
		redir->file = token->next->data;
	redir->down = down;
	ft_printf(1, "\n--- NODE REDIR ---\n");
	ft_printf(1, "ENDERECO = %x\n", redir);
	char *s[] = {"GENERAL", "IN_S_QUOTE", "IN_D_QUOTE", "W_SPACE", "WORD", "PIPELINE", "ENV", "REDIR_IN", "REDIR_OUT", "D_REDIR_OUT", "HERE_DOC", "S_QUOTE", "D_QUOTE", "FILE"};
	ft_printf(1, "redir->type = %s\n", s[redir->type]);
	t_redir *print = redir->down;
	ft_printf(1, "aponta para node->type = %s\n", print->file);
	ft_printf(1, "redir->file = %s\n", redir->file);
	return (redir);
}

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
	ft_printf(1, "\n--- NODE EXEC ---\n");
	ft_printf(1, "ENDERECO = %x\n", exec);
	ft_printf(1, "exec->type = %i\n", exec->type);
	ft_printf(1, "cmd_args[0] = %s\n", exec->cmd_args[0]);
	ft_printf(1, "is_builtin? = %i\n", exec->is_builtin);
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
	ft_printf(1, "\n--- NODE PIPE ---\n");
	ft_printf(1, "ENDERECO = %x\n", pipe);
	ft_printf(1, "pipe->type = %i\n", pipe->type);
	ft_printf(1, "pipe->left = %x\n", pipe->left);
	ft_printf(1, "pipe->right = %x\n", pipe->right);
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
