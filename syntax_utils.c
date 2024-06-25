/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:21:43 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/25 14:48:25 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	unclosed_quotes(char *str)
{
	bool	flag;
	char	to_find;

	flag = false;
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			to_find = *str;
			str++;
			flag = true;
			while (*str && *str != to_find)
				str++;
			if (*str == to_find)
				flag = false;
		}
		if (*str)
			str++;
	}
	if (flag == true)
		ft_printf (STDERR_FILENO, "minishell: syntax error unclosed quotes\n");
	return (flag);
}

bool	previous_is_redir(char *str)
{
	str = str - 2;
	if (*str == '>' && *(str - 1) != '>')
		return (false);
	while (str)
	{
		if (*str == '>')
			return (true);
		else if ((*str  < 9 || *str > 13) && *str != 32)
			return (false);
		str--;
	}
	return (false);
}

bool	empty_line(char *str)
{
	while (*str)
	{
		if (!(*str >= 9 || *str <= 13) || *str != 32)
			return (false);
		str++;
	}
	return (true);
}

bool	exceeded_token(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (true);
		if (!(*str >= 9 || *str <= 13) || *str != 32)
			break ;
		str++;
	}
	return (false);
}