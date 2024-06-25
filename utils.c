/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:14:35 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/25 12:18:26 by vivaccar         ###   ########.fr       */
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

void	exit_line(char *line)
{
	free(line);
	ft_printf(1, "exit\n");
	exit(0);
}

void	free_strings(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
}
