/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:38:33 by vivaccar          #+#    #+#             */
/*   Updated: 2024/07/22 13:20:59 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	find_special(char *data)
{
	char	*specials;
	int		i;
	int		j;

	i = 0;
	specials = "~`!@#$%^&*()-+={[\\;|:<,.>/?]}";
	while (data[i])
	{
		j = 0;
		while (specials[j])
		{
			if (data[i] == specials[j])
				return (data[i]);
			j++;
		}
		i++;
	}
	return (0);
}

int	count_special(char *data, char special)
{
	int	i;

	i = 0;
	while (data[i] != special && data[i])
		i++;
	return (i);
}

char	*expand_aux(char *data, char *to_expand, char *rest, t_shell *shell)
{
	char	*new;
	char	*to_free;
	char	*env;
	
	env = ft_get_env(to_expand, shell);
	to_free = ft_strdup(env);
	new = ft_strjoin(to_free, rest);
	free(data);
	free(to_expand);
	free(rest);
	free(env);
	return (new);
}

bool	is_special(int c)
{
	char	*specials;

	specials = "~`!@#%^&*()_-+={[\\;|:<,.>/?]}";
	if (ft_strchr(specials, c))
		return (true);
	return (false);
}