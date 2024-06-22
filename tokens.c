/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:48:24 by mfassbin          #+#    #+#             */
/*   Updated: 2024/06/22 12:46:19 by vivaccar         ###   ########.fr       */
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
		if (is_type_word(line[i], status))
		{
			i = append_word(token_list, &line[i], status, i);
			if (!line[i])
				break;
		}
		status = change_status(line[i], status);
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
	expand(token_list);
	free_token_list(token_list);
}

void print_token_list(t_token_list *token_list)
{
	int i;
	t_token *ptr;
	char *s[] = {"GENERAL", "IN_S_QUOTE", "IN_D_QUOTE", "W_SPACE", "WORD", "PIPELINE", "ENV", "REDIR_IN", "REDIR_OUT", "D_REDIR_OUT", "HERE_DOC"};

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

int is_type_word(char c, enum t_status status)
{
	if ((!ft_isspace(c) && c != S_QUOTE && c != D_QUOTE && c != PIPE && 
		c != DOLLAR && c != REDIRECT_IN && c != REDIRECT_OUT && c) || (c == S_QUOTE 
			&& status == IN_D_QUOTE && c) || (c == D_QUOTE && status == IN_S_QUOTE && c))
				return (1);
	return (0);
}

enum t_status change_status(char c, enum t_status status)
{
	if (c == S_QUOTE && status != IN_S_QUOTE)
		status = IN_S_QUOTE;
	else if (c == S_QUOTE && status == IN_S_QUOTE)
		status = GENERAL;
	if (c == D_QUOTE && status != IN_D_QUOTE)
		status = IN_D_QUOTE;
	else if (c == D_QUOTE && status == IN_D_QUOTE)
		status = GENERAL;
	return (status);
}
