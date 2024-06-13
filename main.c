/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:38:50 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/13 16:06:05 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char	*line;
	char	**tokens;
	int		i = 0;

	while (1)
	{
		i = 0;
		line = readline("minishell --> ");
		ft_printf(1, "%s\n", line);
		tokens = ft_split(line, ' ');
		while (tokens[i])
		{
			ft_printf(1, "%s\n", tokens[i]);
			i++;
		}
		free(tokens);
	}
	free(line);
}