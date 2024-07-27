/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:48:24 by mfassbin          #+#    #+#             */
/*   Updated: 2024/07/27 15:02:08 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"	

void	find_files(t_token_list *token_list)
{
	t_token	*tmp;

	tmp = token_list->first;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (tmp->prev && is_redir(tmp->prev))
				tmp->type = T_FILE;
			else if (!tmp->prev)
			{
				tmp = tmp->next;
				continue ;
			}
			else if (tmp->prev->prev && is_redir(tmp->prev->prev))
				tmp->type = T_FILE;
		}
		tmp = tmp->next;
	}
}

void	token_redir_pipe(t_token_list *token_list)
{
	t_token	*tmp;

	tmp = token_list->first;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT && tmp->next && tmp->next->type == PIPELINE)
			delete_node(token_list, tmp->next);
		tmp = tmp->next;
	}
}

void	repeated_quotes(t_token_list *token_list)
{
	t_token	*tmp;

	tmp = token_list->first;
	while (tmp)
	{
		if ((tmp->status == GENERAL) && (tmp->type == D_QUOTE || tmp->type == S_QUOTE))
		{
			if ((tmp->next && tmp->next->status == GENERAL) && (tmp->next->type == D_QUOTE || tmp->next->type == S_QUOTE))
			{
				tmp->data = ft_strdup("");
				tmp->type = T_NULL;
				delete_node(token_list, tmp->next);
			}
		}
		tmp = tmp->next;
	}
}

void	tokenizer(t_token_list *token_list, char *line, t_shell *shell)
{
	enum e_status 	status;
	int i;

	status = GENERAL;
	i = 0;
	while(line[i])
	{
		if (is_type_word(line[i]))
		{
			i = append_word(token_list, &line[i], status, i);
			if (!line[i])
				break;
		}
		status = append_quotes(token_list, line[i], status);
		if (ft_isspace(line[i]))
			append_token(token_list, &line[i], status, W_SPACE);
		if (line[i] == PIPE)
			append_token(token_list, &line[i], status, PIPELINE);
		if (line[i] == DOLLAR)
			append_token(token_list, &line[i], status, ENV);
		if (line[i] == R_IN || line[i] == R_OUT)
			i = append_redir(token_list, &line[i], status, i);
		i++;
	}
	prepare_tokens(token_list, shell);
}

void print_token_list(t_token_list *token_list)
{
	int i;
	t_token *ptr;
	char *s[] = {"GENERAL", "IN_S_QUOTE", "IN_D_QUOTE", "W_SPACE", "WORD", "PIPELINE", "ENV", "REDIR_IN", "REDIR_OUT", "D_REDIR_OUT", "HERE_DOC", "S_QUOTE", "D_QUOTE", "FILE", "NULL"};

	ptr = token_list->first;
	i = 1;
	printf("| %-3s | %-20s | %-3s | %-15s | %-15s |\n", "ID", "TOKEN", "LEN", "STATUS", "TYPE");
    printf("|-----|----------------------|-----|-----------------|-----------------|\n");
	while (ptr != NULL)
	{
		printf("| %-3d | %-20s | %-3d | %-15s | %-15s |\n", i, ptr->data, ft_strlen(ptr->data), s[ptr->status], s[ptr->type]);
		printf("|-----|----------------------|-----|-----------------|-----------------|\n");
		ptr = ptr->next;	
		i++;
	}
}

enum e_status change_status(t_token_list *token_list, char c, enum e_status status, enum e_type type)
{
	enum e_status new_status;

	if (type == S_QUOTE)
		new_status = IN_S_QUOTE;
	else if (type == D_QUOTE)
		new_status = IN_D_QUOTE;
	if (status == GENERAL)
	{
		append_token(token_list, &c, status, type);
		status = new_status;
	}
	else if (status == new_status)
	{
		status = GENERAL;
		append_token(token_list, &c, status, type);
	}
	else
		append_token(token_list, &c, status, type);
	return (status);	
}
