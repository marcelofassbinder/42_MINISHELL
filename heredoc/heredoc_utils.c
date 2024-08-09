/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:47:52 by vivaccar          #+#    #+#             */
/*   Updated: 2024/08/03 14:03:48 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*create_here_doc_array(t_shell *shell)
{
	int	*array_fd_here_doc;

	array_fd_here_doc = ft_calloc(sizeof(int), shell->count_hd + 1);
	if (!array_fd_here_doc)
		shell_error(shell, "Calloc error: heredoc", 0, true);
	array_fd_here_doc[shell->count_hd] = -1;
	return (array_fd_here_doc);
}

int	count_here_doc(t_shell *shell)
{
	t_token	*token;
	int		count;

	token = shell->token_list->first;
	count = 0;
	while (token)
	{
		if (token->type == HERE_DOC)
			count++;
		token = token->next;
	}
	return (count);
}
