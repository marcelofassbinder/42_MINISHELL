/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:41:35 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/27 20:20:26 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_digit(char *data)
{
	char	*new_data;
	char	*to_free;

	to_free = data;
	if (data[1])
	{
		new_data = ft_substr(data, 1, ft_strlen(data));
		free(to_free);
		return (new_data);
	}
	free (to_free);
	return (ft_strdup(""));
}

char	*expand_minishell(char *data)
{
	char	*ret;
	char	*new_data;
	char	*to_free;

	ret = ft_strdup("minishell");
	to_free = data;
	if (data[1])
	{
		new_data = ft_strjoin(ret, &data[1]);
		to_free = data;
		free(to_free);
		return (new_data);
	}
	free(to_free);
	return (ret);
}

char	*expand_special(char *data)
{
	char	*new_data;

	if (!data[1])
	{
		free (data);
		return (ft_strdup(""));
	}
	else
	{
		new_data = ft_substr(data, 1, ft_strlen(data));
		free (data);
		return (new_data);
	}
}
