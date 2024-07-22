/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:21:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/22 15:22:19 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**define_cmd_args(t_token *token)
{
	char	**cmd_args;
	int		counter;
	int		i;
	int		flag;
	
	flag = 0;
	counter = count_args(token);
	cmd_args = ft_calloc(sizeof(char *), counter + 1);
	i = 0;
	while(token && token->type != PIPELINE)
	{
		if (is_local_variable(token) && flag == 0)
		{
			token = get_next_token(token->next);
			continue ;
		}
		else if (token->type == WORD || token->type == T_NULL)
		{
			cmd_args[i] = ft_strdup(token->data);
			i++;
		}
		flag = 1;
		token = token->next;
	}
	return(cmd_args);
}

int	count_args(t_token *token)
{
	int	count;
	int	flag;

	flag = 0;
	count = 0;
	while(token && token->type != PIPELINE)
	{
		if (is_local_variable(token) && flag == 0)
		{
			token = get_next_token(token->next);
			continue ;
		}
		else if (token->type == WORD || token->type == T_NULL)
			count++;
		token = token->next;
		flag = 1;
	}
	return (count);
}

bool	is_local_variable(t_token *token)
{
	if (token->status == GENERAL && token->type == WORD 
		&& ft_strchr(token->data, '='))
		return (true);
	return (false);
}