/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:17:02 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/18 18:58:33 by mfassbin         ###   ########.fr       */
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
	if (!ft_strcmp(str, "env"))
		return (true);
	if (!ft_strcmp(str, "exit"))
		return (true);
	return (false);
}

t_redir *create_new_redir(void *down, t_token *token, t_shell *shell, int flag)
{
	t_redir		*redir;
	enum e_type	node_type;
	static int	id = 0;

	if (flag == 1)
	{
		id = 0;
		return (NULL);
	}
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
		else if (node_type == REDIR_IN || node_type == REDIR_OUT || node_type == D_REDIR_OUT || node_type == HERE_DOC)
			redir->down = (t_redir *)down;
	}
	else
		redir->down = NULL;
	if (redir->type == HERE_DOC)
	{
		printf("CREATE NEW REDIR\n");
		id = shell->count_hd - id - 1;
		redir->id = id;
		printf("REDIR->id = %i\n", redir->id);
		printf("REDIR->eof = %s\n", redir->file);
		//run_here_doc(redir, shell);
	}
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