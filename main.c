/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:38:50 by vivaccar          #+#    #+#             */
/*   Updated: 2024/06/21 15:41:16 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) av;
	(void) ac;
	(void) env;
	start_sigaction();
	while (1)
	{
		line = readline("minishell --> ");
		if (!line)
		{
			ft_printf(1, "exit\n");
			free(line);
			exit(0);
		}
		if (!check_syntax(line))
			continue ;
		free(line);
		//tokenizer(line);
	}
}
