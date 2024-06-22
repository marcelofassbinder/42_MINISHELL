/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:48:24 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/22 17:25:30 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	tokenizer(t_token_list *token_list, char *line)
{
	enum t_status 	status;
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
		if (line[i] == REDIRECT_IN || line[i] == REDIRECT_OUT)
			i = append_redir(token_list, &line[i], status, i);
		i++;
	}
	print_token_list(token_list);
	//expand(token_list);
	free_token_list(token_list);
}

void print_token_list(t_token_list *token_list)
{
	int i;
	t_token *ptr;
	char *s[] = {"GENERAL", "IN_S_QUOTE", "IN_D_QUOTE", "W_SPACE", "WORD", "PIPELINE", "ENV", "REDIR_IN", "REDIR_OUT", "D_REDIR_OUT", "HERE_DOC", "S_QUOTE", "D_QUOTE"};

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

int is_type_word(char c)
{
	if (!ft_isspace(c) && c != S_QTE && c != D_QTE && c != PIPE && 
		c != DOLLAR && c != REDIRECT_IN && c != REDIRECT_OUT && c)
				return (1);
	return (0);
}

enum t_status append_quotes(t_token_list *token_list, char c, enum t_status status)
{
	if (c == S_QTE)
		status = change_status(token_list, c, status, S_QUOTE);
	else if (c == D_QTE)
		status = change_status(token_list, c, status, D_QUOTE);
	return (status);
}

enum t_status change_status(t_token_list *token_list, char c, enum t_status status, enum t_type type)
{
	enum t_status new_status;

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
