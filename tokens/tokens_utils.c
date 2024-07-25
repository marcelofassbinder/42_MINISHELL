/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:50:22 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/22 14:51:41 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prepare_tokens(t_token_list *token_list, t_shell *shell)
{
	check_dollar(token_list, shell);
	g_received_signal = 0;
	join_spaces(token_list);
	join_quotes(token_list);
	join_words(token_list);
	find_files(token_list);
	token_redir_pipe(token_list);
}

int is_type_word(char c)
{
	if (!ft_isspace(c) && c != S_QTE && c != D_QTE && c != PIPE && 
		c != DOLLAR && c != R_IN && c != R_OUT && c)
				return (1);
	return (0);
}

bool	is_redir(t_token *token)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == D_REDIR_OUT || token->type == HERE_DOC)
		return (true);
	return (false);
}

enum e_status append_quotes(t_token_list *token_list, char c, enum e_status status)
{
	if (c == S_QTE)
		status = change_status(token_list, c, status, S_QUOTE);
	else if (c == D_QTE)
		status = change_status(token_list, c, status, D_QUOTE);
	return (status);
}