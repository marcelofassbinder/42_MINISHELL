/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:17:02 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/29 16:54:36 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
/* 	ft_printf(1, "\n--- NODE REDIR ---\n");
	ft_printf(1, "ENDERECO = %x\n", redir);
	char *s[] = {"GENERAL", "IN_S_QUOTE", "IN_D_QUOTE", "W_SPACE", "WORD", "PIPELINE", "ENV", "REDIR_IN", "REDIR_OUT", "D_REDIR_OUT", "HERE_DOC", "S_QUOTE", "D_QUOTE", "FILE"};
	ft_printf(1, "redir->type = %s\n", s[redir->type]);
	t_exec *print = redir->down;
	ft_printf(1, "aponta para exec cmd = %s\n", print->cmd_args[0]);
	ft_printf(1, "redir->file = %s\n", redir->file); */
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
/* 	ft_printf(1, "\n--- NODE REDIR ---\n");
	ft_printf(1, "ENDERECO = %x\n", redir);
	char *s[] = {"GENERAL", "IN_S_QUOTE", "IN_D_QUOTE", "W_SPACE", "WORD", "PIPELINE", "ENV", "REDIR_IN", "REDIR_OUT", "D_REDIR_OUT", "HERE_DOC", "S_QUOTE", "D_QUOTE", "FILE"};
	ft_printf(1, "redir->type = %s\n", s[redir->type]);
	t_redir *print = redir->down;
	ft_printf(1, "aponta para node->type = %s\n", print->file);
	ft_printf(1, "redir->file = %s\n", redir->file); */
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