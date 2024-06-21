/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:14:35 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/21 20:47:52 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_token_list(t_token_list *token_list)
{
	t_token	*tmp;
	t_token	*to_free;

	tmp = token_list->first;
	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		if (to_free->type != D_REDIR_OUT && to_free->type != HERE_DOC)
			free (to_free->data);
		free(to_free);
	}
}

void	free_env(t_token *token)
{
	t_token *to_free;

	to_free = token;
	free(to_free->data);
	free(to_free);
}
